#include "stdafx.h"
#include "character.h"

HRESULT character::init(int x, int y, CharaName name, int lv)
{
	//초기화

	_state = C_READY;
	_preState = C_READY;

	_cName = name;

	switch (_cName)
	{
	case N_KARIN:
		_charaName = "카린";
		_status.Exp = CHARADATA->getKarinExp();
		break;
	case N_ARIS:
		_charaName = "아리스";
		_status.Exp = CHARADATA->getArisExp();
		break;
	case N_AL:
		_charaName = "알";
		_status.Exp = CHARADATA->getAlExp();
		break;
	default:
		
		break;
	}

	_targetPoint.y = NULL;
	_targetPoint.x = NULL;

	_indexX = x;					//타일상의 위치. i, j
	_indexY = y;

	_tempX = 0;						//캐릭터가 일시적으로 표시될 위치의 x y값
	_tempY = 0;

	_tempForward = 0;				//임시적으로 캐릭터가 가지는 방향

	_moveForward = 0;				//캐릭터가 움직일때 가지는 방향

	_moveCount = 0;					//캐릭터가 움직일때 타일의 절반지점에서 높이가 달라짐.

	_jumpCount = 0;					//점프이동에 사용할 카운터

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


	//데미지출력용

	_numberFrame = 0;
	_numberCount = 0;
	_numberUpUp = 0;

	hund = 0;
	ten = 0;
	one = 0;

	isOnPrintDemage = false;
	
	if (_charaName == "카린")
	{
		_status.maxHp = 30 + lv;
		_status.hp = _status.maxHp;
		_status.attack = 15 + lv * 1;
		_status.mAttack = 15 + lv * 4;

		_Fskill = new F_Skill;
		_Fskill->init("플레임버스트", _status.mAttack, 2);
	}
	else if (_charaName == "아리스")
	{
		_status.maxHp = 30 + lv;
		_status.hp = _status.maxHp;
		_status.attack = 5 + lv * 1;
		_status.mAttack = 15 + lv * 3;

		_Fskill = new F_Skill;
		_Fskill->init("힐", _status.mAttack, 0);
	}
	else if(_charaName == "알")
	{
		_status.def = lv * 2;
		_status.maxHp = 50 + lv * 2;
		_status.hp = _status.maxHp;
		_status.attack = 30 + lv * 4;
		_status.mAttack = 15 + lv;

		_Fskill = new F_Skill;
		_Fskill->init("힐", _status.mAttack, 0);
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
		_preState = _state;//이전 상태에 현재 상태를 저장(전에도 같은 동작을 하고 있었다.)
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

		if (_charaName == "카린")
		{
			if (_status.count % 6 == 0)
			{
				_status.currentFrame++;
			}
		}
		else if (_charaName == "아리스")
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
		else if (_charaName == "알")
		{
			if (_status.count % 6 == 0)
			{
				_status.currentFrame++;
			}
		}
/*
		if (_charaName == "두목")
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

		if (_charaName == "카린")
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
		else if (_charaName == "아리스")
		{
			if (_status.currentFrame > 9)
			{
				_state = C_SKILL2;
			}
		}


		break;
	case C_SKILL2:
		

		if (_charaName == "카린")
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
		else if (_charaName == "아리스")
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

		IMAGEMANAGER->focusRender("그림자", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64);
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_준비", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		break;
	case C_STAY:
		IMAGEMANAGER->focusRender("그림자", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64);
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_대기", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		//IMAGEMANAGER->focusFrameRender(this->_charaName + "_대기", getMemDC(), _MoveRc.left - 16,_MoveRc.top - 64, _status.forward, _status.currentFrame);
		break;
	case C_MOVE:
		IMAGEMANAGER->focusRender("그림자", getMemDC(), _MoveRc.left - 16, _MoveRc.top - 64);
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_이동", getMemDC(), _MoveRc.left - 16, _MoveRc.top - 64, _moveForward, _status.currentFrame);
		break;
	case C_MOVETEMPORARY:
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_준비", getMemDC(), MAPDATA->getTileData(_tempX, _tempY)->rc.left - 16, MAPDATA->getTileData(_tempX, _tempY)->rc.top - 64, _tempForward, _status.currentFrame);//거리정보가나오고 일시적으로 캐릭터가 움직였을경우에 무브 템포러리.
		if (STATEMANAGER->getState() == B_SELECTFORWARD)
		{
			IMAGEMANAGER->focusFrameRender("방향", getMemDC(), MAPDATA->getTileData(_tempX, _tempY)->rc.left - 16, MAPDATA->getTileData(_tempX, _tempY)->rc.top - 64, _tempForward, _status.currentFrame);
		}
		break;
	case C_JUMPUP:
		//IMAGEMANAGER->focusFrameRender(this->_charaName + "_점프", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_점프", getMemDC(), _MoveRc.left - 16, _MoveRc.top - 64, _moveForward, _status.currentFrame);
		break;
	case C_JUMPDOWN:
		//IMAGEMANAGER->focusFrameRender(this->_charaName + "_점프", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_점프", getMemDC(), _MoveRc.left - 16, _MoveRc.top - 64, _moveForward, _status.currentFrame);
		break;
	case C_ATTACK:
		IMAGEMANAGER->focusRender("그림자", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64);
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_공격", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		break;
	case C_SKILL1:
		IMAGEMANAGER->focusRender("그림자", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64);
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_스킬1", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		break;
	case C_SKILL2:
		IMAGEMANAGER->focusRender("그림자", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64);
		if (_charaName == "카린")
		{
			IMAGEMANAGER->focusFrameRender(this->_charaName + "_스킬2", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		}
		else if (_charaName == "아리스")
		{
			IMAGEMANAGER->focusFrameRender(this->_charaName + "_스킬1", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		}
		break;
	case C_SKILL3:
		IMAGEMANAGER->focusRender("그림자", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64);
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_스킬3", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		break;
	case C_DEMAGED:
		IMAGEMANAGER->focusRender("그림자", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64);
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_피격", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		break;
	case C_GUARD:
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_가드", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		break;
	case C_MISS:
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_회피", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		break;
	case C_FREEZE:
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_빙결", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		break;
	case C_PETRIFICATION:
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_석화", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		break;
	case C_STUN:
		IMAGEMANAGER->focusRender("그림자", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64);
		IMAGEMANAGER->focusFrameRender(this->_charaName + "_기절", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
		IMAGEMANAGER->focusFrameRender("기절", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left - 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64, _status.forward, _status.currentFrame);
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
		//X, I가 좌우
		//Y, J가 앞뒤
		if (!(_MoveRc.left == MAPDATA->getTileData(_targetPoint.x, _targetPoint.y)->rc.left &&
			_MoveRc.top == MAPDATA->getTileData(_targetPoint.x, _targetPoint.y)->rc.top))
		{

			_moveCount++;
			if (_MovePoint.x == 1)//우
			{
				_moveForward = 3;
				_MoveRc = RectMake(_MoveRc.left + 4, _MoveRc.top + 2, TILEWIDTH, TILEHEIGHT);
			}
			else if (_MovePoint.x == -1)//좌
			{
				_moveForward = 2;
				_MoveRc = RectMake(_MoveRc.left - 4, _MoveRc.top - 2, TILEWIDTH, TILEHEIGHT);
			}
			else if (_MovePoint.y == 1)//뒤
			{
				_moveForward = 1;
				_MoveRc = RectMake(_MoveRc.left - 4, _MoveRc.top + 2, TILEWIDTH, TILEHEIGHT);
			}
			else if (_MovePoint.y == -1)//앞
			{
				_moveForward = 0;
				_MoveRc = RectMake(_MoveRc.left + 4, _MoveRc.top - 2, TILEWIDTH, TILEHEIGHT);
			}
			//절반지점에서 한번 해줌.

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
			//한칸 이동 완료
			_status.forward = _tempForward;
			_moveOn = false;
		}
	}
}

void character::jumpUp()
{
	//32z값을 32만큼 높이면 됨.

	//8프레임 만에 변화시켜보자.

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
		//점프 하자~
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
		//올라갔다 내려가자~
		_MoveRc = RectMake(_MoveRc.left, _MoveRc.top + 4, TILEWIDTH, TILEHEIGHT);
		if (_status.count % 4 == 0 && _status.count != 0)
		{
			_status.currentFrame++;
			_status.count = 0;
		}
		//떨어지는 순간에 인덱스 이동.
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
			_state = C_MOVE;//이상태로는 안된다. 다시 점프가 시작되어 버림. movecount가 8이면 점프하고 다시 8부터 16까지 움직인다. 점프시 z값만 바꾼다....
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
		//점프 하자~
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
		//올라갔다 내려가자~
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
			_state = C_MOVE;//이상태로는 안된다. 다시 점프가 시작되어 버림. movecount가 8이면 점프하고 다시 8부터 16까지 움직인다. 점프시 z값만 바꾼다....
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
		_numberUpUp = 32 * sinf(22.5 * M_RAD * _numberFrame);//이부분이 좀 불안
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
			if (hund == 0)//100의 자리 없음
			{
				if (ten == 0)//1의 자리 출력
				{
					IMAGEMANAGER->focusFrameRender("숫자폰트2", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 24, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, one);
					//Rectangle(hdc, MAPDATA->getTileData(_indexX, _indexY)->rc.left, MAPDATA->getTileData(_indexX, _indexY)->rc.top, MAPDATA->getTileData(_indexX, _indexY)->rc.right, MAPDATA->getTileData(_indexX, _indexY)->rc.bottom);
				}
				else//10의 자리 출력
				{
					IMAGEMANAGER->focusFrameRender("숫자폰트2", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, ten);
					IMAGEMANAGER->focusFrameRender("숫자폰트2", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 32, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, one);
				}
			}
			else//100의 자리 까지 출력
			{
				IMAGEMANAGER->focusFrameRender("숫자폰트2", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 8, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, hund);
				IMAGEMANAGER->focusFrameRender("숫자폰트2", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 24, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, ten);
				IMAGEMANAGER->focusFrameRender("숫자폰트2", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 40, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, one);
			}
		}
		else
		{
			if (hund == 0)//100의 자리 없음
			{
				if (ten == 0)//1의 자리 출력
				{
					IMAGEMANAGER->focusFrameRender("숫자폰트1", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 24, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, one);
					//Rectangle(hdc, MAPDATA->getTileData(_indexX, _indexY)->rc.left, MAPDATA->getTileData(_indexX, _indexY)->rc.top, MAPDATA->getTileData(_indexX, _indexY)->rc.right, MAPDATA->getTileData(_indexX, _indexY)->rc.bottom);
				}
				else//10의 자리 출력
				{
					IMAGEMANAGER->focusFrameRender("숫자폰트1", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 16, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, ten);
					IMAGEMANAGER->focusFrameRender("숫자폰트1", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 32, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, one);
				}
			}
			else//100의 자리 까지 출력
			{
				IMAGEMANAGER->focusFrameRender("숫자폰트1", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 8, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, hund);
				IMAGEMANAGER->focusFrameRender("숫자폰트1", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 24, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, ten);
				IMAGEMANAGER->focusFrameRender("숫자폰트1", getMemDC(), MAPDATA->getTileData(_indexX, _indexY)->rc.left + 40, MAPDATA->getTileData(_indexX, _indexY)->rc.top - 64 - _numberUpUp, _numberFrame, one);
			}
		}
	}



}

