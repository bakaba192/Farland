#include "stdafx.h"
#include "F_MAPDATA.h"

HRESULT F_MAPDATA::init(void)
{
	_pickI = 0;
	_pickJ = 0;

	MAPDATA->setPick(0, 0);
	
	//_stageNumber = 1;

	//loadMap(_stageNumber);

	FOCUSMANAGER->setBound(-TILEMAXJ * TILEWIDTH/2, TILEMAXJ * TILEWIDTH / 2, -(TILEMAXI)*TILEHEIGHT/2 - WINSIZEY/2, WINSIZEY/2 - TILEHEIGHT);

	return S_OK;
}

void F_MAPDATA::release(void)
{

}

void F_MAPDATA::showMoveRange(int x, int y, int range)
{
	for (int i = 0; i < TILEMAXI; i++)
	{
		for (int j = 0; j < TILEMAXJ; j++)
		{
			if (i == x && j == y)
			{
				_map[i][j].tSELECT = S_TRUE2;
			}

			if (abs(x - i) + abs(y - j) <= range)
			{
				this->initAstar(x, y, i, j);

				while (!_rangeStack.empty())
				{
					_rangeStack.pop_back();
				}

				_rangeStack = this->Astar();

				if (_rangeStack.size() != 0 && _rangeStack.size() <= range)
				{
					_map[i][j].tSELECT = S_TRUE2;
				}
			}
		}
	}
}

void F_MAPDATA::showSkillrange(int x, int y, int range, bool isHeal)
{
	if (!isHeal)
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
	for (int i = 0; i < TILEMAXI; i++)
	{
		for (int j = 0; j < TILEMAXJ; j++)
		{
			_map[i][j].idx.x = i;
			_map[i][j].idx.y = j;
			_map[i][j].AstarF = 0;
			_map[i][j].AstarH = 0;
			_map[i][j].AstarG = 0;

			//_map[i][j].isOpen = true;
			_map[i][j].isOpenList = false;

			_map[i][j].parentNode = nullptr;
		}
	}
	_isFind = false;
	_isNoWay = false;

	_startX = startX;
	_startY = startY;

	_endX = destX;
	_endY = destY;

	//우선 벡터에 경로를 담은후 빼면서 넣는다

	_closeIndex = 0;

	_currentX = _startX;
	_currentY = _startY;
	_currentG = 0;

	while (!_roadStack.empty())
	{
		_roadStack.pop_back();
	}
	_closeList.clear();
	_openList.clear();


	_closeList.push_back(&_map[_currentX][_currentY]);
	_closeList[_closeIndex]->isOpen = false;//오픈리스트에 있는가?

}

