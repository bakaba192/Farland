#pragma once
#include "gameNode.h"
#include "FarMapTile.h"
#include "character.h"

class stageMap : public gameNode
{
private:
	bool _search[4];

	//selectedCharacter
	//selectedSkill

	image* _background;

	

	int x;
	int y;

	RECT rc;

public:
	stageMap() {}
	~stageMap() {}


	HRESULT init();
	void release(void);
	void update(void);
	void render(void);

	//void drawMap();

	void setTilePosUpdate();

	void showBlock(int i, int j);

	void showTile(int i, int j);

	void showObject(int i, int j);

	void showSelectedTile();

	void pickTile();

	void searchInit();
	
	void showRange(int i, int j);

	//vector<character>* getVChara() { return &_vCharacter; }

	//vector<monster>* getVMonster() { return &_vMonster; }
	


};

