#include "stdafx.h"
#include "character.h"

HRESULT character::init(int x, int y, CharaName name, int lv)
{
	//�ʱ�ȭ

	_state = C_READY;
	_preState = C_READY;

	_cName = name;

	switch (_cName)
	{
	case N_KARIN:
		_charaName = "ī��";
		_status.Exp = CHARADATA->getKarinExp();
		break;
	case N_ARIS:
		_charaName = "�Ƹ���";
		_status.Exp = CHARADATA->getArisExp();
		break;
	case N_AL:
		_charaName = "��";
		_status.Exp = CHARADATA->getAlExp();
		break;
	default:
		
		break;
	}

	_targetPoint.y = NULL;
	_targetPoint.x = NULL;

	_indexX = x;					//Ÿ�ϻ��� ��ġ. i, j
	_indexY = y;

	_tempX = 0;						//ĳ���Ͱ� �Ͻ������� ǥ�õ� ��ġ�� x y��
	_tempY = 0;

	_tempForward = 0;				//�ӽ������� ĳ���Ͱ� ������ ����

	_moveForward = 0;				//ĳ���Ͱ� �����϶� ������ ����

	_moveCount = 0;					//ĳ���Ͱ� �����϶� Ÿ���� ������������ ���̰� �޶���.

	_jumpCount = 0;					//�����̵��� ����� ī����

	_MoveRc = MAPDATA->getTileData(_indexX, _indexY)->rc;

	_repeatCount = 0;

	_moveOn = false;

	//_way->push({ 0, -1 });
	/*_way->push({ 0, -1 });
	_way->push({ 0, -1 });
	_way->push({ 0, -1 });
	_way->push({ 0, -1 });
	_way->push({ 0, -1 });
	_way->push({ 0, -1 });*/

	_status.attack = 3;
	_status.mAttack = 5;
	_status.count = 0;
	_status.currentFrame = 0;
	_status.forward = 3;
	_status.isReadyToBehavior = true;
	_status.isReadyToMove = true;
	_status.lv = lv;
	_status.def = lv;
	_status.moveLimit = 5;
	_status.range = 1;
	

	MAPDATA->getTileData(_indexX, _indexY)->wayState = WAYSTATE::WAY_BLOCK;


	//��������¿�

	_numberFrame = 0;
	_numberCount = 0;
	_numberUpUp = 0;

	hund = 0;
	ten = 0;
	one = 0;

	isOnPrintDemage = false;
	
	if (_charaName == "ī��")
	{
		_status.maxHp = 30 + lv;
		_status.hp = _status.maxHp;
		_status.attack = 15 + lv * 1;
		_status.mAttack = 15 + lv * 4;

		_Fskill = new F_Skill;
		_Fskill->init("�÷��ӹ���Ʈ", _status.mAttack, 2);
	}
	else if (_charaName == "�Ƹ���")
	{
		_status.maxHp = 30 + lv;
		_status.hp = _status.maxHp;
		_status.attack = 5 + lv * 1;
		_status.mAttack = 15 + lv * 3;

		_Fskill = new F_Skill;
		_Fskill->init("��", _status.mAttack, 0);
	}
	else if(_charaName == "��")
	{
		_status.def = lv * 2;
		_status.maxHp = 50 + lv * 2;
		_status.hp = _status.maxHp;
		_status.attack = 30 + lv * 4;
		_status.mAttack = 15 + lv;

		_Fskill = new F_Skill;
		_Fskill->init("��", _status.mAttack, 0);
	}

	_vSkill.push_back(_Fskill);

	_selectedSkill = _Fskill;

	return S_OK;
}

void character::release(void)
{

}

void character::update(void)
{
	if (_status.hp > _status.maxHp)
	{
		_status.hp = _status.maxHp;
	}

	behaviorByState();

	for (int i = 0; i < _vSkill.size(); i++)
	{
		(*(_vSkill.begin() + i))->update();
	}
}

void character::render(void)
{
	showCharaByState();
}

