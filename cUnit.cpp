#include "stdafx.h"
#include "cUnit.h"
#include "cUnitState.h"

cUnit::cUnit() : m_PosX(0), m_PosY(0)
{

}

cUnit::~cUnit()
{

}

HRESULT cUnit::init()
{
	return S_OK;
}

void cUnit::update()
{
	m_State->update();
}

void cUnit::render()
{
	m_State->render();
}

void cUnit::release()
{
	m_State->release();
	SAFE_DELETE(m_State);
}


/*

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
_openList.insertNode(&_map[_currentX - 1][_currentY]);
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
_openList.insertNode(&_map[_currentX + 1][_currentY]);
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
_openList.insertNode(&_map[_currentX][_currentY - 1]);
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
_openList.insertNode(&_map[_currentX][_currentY + 1]);
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
//for (int i = 0; i < _openList.size(); i++)
//{	//F = G + H
//	_openList[i]->AstarF = _openList[i]->AstarH + _openList[i]->AstarG;
//}
}

void F_MAPDATA::selectNext()
{
if (_openList.isEmpty())
{
_isNoWay = true;
return;
}

tagFarTile* minNode = _openList.popRootNode();

_closeList.push_back(minNode);
_closeIndex++;

if (_closeList[_closeIndex]->idx.x == _endX && _closeList[_closeIndex]->idx.y == _endY)
{
_isFind = true;
return;
}
return;
}


*/