vector<POINT> F_MAPDATA::Astar()
{
	while (true)
	{
		_currentX = _closeList[_closeIndex]->idx.x;
		_currentY = _closeList[_closeIndex]->idx.y;
		_currentG = _closeList[_closeIndex]->AstarG;

		if (_currentX > 0)
		{
			if (_map[_currentX - 1][_currentY].isOpen)
			{
				if (!_map[_currentX - 1][_currentY].isOpenList &&
					abs(_map[_currentX][_currentY].z - _map[_currentX - 1][_currentY].z) < 3)
				{
					_map[_currentX - 1][_currentY].isOpenList = true;
					_map[_currentX - 1][_currentY].AstarG = _currentG + BLINE;
					_map[_currentX - 1][_currentY].parentNode = _closeList[_closeIndex];
					_openList.push_back(&_map[_currentX - 1][_currentY]);
				}
				else
				{
					if (_currentG + BLINE < _map[_currentX - 1][_currentY].AstarG
						&& abs(_map[_currentX][_currentY].z - _map[_currentX - 1][_currentY].z) < 3)
					{
						_map[_currentX - 1][_currentY].AstarG = _currentG + BLINE;
						_map[_currentX - 1][_currentY].parentNode = _closeList[_closeIndex];
					}
				}
			}
		}

		if (_currentX < TILEMAXI - 1)
		{
			if (_map[_currentX + 1][_currentY].isOpen)
			{
				if (!_map[_currentX + 1][_currentY].isOpenList &&
					abs(_map[_currentX][_currentY].z - _map[_currentX + 1][_currentY].z) < 3)
				{
					_map[_currentX + 1][_currentY].isOpenList = true;
					_map[_currentX + 1][_currentY].AstarG = _currentG + BLINE;
					_map[_currentX + 1][_currentY].parentNode = _closeList[_closeIndex];
					_openList.push_back(&_map[_currentX + 1][_currentY]);
				}
				else
				{
					if (_currentG + BLINE < _map[_currentX + 1][_currentY].AstarG &&
						abs(_map[_currentX][_currentY].z - _map[_currentX & 1][_currentY].z) < 3)
					{
						_map[_currentX + 1][_currentY].AstarG = _currentG + BLINE;
						_map[_currentX + 1][_currentY].parentNode = _closeList[_closeIndex];
					}
				}
			}
		}

		if (_currentY > 0)
		{
			if (_map[_currentX][_currentY - 1].isOpen)
			{
				if (!_map[_currentX][_currentY - 1].isOpenList &&
					abs(_map[_currentX][_currentY].z - _map[_currentX][_currentY - 1].z) < 3)
				{
					_map[_currentX][_currentY - 1].isOpenList = true;
					_map[_currentX][_currentY - 1].AstarG = _currentG + BLINE;
					_map[_currentX][_currentY - 1].parentNode = _closeList[_closeIndex];
					_openList.push_back(&_map[_currentX][_currentY - 1]);
				}
				else
				{
					if (_currentG + BLINE < _map[_currentX][_currentY - 1].AstarG &&
						abs(_map[_currentX][_currentY].z - _map[_currentX][_currentY - 1].z) < 3)
					{
						_map[_currentX][_currentY - 1].AstarG = _currentG + BLINE;
						_map[_currentX][_currentY - 1].parentNode = _closeList[_closeIndex];
					}
				}
			}
		}

		if (_currentY < TILEMAXI - 1)
		{
			if (_map[_currentX][_currentY + 1].isOpen)
			{
				if (!_map[_currentX][_currentY + 1].isOpenList &&
					abs(_map[_currentX][_currentY].z - _map[_currentX][_currentY + 1].z) < 3)
				{
					_map[_currentX][_currentY + 1].isOpenList = true;
					_map[_currentX][_currentY + 1].AstarG = _currentG + BLINE;
					_map[_currentX][_currentY + 1].parentNode = _closeList[_closeIndex];
					_openList.push_back(&_map[_currentX][_currentY + 1]);
				}
				else
				{
					if (_currentG + BLINE < _map[_currentX][_currentY + 1].AstarG &&
						abs(_map[_currentX][_currentY].z - _map[_currentX][_currentY + 1].z) < 3)
					{
						_map[_currentX][_currentY + 1].AstarG = _currentG + BLINE;
						_map[_currentX][_currentY + 1].parentNode = _closeList[_closeIndex];
					}
				}
			}
		}

		calculateH();
		calculateF();
		selectNext();

		if (_isNoWay)
		{
			while (!_roadStack.empty())
			{
				_roadStack.pop_back();
			}
			return _roadStack;
		}

		if (_isFind)
		{
			POINT temp = { 0,0 };
			tagFarTile* tempTile = _closeList[_closeIndex];

			while (true)
			{

				temp.x = (tempTile->idx.x - tempTile->parentNode->idx.x);
				temp.y = (tempTile->idx.y - tempTile->parentNode->idx.y);


				_roadStack.push_back(temp); // (0,1)/(1,0)/(0,-1)/(-1,0)

				tempTile = tempTile->parentNode;

				if (tempTile->parentNode == nullptr)
				{
					return _roadStack;
				}
			}
		}
	}
}

void F_MAPDATA::calculateH()

{
	for (int i = 0; i < _openList.size(); i++)
	{
		int v = (_endX - _openList[i]->idx.x) * BLINE;
		int h = (_endY - _openList[i]->idx.y) * BLINE;

		_openList[i]->AstarH = abs(v) + abs(h);
	}
}

void F_MAPDATA::calculateF()
{
	for (int i = 0; i < _openList.size(); i++)
	{	//F = G + H
		_openList[i]->AstarF = _openList[i]->AstarH + _openList[i]->AstarG;
	}
}

void F_MAPDATA::selectNext()
{
	if (_openList.size() == 0)
	{
		_isNoWay = true;
		return;
	}

	int minimum = 5000;
	int index;

	for (int i = 0; i < _openList.size(); i++)
	{	//F = G + H
		if (_openList[i]->AstarF < minimum)
		{
			minimum = _openList[i]->AstarF;
			index = i;
		}
	}


	_closeList.push_back(_openList[index]);
	_closeIndex++;
	_openList.erase(_openList.begin() + index);

	if (_closeList[_closeIndex]->idx.x == _endX && _closeList[_closeIndex]->idx.y == _endY)
	{
		_isFind = true;
		return;
	}
	return;
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
			if (_map[i][j].objIndex2 == OBJ2_NULL)
			{
				_map[i][j].isOpen = true;
			}
			else
			{
				_map[i][j].isOpen = false;
			}
		}
	}
}