void character::behaviorByState()
{	
	/*
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_state = C_READY;
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_state = C_ATTACK;
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_state = C_STUN;
	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		_state = C_DEMAGED;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_status.forward = 1;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_status.forward = 0;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_status.forward = 2;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_status.forward = 3;
	}
	*/

	_status.count++;
	if (_preState != _state)
	{
		_status.currentFrame = 0;
		_status.count = 0;
		_repeatCount = 0;
		_preState = _state;//���� ���¿� ���� ���¸� ����(������ ���� ������ �ϰ� �־���.)
	}

	switch (_state)
	{
	case C_READY:

		if (_status.hp <= 0)
		{
			_status.hp = 0;
			_state = C_STUN;
			return;
		}
		else if (!_status.isReadyToBehavior && !_status.isReadyToMove)
		{
			_state = C_STAY;
		}

		if (_status.count % 10 == 0)
		{
			_status.currentFrame++;
		}

		if (_status.currentFrame > 3)
		{
			_status.currentFrame = 0;
		}

		break;
	case C_STAY:

		if (_status.isReadyToBehavior || _status.isReadyToMove)
		{
			_state = C_READY;
		}

		break;
	case C_MOVE:

		if (_status.count % 5 == 0)
		{
			_status.currentFrame++;
		}
		if (_status.currentFrame > 3)
		{
			_status.currentFrame = 0;
		}

		moveToWay();

		break;
	case C_JUMPUP:


		jumpUp();

		break;
	case C_JUMPDOWN:

		jumpDown();
		break;
	case C_ATTACK:

		if (_charaName == "ī��")
		{
			if (_status.count % 6 == 0)
			{
				_status.currentFrame++;
			}
		}
		else if (_charaName == "�Ƹ���")
		{
			if (_status.count % 2 == 0)
			{
				_status.currentFrame++;
				if (_status.currentFrame > 5 && _repeatCount < 5)
				{
					_repeatCount++;
					_status.currentFrame = 2;
				}
			}
		}
		else if (_charaName == "��")
		{
			if (_status.count % 6 == 0)
			{
				_status.currentFrame++;
			}
		}
/*
		if (_charaName == "�θ�")
		{
			if (_status.currentFrame > 11)
			{
				_state = C_READY;
				_status.currentFrame = 0;
			}
		}
		else
		{
			if (_status.currentFrame > 8)
			{
				_state = C_READY;
				_status.currentFrame = 0;
			}
		}*/
		break;
	case C_SKILL1:

		if (_status.count % 10 == 0)
		{
			_status.currentFrame++;
		}

		if (_charaName == "ī��")
		{
			if (_status.currentFrame > 2)
			{
				_repeatCount++;
				_status.currentFrame = 0;
			}

			if (_repeatCount > 2)
			{
				_repeatCount = 0;
				_state = C_SKILL2;
			}
		}
		else if (_charaName == "�Ƹ���")
		{
			if (_status.currentFrame > 9)
			{
				_state = C_SKILL2;
			}
		}


		break;
	case C_SKILL2:
		

		if (_charaName == "ī��")
		{

			if (_status.count % 8 == 0)
			{
				_status.currentFrame++;
			}


			if (_status.currentFrame > 2)
			{
				_repeatCount++;
				_status.currentFrame = 0;
			}

			if (_repeatCount > 0)
			{
				_repeatCount = 0;
				_state = C_SKILL3;
			}
		}
		else if (_charaName == "�Ƹ���")
		{

			if (_status.currentFrame < 9)
			{
				_status.currentFrame = 9;
			}

			if (_status.count % 15 == 0)
			{
				_status.currentFrame++;
			}


			if (_status.currentFrame > 10)
			{
				_status.currentFrame = 9;
			}

		}

		break;
	case C_SKILL3:

		if (_status.count % 10 == 0)
		{
			_status.currentFrame++;
		}
		if (_status.currentFrame > 4)
		{
			_repeatCount++;
			if (_repeatCount <= 3)
			{
				_status.currentFrame = 0;
			}
		}
		break;
	case C_DEMAGED:
/*
		if (_status.count % 10 == 0)
		{
			_status.currentFrame++;
		}
		if (_status.currentFrame > 1)
		{
			_status.currentFrame = 0;
		}*/
		break;
	case C_GUARD:

		break;
	case C_MISS:

		break;
	case C_FREEZE:

		break;
	case C_PETRIFICATION:

		break;
	case C_STUN:
		if (_status.count % 10 == 0)
		{
			_status.currentFrame++;
		}
		if (_status.currentFrame > 3)
		{
			_status.currentFrame = 0;
		}
		_status.isReadyToBehavior = false;
		_status.isReadyToMove = false;

		if (getStatus().hp > 0)
		{
			setState(C_READY);
		}

		break;
	default:
		break;
	}
}


