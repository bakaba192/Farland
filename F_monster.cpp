#include "stdafx.h"
#include "F_monster.h"

HRESULT F_monster::init(int x, int y, MonsterName name, int lv)
{
	_mName = name;

	switch (_mName)
	{
	case MN_HYDRA:
		_name = "�����";
		break;
	case MN_JACO1:
		_name = "�θ�";
		break;
	default:

		break;
	}

	_targetPoint.y = NULL;
	_targetPoint.x = NULL;

	ZeroMemory(&_mStatus, sizeof(MonsterStatus));
	_mStatus.isReadyToBehavior = true;
	_mStatus.isReadyToMove = true;

	_mStatus.lv = lv;
	_mStatus.maxHp = 10;
	_mStatus.hp = 10;
	_mStatus.moveLimit = 4;
	_mStatus.attack = 5;
	_mStatus.forward = 1;
	_mStatus.def = lv;

	_indexX = x;
	_indexY = y;

	_mState = M_READY;//���� ����. = ���
	_mPreState = M_READY;

	MAPDATA->getTileData(x, y)->wayState = WAYSTATE::WAY_BLOCK;


	_tempForward = 0;				//�ӽ������� ĳ���Ͱ� ���� ����

	_moveOn = false;

	_moveCount = 0;					//�̵��� ���������� ã�� ī����
	_jumpCount = 0;					//�����̵��� ����� ī����

	_MoveRc = MAPDATA->getTileData(_indexX, _indexY)->rc;

	_repeatCount = 0;				//��� �ݺ��� ���ΰ�?

	_moveLimitCount = 0;

	_alpha = 255;

	//������ ��¿�
	_numberFrame = 0;
	_numberCount = 0;
	_numberUpUp = 0;

	hund = 0;
	ten = 0;
	one = 0;

	isOnPrintDemage = false;

	_onAttack = false;

	if (_name == "�����")
	{
		_mStatus.attack = 25 + lv;
		_mStatus.maxHp = 60 + lv;
		_mStatus.hp = _mStatus.maxHp;
	}
	else if(_name == "�θ�")
	{
		_mStatus.attack = 15 + lv;
		_mStatus.maxHp = 30 + lv;
		_mStatus.hp = _mStatus.maxHp;
	}

	return S_OK;
}

void F_monster::release(void)
{

}

void F_monster::update(void)
{

	if (_mStatus.hp > _mStatus.maxHp)
	{
		_mStatus.hp = _mStatus.maxHp;
	}


	stateChange();
	behaviorByState();

}

void F_monster::render(void)
{
	showCharaByState();
}

void F_monster::behaviorByState()
{
	_mStatus.count++;
	if (_mPreState != _mState)
	{
		_repeatCount = 0;
		_mStatus.currentFrame = 0;
		_mStatus.count = 0;
		_mPreState = _mState;//���� ���¿� ���� ���¸� ����(������ ���� ������ �ϰ� �־���.)
	}

	switch (_mState)
	{
	case M_READY:

		if (_mStatus.count % 10 == 0)
		{
			_mStatus.currentFrame++;
		}

		if (_mStatus.currentFrame > 3)
		{
			_mStatus.currentFrame = 0;
		}

		break;
	case M_MOVE:
		if (_mStatus.count % 5 == 0)
		{
			_mStatus.currentFrame++;
		}
		if (_mStatus.currentFrame > 3)
		{
			_mStatus.currentFrame = 0;
		}

		moveToWay();

		break;
	case M_JUMPUP:


		jumpUp();

		break;
	case M_JUMPDOWN:

		jumpDown();
		break;
	case M_ATTACK:
		if (_mStatus.count % 5 == 0)
		{
			_mStatus.currentFrame++;
		}

		if (_mStatus.currentFrame > IMAGEMANAGER->findImage(_name + "_����")->getMaxFrameY())
		{
			if (_name == "�����" && _repeatCount < 2)
			{
				_repeatCount++;
				_mStatus.currentFrame = 0;
			}
			else//�θ� etc...
			{
				_onAttack = false;
			}
		}
		break;
	case M_DEMAGED:
		if (STATEMANAGER->getState() == B_NONE)
		{
			_mState = M_READY;
		}
		break;
	case M_DEATH:
		MAPDATA->getTileData(_indexX, _indexY)->wayState = WAYSTATE::WAY_EMPTY;

		if (_mStatus.count % 10 == 0)
		{
			_mStatus.currentFrame++;
		}
		if (_mStatus.currentFrame > 3)
		{
			_mStatus.currentFrame = 0;
		}

		_alpha -= 5;

		if (_alpha < 0)
		{
			_alpha = 0;
		}

		break;
	default:
		break;
	}
}

