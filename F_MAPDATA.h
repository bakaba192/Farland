#pragma once
#include "FarMapTile.h"
#include "singletonBase.h"
#include <stack>

//���� �����͸� �����ϴ� Ŭ����.
#define BLINE 10

class F_MAPDATA : public singletonBase<F_MAPDATA>
{
private:
	tagFarTile _map[TILEMAXI][TILEMAXJ];

	int _pickI;
	int _pickJ;

	int _lastIdx;

	int _startX;
	int _startY;

	int _endX;
	int _endY;

	int _currentX;
	int _currentY;
	int _currentG;

	int _closeIndex;

	bool _isFind;
	bool _isNoWay;

	//vector<tagFarTile>* _vRoad;	//��θ� ���� ����
	//vector<tagFarTile>* _vOpenList;	//
	//vector<tagFarTile>* _vCloseList;//

	int _stageNumber;

	vector<POINT> _roadStack;
	vector<POINT> _rangeStack;
	vector<tagFarTile*> _openList;
	vector<tagFarTile*> _closeList;

public:

	F_MAPDATA() {};
	~F_MAPDATA() {};

	HRESULT init(void);
	void release(void);

	int getStartX() { return _startX; }
	int getStartY() { return _startY; }

	int getEndX() { return _endX; }
	int getEndY() { return _endY; }

	inline tagFarTile* getTileData(int i, int j) { return &_map[i][j]; }; //Ÿ�� �ϳ��� �����Ϳ� ���ٰ���.

	void showMoveRange(int i, int j, int range);

	void showSkillrange(int x, int y, int range, bool isHeal = false);


	void unShowRange();

	//void showAroundEnemy(int i, int j);

	void initAstar(int startX, int startY, int destX, int destY);

	vector<POINT> Astar();
/*
	void AstarStart();
*/
	void setPick(int i, int j) { _pickI = i, _pickJ = j; }

	int getPickI() { return _pickI; }
	int getPickJ() { return _pickJ; }

	//vector<tagFarTile>* getRoadVector() { return _vRoad; }

	void calculateH();

	void calculateF();

	void selectNext();

	void loadMap(int i);

	int& getStageNumber() { return _stageNumber; }
};