void character::showCharaByState()
{
	if (_state != C_JUMPDOWN || C_JUMPUP || C_STUN)
	{
		
	}

	switch (_state)
	{
	case C_READY:

		IMAGEMANAGER->focusRender("�׸���", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64);
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_�غ�", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		break;
	case C_STAY:
		IMAGEMANAGER->focusRender("�׸���", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64);
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_���", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		//IMAGEMANAGER->focusFrameRender(this->_charaName + "_���", getMemDC(), _MoveRc.left - 16,_MoveRc.top - 64, _status.forward, _status.currentFrame);
		break;
	case C_MOVE:
		IMAGEMANAGER->focusRender("�׸���", getMemDC(), _MoveRc.left - 16, _MoveRc.top - 64);
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_�̵�", getMemDC(), _MoveRc.left - 16, _MoveRc.top - 64, _moveForward, _status.currentFrame);
		break;
	case C_MOVETEMPORARY:
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_�غ�", getMemDC(), MAPDATA->getTileData(_tempX, _tempY)->rc.left - 16, MAPDATA->getTileData(_tempX, _tempY)->rc.top - 64, _tempForward, _status.currentFrame);//�Ÿ������������� �Ͻ������� ĳ���Ͱ� ����������쿡 ���� ��������.
		if (STATEMANAGER->getState() == B_SELECTFORWARD)
		{
			IMAGEMANAGER->focusFrameRender("����", getMemDC(), MAPDATA->getTileData(_tempX, _tempY)->rc.left - 16, MAPDATA->getTileData(_tempX, _tempY)->rc.top - 64, _tempForward, _status.currentFrame);
		}
		break;
	case C_JUMPUP:
		//IMAGEMANAGER->focusFrameRender(this->_charaName + "_����", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_����", getMemDC(), _MoveRc.left - 16, _MoveRc.top - 64, _moveForward, _status.currentFrame);
		break;
	case C_JUMPDOWN:
		//IMAGEMANAGER->focusFrameRender(this->_charaName + "_����", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_����", getMemDC(), _MoveRc.left - 16, _MoveRc.top - 64, _moveForward, _status.currentFrame);
		break;
	case C_ATTACK:
		IMAGEMANAGER->focusRender("�׸���", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64);
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_����", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		break;
	case C_SKILL1:
		IMAGEMANAGER->focusRender("�׸���", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64);
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_��ų1", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		break;
	case C_SKILL2:
		IMAGEMANAGER->focusRender("�׸���", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64);
		if (_charaName == "ī��")
		{
			IMAGEMANAGER->focusFrameRender(this->_charaName + "_��ų2", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		}
		else if (_charaName == "�Ƹ���")
		{
			IMAGEMANAGER->focusFrameRender(this->_charaName + "_��ų1", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		}
		break;
	case C_SKILL3:
		IMAGEMANAGER->focusRender("�׸���", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64);
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_��ų3", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		break;
	case C_DEMAGED:
		IMAGEMANAGER->focusRender("�׸���", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64);
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_�ǰ�", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		break;
	case C_GUARD:
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_����", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		break;
	case C_MISS:
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_ȸ��", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		break;
	case C_FREEZE:
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_����", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		break;
	case C_PETRIFICATION:
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_��ȭ", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		break;
	case C_STUN:
		IMAGEMANAGER->focusRender("�׸���", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64);
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_����", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		IMAGEMANAGER->focusFrameRender("����", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		break;
	default:
		break;
	}
}

void character::moveToWay()
{
	if (_moveOn == false)
	{
		if (!_way.empty())
		{
			_MovePoint = _way.back();
			_targetPoint.x = _indexX + _MovePoint.x;
			_targetPoint.y = _indexY + _MovePoint.y;
			_way.pop_back();
			_moveOn = true;
			_moveCount = 0;
		}
		else
		{
			MAPDATA->getTileData(MAPDATA->getStartX(), MAPDATA->getStartY())->wayState = WAYSTATE::WAY_EMPTY;
			MAPDATA->getTileData(MAPDATA->getEndX(), MAPDATA->getEndY())->wayState = WAYSTATE::WAY_BLOCK;
			_state = C_READY;
		}
	}

	if (_moveOn)
	{
		//X, I�� �¿�
		//Y, J�� �յ�
		if (!(_MoveRc.left == MAPDATA->getTileData(_targetPoint.x, _targetPoint.y)->rc.left &&
			_MoveRc.top == MAPDATA->getTileData(_targetPoint.x, _targetPoint.y)->rc.top))
		{

			_moveCount++;
			if (_MovePoint.x == 1)//��
			{
				_moveForward = 3;
				_MoveRc = RectMake(_MoveRc.left + 4, _MoveRc.top + 2, TILEWIDTH, TILEHEIGHT);
			}
			else if (_MovePoint.x == -1)//��
			{
				_moveForward = 2;
				_MoveRc = RectMake(_MoveRc.left - 4, _MoveRc.top - 2, TILEWIDTH, TILEHEIGHT);
			}
			else if (_MovePoint.y == 1)//��
			{
				_moveForward = 1;
				_MoveRc = RectMake(_MoveRc.left - 4, _MoveRc.top + 2, TILEWIDTH, TILEHEIGHT);
			}
			else if (_MovePoint.y == -1)//��
			{
				_moveForward = 0;
				_MoveRc = RectMake(_MoveRc.left + 4, _MoveRc.top - 2, TILEWIDTH, TILEHEIGHT);
			}
			//������������ �ѹ� ����.

			if (_moveCount == 4)
			{
				int z = MAPDATA->getTileData(_indexX, _indexY)->z - MAPDATA->getTileData(_targetPoint.x, _targetPoint.y)->z;
				if (z == 1 || z == -1)
				{
					_MoveRc = RectMake(_MoveRc.left, _MoveRc.top + z * 16, TILEWIDTH, TILEHEIGHT);
					_indexX = _targetPoint.x;
					_indexY = _targetPoint.y;
				}
				else if (z == -2)
				{
					_status.count = 0;
					_state = C_JUMPUP;
				}
				else if (z == 2)
				{
					_status.count = 0;
					_state = C_JUMPDOWN;

				}
				else if (z == 0)
				{
					_indexX = _targetPoint.x;
					_indexY = _targetPoint.y;
				}
			}
		}
		else
		{
			//��ĭ �̵� �Ϸ�
			_status.forward = _tempForward;
			_moveOn = false;
		}
	}
}

void character::jumpUp()
{
	//32z���� 32��ŭ ���̸� ��.

	//8������ ���� ��ȭ���Ѻ���.

	if (_status.currentFrame == 0)
	{
		if (_status.count % 8 == 0 && _status.count != 0)
		{
			_status.currentFrame++;
			_status.count = 0;
		}
		return;
	}
	else if (_status.currentFrame == 1 )
	{
		//���� ����~
		_MoveRc = RectMake(_MoveRc.left, _MoveRc.top - 4, TILEWIDTH, TILEHEIGHT);
		if (_status.count % 12 == 0 && _status.count != 0)
		{
			_status.currentFrame++;
			_status.count = 0;
		}
		return;
	}
	else if ( _status.currentFrame == 2 )
	{
		//�ö󰬴� ��������~
		_MoveRc = RectMake(_MoveRc.left, _MoveRc.top + 4, TILEWIDTH, TILEHEIGHT);
		if (_status.count % 4 == 0 && _status.count != 0)
		{
			_status.currentFrame++;
			_status.count = 0;
		}
		//�������� ������ �ε��� �̵�.
		_indexX = _targetPoint.x;
		_indexY = _targetPoint.y;
		return;
	}
	else if ( _status.currentFrame == 3)
	{
		if (_status.count % 15 == 0 && _status.count != 0)
		{
			_status.currentFrame++;
			_status.count = 0;
			_state = C_MOVE;//�̻��·δ� �ȵȴ�. �ٽ� ������ ���۵Ǿ� ����. movecount�� 8�̸� �����ϰ� �ٽ� 8���� 16���� �����δ�. ������ z���� �ٲ۴�....
		}
		return;
	}


}

void character::jumpDown()
{

	if (_status.currentFrame == 0)
	{
		if (_status.count % 8 == 0 && _status.count != 0)
		{
			_status.currentFrame++;
			_status.count = 0;
		}
		return;
	}
	else if (_status.currentFrame == 1)
	{
		//���� ����~
		_MoveRc = RectMake(_MoveRc.left, _MoveRc.top - 4, TILEWIDTH, TILEHEIGHT);
		if (_status.count % 4 == 0 && _status.count != 0)
		{
			_status.currentFrame++;
			_status.count = 0;
		}
		return;
	}
	else if (_status.currentFrame == 2)
	{
		//�ö󰬴� ��������~
		_MoveRc = RectMake(_MoveRc.left, _MoveRc.top + 4, TILEWIDTH, TILEHEIGHT);
		if (_status.count % 12 == 0 && _status.count != 0)
		{
			_status.currentFrame++;
			_status.count = 0;
		}


		_indexX = _targetPoint.x;
		_indexY = _targetPoint.y;
		return;
	}
	else if (_status.currentFrame == 3)
	{
		if (_status.count % 15 == 0 && _status.count != 0)
		{
			_status.currentFrame++;
			_status.count = 0;
			_state = C_MOVE;//�̻��·δ� �ȵȴ�. �ٽ� ������ ���۵Ǿ� ����. movecount�� 8�̸� �����ϰ� �ٽ� 8���� 16���� �����δ�. ������ z���� �ٲ۴�....
		}
		return;
	}


	//_MoveRc = RectMake(_MoveRc.left, _MoveRc.top + z * 16, TILEWIDTH, TILEHEIGHT);
}



bool character::printDemage(int Demage , bool isHeal)
{
	isOnPrintDemage = true;

	_isHeal = isHeal;

	hund = Demage / 100;
	ten = (Demage % 100) / 10;
	one = Demage % 10;


	_numberCount++;

	if (_numberCount > 4)
	{
		_numberCount = 0;
		_numberFrame++;
	}

	if (_numberFrame < 9)
	{
		_numberUpUp = 32 * sinf(22.5 * M_RAD * _numberFrame);//�̺κ��� �� �Ҿ�
	}



	if (_numberFrame > 17)
	{
		_numberFrame = 0;
		_numberCount = 0;
		_numberUpUp = 0;

		isOnPrintDemage = false;

		return true;
	}
	return false;
}

void  character::DemageRender()
{
	if (isOnPrintDemage)
	{
		if (!_isHeal)
		{
			if (hund == 0)//100�� �ڸ� ����
			{
				if (ten == 0)//1�� �ڸ� ���
				{
					IMAGEMANAGER->focusFrameRender("������Ʈ2", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 24, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, one);
					//Rectangle(hdc, MAPDATA->getTileData(_indexX, _indexY)->rc.left, MAPDATA->getTileData(_indexX, _indexY)->rc.top, MAPDATA->getTileData(_indexX, _indexY)->rc.right, MAPDATA->getTileData(_indexX, _indexY)->rc.bottom);
				}
				else//10�� �ڸ� ���
				{
					IMAGEMANAGER->focusFrameRender("������Ʈ2", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, ten);
					IMAGEMANAGER->focusFrameRender("������Ʈ2", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 32, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, one);
				}
			}
			else//100�� �ڸ� ���� ���
			{
				IMAGEMANAGER->focusFrameRender("������Ʈ2", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 8, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, hund);
				IMAGEMANAGER->focusFrameRender("������Ʈ2", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 24, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, ten);
				IMAGEMANAGER->focusFrameRender("������Ʈ2", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 40, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, one);
			}
		}
		else
		{
			if (hund == 0)//100�� �ڸ� ����
			{
				if (ten == 0)//1�� �ڸ� ���
				{
					IMAGEMANAGER->focusFrameRender("������Ʈ1", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 24, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, one);
					//Rectangle(hdc, MAPDATA->getTileData(_indexX, _indexY)->rc.left, MAPDATA->getTileData(_indexX, _indexY)->rc.top, MAPDATA->getTileData(_indexX, _indexY)->rc.right, MAPDATA->getTileData(_indexX, _indexY)->rc.bottom);
				}
				else//10�� �ڸ� ���
				{
					IMAGEMANAGER->focusFrameRender("������Ʈ1", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, ten);
					IMAGEMANAGER->focusFrameRender("������Ʈ1", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 32, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, one);
				}
			}
			else//100�� �ڸ� ���� ���
			{
				IMAGEMANAGER->focusFrameRender("������Ʈ1", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 8, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, hund);
				IMAGEMANAGER->focusFrameRender("������Ʈ1", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 24, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, ten);
				IMAGEMANAGER->focusFrameRender("������Ʈ1", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 40, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, one);
			}
		}
	}



}