void F_monster::stateChange()
{

}

void F_monster::showCharaByState()
{
	switch (_mState)
	{
	case M_READY:
		IMAGEMANAGER->focusRender("�׸���", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64);
		IMAGEMANAGER->focusFrameRender(this->_name + "_���", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _mStatus.forward, _mStatus.currentFrame);
		break;
	case M_MOVE:
		IMAGEMANAGER->focusRender("�׸���", getMemDC(), _MoveRc.left - 16, _MoveRc.top - 64);
		IMAGEMANAGER->focusFrameRender(this->_name + "_�̵�", getMemDC(), _MoveRc.left - 16, _MoveRc.top - 64, _mStatus.moveForward, _mStatus.currentFrame);
		break;
	case M_JUMPUP:
		//IMAGEMANAGER->focusFrameRender(this->_name + "_����", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _mStatus.forward, _mStatus.currentFrame);
		IMAGEMANAGER->focusFrameRender(this->_name + "_����", getMemDC(), _MoveRc.left - 16, _MoveRc.top - 64, _mStatus.moveForward, _mStatus.currentFrame);
		break;
	case M_JUMPDOWN:
		//IMAGEMANAGER->focusFrameRender(this->_name + "_����", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _mStatus.forward, _mStatus.currentFrame);
		IMAGEMANAGER->focusFrameRender(this->_name + "_����", getMemDC(), _MoveRc.left - 16, _MoveRc.top - 64, _mStatus.moveForward, _mStatus.currentFrame);
		break;
	case M_ATTACK:
		IMAGEMANAGER->focusRender("�׸���", getMemDC(), _MoveRc.left - 16, _MoveRc.top - 64);
		IMAGEMANAGER->focusFrameRender(this->_name + "_����", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _mStatus.forward, _mStatus.currentFrame);
		break;
	case M_DEMAGED:
		IMAGEMANAGER->focusRender("�׸���", getMemDC(), _MoveRc.left - 16, _MoveRc.top - 64);
		IMAGEMANAGER->focusFrameRender(this->_name + "_�ǰ�", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _mStatus.forward, _mStatus.currentFrame);
		break;
	case M_DEATH:
		IMAGEMANAGER->focusRender("�׸���", getMemDC(), _MoveRc.left - 16, _MoveRc.top - 64);
		IMAGEMANAGER->focusFrameAlphaRender(this->_name + "_���", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _mStatus.forward, _mStatus.currentFrame, _alpha);
		//IMAGEMANAGER->focusFrameRender("����", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _mStatus.forward, _mStatus.currentFrame);

		break;
	default:
		break;
	}
}


void F_monster::moveToWay()
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
			_moveLimitCount++;
			if (_moveLimitCount >= _mStatus.moveLimit)
			{
				_moveLimitCount = 0;
				while (true)
				{
					if (!_way.empty())
					{
						_way.pop_back();
					}
					else
					{
						break;
					}
				}
			}
		}
		else
		{
			MAPDATA->getTileData(MAPDATA->getStartX(), MAPDATA->getStartY())->wayState = WAYSTATE::WAY_EMPTY;
			MAPDATA->getTileData(_indexX, _indexY)->wayState = WAYSTATE::WAY_BLOCK;
			_mState = M_READY;
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
				_mStatus.moveForward = 3;
				_MoveRc = RectMake(_MoveRc.left + 4, _MoveRc.top + 2, TILEWIDTH, TILEHEIGHT);
			}
			else if (_MovePoint.x == -1)//��
			{
				_mStatus.moveForward = 2;
				_MoveRc = RectMake(_MoveRc.left - 4, _MoveRc.top - 2, TILEWIDTH, TILEHEIGHT);
			}
			else if (_MovePoint.y == 1)//��
			{
				_mStatus.moveForward = 1;
				_MoveRc = RectMake(_MoveRc.left - 4, _MoveRc.top + 2, TILEWIDTH, TILEHEIGHT);
			}
			else if (_MovePoint.y == -1)//��
			{
				_mStatus.moveForward = 0;
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
					_mStatus.count = 0;
					_mState = M_JUMPUP;
				}
				else if (z == 2)
				{
					_mStatus.count = 0;
					_mState = M_JUMPDOWN;

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
			_mStatus.forward = _mStatus.moveForward;
			_moveOn = false;
		}
	}
}

