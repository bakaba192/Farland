#pragma once
#include "gameNode.h"
#include "FarMapTile.h"
#include "stageMap.h"
class F_TileMapTool : public gameNode
{
private:
	int drawCase;

	tagFarTile _Ftiles[TILEMAXI][TILEMAXJ];

	int _FocusX;
	int _FocusY;

	image* _temp;

	int _x = 0;
	int _y = 0;

	int _selectedTileType;

	bool _search[4];

	//int _pickI;
	//int _pickJ;

	TILETYPE _selectedTile;

	OBJECT2 _selectedObject;

	stageMap* _map;

	RECT _clipingRc;

	RECT _boundRect;

	RECT _UIrect;

	RECT _stageNumberRc;
	RECT _stageArrowLeftRc;
	RECT _stageArrowRightRc;

	RECT _UItileRc;
	RECT _tileArrowLeftRc;
	RECT _tileArrowRightRc;

	RECT _UIobjectRc;
	RECT _objectArrowLeftRc;
	RECT _objectArrowRightRc;

	RECT _saveBtnRc;
	RECT _loadBtnRc;

	bool _isFolding;//접혀있다.

	bool _UIgoLeft;//ui를 왼쪽으로 꺼내와라.
	bool _UIgoRight;

	vector<character*> _vChara;
	vector<F_monster*> _vMonster;

	int _unitLv;
	

public:
	F_TileMapTool() {}
	~F_TileMapTool() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	void setTilePosUpdate();
	void pickTile();
	void setTileType();
	void setTile_Z_Order();
	void setObject();
	void drawMap();
	void showTile(int i , int j);
	void showSelectedTile();
	void searchInit();
	void saveAndLoad(int stageNumber);
	void showObject(int i, int j);

//	int& getStageNumber() { return _stageNumber; }

	void UIcontrol();

	void UIrender();
	void setUIpos();
	void UIDrag();
};