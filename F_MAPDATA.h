#pragma once
#include "FarMapTile.h"
#include "singletonBase.h"
#include "cHeap.h"


//맵의 데이터를 관리하는 클래스.
class F_MAPDATA : public singletonBase<F_MAPDATA>
{
private:
	tagFarTile _map[TILEMAXI][TILEMAXJ];

	int _pickI;
	int _pickJ;

	int _startX;
	int _startY;

	int _endX;
	int _endY;

	int _stageNumber;

	vector<POINT> _vecRange;

	cHeap<tagFarTile> _openList;
	list<tagFarTile*> _closeList;

public:
	F_MAPDATA() {};
	~F_MAPDATA() {};

	HRESULT init(void);
	void release(void);

	int getStartX() { return _startX; }
	int getStartY() { return _startY; }

	int getEndX() { return _endX; }
	int getEndY() { return _endY; }

	inline tagFarTile* getTileData(int i, int j) { return &_map[i][j]; }; //타일 하나의 데이터에 접근가능.

	void setPick(int i, int j) { _pickI = i, _pickJ = j; }

	int getPickI() { return _pickI; }
	int getPickJ() { return _pickJ; }

	int& getStageNumber() { return _stageNumber; }

public:

	void showMoveRange(int i, int j, int range);

	void showSkillrange(int x, int y, int range, bool isHeal = false);


	void unShowRange();

	void initAstar(int startX, int startY, int destX, int destY);

	vector<POINT> Astar();

	void pickTile();

	void loadMap(int i);

};