void F_monster::jumpUp()
{
	//32z���� 32��ŭ ���̸� ��.

	//8������ ���� ��ȭ���Ѻ���.

	if (_mStatus.currentFrame == 0)
	{
		if (_mStatus.count % 8 == 0 && _mStatus.count != 0)
		{
			_mStatus.currentFrame++;
			_mStatus.count = 0;
		}
		return;
	}
	else if (_mStatus.currentFrame == 1)
	{
		//���� ����~
		_MoveRc = RectMake(_MoveRc.left, _MoveRc.top - 4, TILEWIDTH, TILEHEIGHT);
		if (_mStatus.count % 12 == 0 && _mStatus.count != 0)
		{
			_mStatus.currentFrame++;
			_mStatus.count = 0;
		}
		return;
	}
	else if (_mStatus.currentFrame == 2)
	{
		//�ö󰬴� ��������~
		_MoveRc = RectMake(_MoveRc.left, _MoveRc.top + 4, TILEWIDTH, TILEHEIGHT);
		if (_mStatus.count % 4 == 0 && _mStatus.count != 0)
		{
			_mStatus.currentFrame++;
			_mStatus.count = 0;
		}
		//�������� ������ �ε��� �̵�.
		_indexX = _targetPoint.x;
		_indexY = _targetPoint.y;
		return;
	}
	else if (_mStatus.currentFrame == 3)
	{
		if (_mStatus.count % 15 == 0 && _mStatus.count != 0)
		{
			_mStatus.currentFrame++;
			_mStatus.count = 0;
			_mState = M_MOVE;//�̻��·δ� �ȵȴ�. �ٽ� ������ ���۵Ǿ� ����. movecount�� 8�̸� �����ϰ� �ٽ� 8���� 16���� �����δ�. ������ z���� �ٲ۴�....
		}
		return;
	}


}

void F_monster::jumpDown()
{

	if (_mStatus.currentFrame == 0)
	{
		if (_mStatus.count % 8 == 0 && _mStatus.count != 0)
		{
			_mStatus.currentFrame++;
			_mStatus.count = 0;
		}
		return;
	}
	else if (_mStatus.currentFrame == 1)
	{
		//���� ����~
		_MoveRc = RectMake(_MoveRc.left, _MoveRc.top - 4, TILEWIDTH, TILEHEIGHT);
		if (_mStatus.count % 4 == 0 && _mStatus.count != 0)
		{
			_mStatus.currentFrame++;
			_mStatus.count = 0;
		}
		return;
	}
	else if (_mStatus.currentFrame == 2)
	{
		//�ö󰬴� ��������~
		_MoveRc = RectMake(_MoveRc.left, _MoveRc.top + 4, TILEWIDTH, TILEHEIGHT);
		if (_mStatus.count % 12 == 0 && _mStatus.count != 0)
		{
			_mStatus.currentFrame++;
			_mStatus.count = 0;
		}


		_indexX = _targetPoint.x;
		_indexY = _targetPoint.y;
		return;
	}
	else if (_mStatus.currentFrame == 3)
	{
		if (_mStatus.count % 15 == 0 && _mStatus.count != 0)
		{
			_mStatus.currentFrame++;
			_mStatus.count = 0;
			_mState = M_MOVE;//�̻��·δ� �ȵȴ�. �ٽ� ������ ���۵Ǿ� ����. movecount�� 8�̸� �����ϰ� �ٽ� 8���� 16���� �����δ�. ������ z���� �ٲ۴�....
		}
		return;
	}
}



bool F_monster::printDemage(int Demage)
{

	isOnPrintDemage = true;

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

void  F_monster::DemageRender()
{
	if (isOnPrintDemage)
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
}

