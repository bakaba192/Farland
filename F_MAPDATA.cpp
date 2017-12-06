#include "stdafx.h"
#include "F_MAPDATA.h"


HRESULT F_MAPDATA::init(void)
{
	for (int i = 0; i < TILEMAXI; i++)
	{
		for (int j = 0; j < TILEMAXJ; j++)
		{
			memset(&_map[i][j], 0, sizeof(tagFarTile));

			_map[i][j].idx.x = i;
			_map[i][j].idx.y = j;
		}
	}

	_pickI = 27;
	_pickJ = 29;

	_startX = 0;
	_startY = 0;

	_endX = 0;
	_endY = 0;

	_vecRange.clear();
	_openList.clear();
	_closeList.clear();

	//_stageNumber = -1;

	MAPDATA->setPick(0, 0);

	//_stageNumber = 1;

	//loadMap(_stageNumber);

	FOCUSMANAGER->setBound(-TILEMAXJ * TILEWIDTH / 2, TILEMAXJ * TILEWIDTH / 2, -(TILEMAXI)*TILEHEIGHT / 2 - WINSIZEY / 2, WINSIZEY / 2 - TILEHEIGHT);

	return S_OK;
}

void F_MAPDATA::release(void)
{

}

void F_MAPDATA::showMoveRange(int x, int y, int range)
{
	for (int i = -range; i <= range; i++)
	{
		for (int j = -range; j <= range; j++)
		{
			int tx = x + i;
			int ty = y + j;
			
			if (abs(i) + abs(j) > range) continue;
			if (tx < 0 || tx >= TILEMAXI) continue;
			if (ty < 0 || ty >= TILEMAXJ) continue;
			if (_map[tx][ty].wayState == WAYSTATE::WAY_BLOCK) continue;

			if (tx == x && ty == y)
			{
				_map[tx][ty].tSELECT = S_TRUE2;
			}

			this->initAstar(x, y, tx, ty);
			_vecRange.clear();

			_vecRange = this->Astar();

			if (_vecRange.size() != 0 && _vecRange.size() <= range)
			{
				_map[tx][ty].tSELECT = S_TRUE2;
			}
		}
	}
}

void F_MAPDATA::showSkillrange(int x, int y, int range, bool isAttack)
{
	if (isAttack)
	{
		for (int i = 0; i < TILEMAXI; i++)
		{
			for (int j = 0; j < TILEMAXJ; j++)
			{

				if (abs(x - i) + abs(y - j) <= range)
				{
					_map[i][j].tSELECT = S_FALSE2;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < TILEMAXI; i++)
		{
			for (int j = 0; j < TILEMAXJ; j++)
			{

				if (abs(x - i) + abs(y - j) <= range)
				{
					_map[i][j].tSELECT = S_TRUE2;
				}
			}
		}
	}
}

void F_MAPDATA::unShowRange()
{
	for (int i = 0; i < TILEMAXI; i++)
	{
		for (int j = 0; j < TILEMAXJ; j++)
		{
			_map[i][j].tSELECT = S_NONE;
		}
	}
}

void F_MAPDATA::initAstar(int startX, int startY, int destX, int destY)
{
	_openList.clear();
	_closeList.clear();

	for (int i = 0; i < TILEMAXI; i++)
	{
		for (int j = 0; j < TILEMAXJ; j++)
		{

			_map[i][j].AstarH = abs(i - destX) + abs(j - destY);
			_map[i][j].AstarG = 0;
			_map[i][j].AstarF = _map[i][j].AstarH;

			_map[i][j].parentNode = nullptr;

			if (_map[i][j].wayState != WAYSTATE::WAY_BLOCK)
			{
				_map[i][j].wayState = WAYSTATE::WAY_EMPTY;
			}
		}
	}

	_startX = startX;
	_startY = startY;

	_endX = destX;
	_endY = destY;

	_openList.insertNode(&_map[startX][startY]);
	_map[startX][startY].wayState = WAYSTATE::WAY_OPEN; //오픈리스트에 들어감.
}

vector<POINT> F_MAPDATA::Astar()
{
	vector<POINT> vecBestWay;
	vecBestWay.clear();

	while (1)
	{
		//===============================성공검사=====================================//
		if (_openList.isEmpty())
		{
			vecBestWay.clear();
			break;
		}

		if (!_closeList.empty())
		{
			if (_closeList.back()->idx.x == _endX && _closeList.back()->idx.y == _endY)
			{
				POINT temp = { 0,0 };
				tagFarTile* tempTile = _closeList.back();
				
				if (_closeList.size() == 1)
				{
					temp.x = tempTile->idx.x - _startX;
					temp.x = tempTile->idx.y - _startY;
					vecBestWay.push_back(temp);
				}
				else
				{
					while (true)
					{
						temp.x = (tempTile->idx.x - tempTile->parentNode->idx.x);
						temp.y = (tempTile->idx.y - tempTile->parentNode->idx.y);

						vecBestWay.push_back(temp);

						tempTile = tempTile->parentNode;
						if (tempTile->parentNode == nullptr) break;
					}
				}
				break;
			}
		}
		//==============================================================================//

		//가장 유망한 노드를 오픈리스트에서 제거하고 클로즈리스트에 추가한다.
		tagFarTile* tempNode = _openList.popRootNode();
		tempNode->wayState = WAYSTATE::WAY_CLOSE;
		_closeList.push_back(tempNode);

		//오픈리스트를 확장한다.
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				int tx = tempNode->idx.x + i;
				int ty = tempNode->idx.y + j;

				if (i == 0 && j == 0) continue;	//현재 노드 검사 안함.
				if (abs(i) + abs(j) == 2) continue;//대각방향 검사 안함.
				if (tx < 0 || tx >= TILEMAXI) continue;
				if (ty < 0 || ty >= TILEMAXJ) continue;
				if (_map[tx][ty].wayState == WAYSTATE::WAY_BLOCK) continue;
				if (_map[tx][ty].wayState == WAYSTATE::WAY_CLOSE) continue;

				//오픈리스트에 없음.
				if (_map[tx][ty].wayState == WAYSTATE::WAY_EMPTY)
				{
					_map[tx][ty].AstarG = tempNode->AstarG + 1;
					_map[tx][ty].AstarF = _map[tx][ty].AstarG + _map[tx][ty].AstarH;
					_map[tx][ty].wayState = WAYSTATE::WAY_OPEN;
					_map[tx][ty].parentNode = tempNode;
					_openList.insertNode(&_map[tx][ty]);
					
				}
				else
				{
					//만약 새로운 부모가 더 낮은 F값을 갖게 한다면
					//F값을 갱신하고 부모를 바꾼다.
					if (_map[tx][ty].AstarG > tempNode->AstarG + 1)
					{
						_map[tx][ty].AstarG = tempNode->AstarG + 1;
						_map[tx][ty].AstarF = _map[tx][ty].AstarG + _map[tx][ty].AstarH;
						_map[tx][ty].parentNode = tempNode;
					}
				}
			}
		}
	}

	return vecBestWay;
}

void F_MAPDATA::loadMap(int i)
{
	vector<tagFarTile> v;

	string stage;

	stage = "ini/스테이지" + to_string(i);

	v = DATABASE->loadMapData(stage.c_str());

	for (int i = 0; i < TILEMAXI; i++)
	{
		for (int j = 0; j < TILEMAXI; j++)
		{
			if (i*TILEMAXI + j < v.size())
			{
				_map[i][j].z = v[i*TILEMAXI + j].z;
				_map[i][j].tileT = v[i*TILEMAXI + j].tileT;
				_map[i][j].objIndex1 = v[i*TILEMAXI + j].objIndex1;
				_map[i][j].objIndex2 = v[i*TILEMAXI + j].objIndex2;
			}
			else
			{
				_map[i][j].z = 1;
				_map[i][j].tileT = T_GRASS;
				_map[i][j].objIndex1 = OBJ1_NULL;
				_map[i][j].objIndex2 = OBJ2_NULL;
			}
			_map[i][j].x = WINSIZEX / 2 - TILEWIDTH / 2 + (TILEWIDTH / 2)*(i - j);
			_map[i][j].y = 50 - TILEHEIGHT / 2 + (TILEHEIGHT / 2) *(i + j);
			_map[i][j].pivotX = MAPDATA->getTileData(i, j)->x + TILEWIDTH / 2;
			_map[i][j].pivotY = MAPDATA->getTileData(i, j)->y + TILEHEIGHT / 2;
			_map[i][j].rc = RectMake(MAPDATA->getTileData(i, j)->x, MAPDATA->getTileData(i, j)->y - MAPDATA->getTileData(i, j)->z * 16, TILEWIDTH, TILEHEIGHT);
			_map[i][j].poly[0] = { MAPDATA->getTileData(i,j)->pivotX - TILEWIDTH / 2, MAPDATA->getTileData(i,j)->pivotY }; //left
			_map[i][j].poly[1] = { MAPDATA->getTileData(i,j)->pivotX, MAPDATA->getTileData(i,j)->pivotY - TILEHEIGHT / 2 }; //top
			_map[i][j].poly[2] = { MAPDATA->getTileData(i,j)->pivotX + TILEWIDTH / 2, MAPDATA->getTileData(i,j)->pivotY }; //right
			_map[i][j].poly[3] = { MAPDATA->getTileData(i,j)->pivotX, MAPDATA->getTileData(i,j)->pivotY + TILEHEIGHT / 2 }; //bottom
			_map[i][j].classify = CL_NONE;//거기에 무엇이 있는가?
			_map[i][j].tSELECT = S_NONE;//타일의 선택상태
			if (_map[i][j].objIndex2 != OBJ2_NULL)
			{
				_map[i][j].wayState = WAYSTATE::WAY_BLOCK;
			}
		}
	}
}
