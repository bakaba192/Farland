#pragma once
#include "gameNode.h"
#include "FarMapTile.h"
#include "stageMap.h"
#include "character.h"
#include "F_monster.h"
#include "stateBar.h"

class stageScene : public gameNode
{
private:
	image* _backGround[3];

	bool _gameStart;

	bool _isShowStateWindow;

	bool _showTurn;

	bool _turnSwitch;
	int _turnSwitchCount;

	int _turnCount;

	int _saveSlot;

	string _charaStateName;
	int _charaStateLevel;

	RECT _charaStateRect;

	stateBar* _hpBar;
	stateBar* _mpBar;

	stateBar* _ExpBar;

	RECT _clipingRc;

	stageMap* _map;

	/*character* _karin;
	character* _aris;
	character* _al;


	F_monster* _minion;
	F_monster* _minion2;
	F_monster* _minion3;*/

	character* _selectedChara;
	F_monster* _selectedMonster;

	character* _healTarget;


	vector<character*> _vCharacter;
	vector<F_monster*> _vMonster;

	int _tempCount;
	int _tempFrame;

	int _alpha; //씬 체인지용 알파값.

	bool _isVictory;
	int _VictoryAlpha;

	bool _isDefeat;

	bool _dark;

	bool _isSceneChange; //씬 체인지 시작됬는가?
	int _SceneChangeAlPha;
	
	int _gainExp;
	int _totalExp;//이번 턴에 얻는 토탈 경험치. 한 캐릭터당 0으로 만든다. 이걸 씬에서처리할까?
	bool _isLvUp;

	int _deleyCount;

public:
	stageScene() {};
	~stageScene() {};

	HRESULT init();
	void release(void);
	void update(void);
	void render(void);

	void playerBehavior();//상태에 따른 플레이어의 행동

	bool showMeleeAttackRange(int i, int j);
	void showCharaState();

	void stageSave();
	void stageLoad();
	void stageInitialize();
	void WinLose();


	//경험치게이지가 gain만큼 올라가는 도중이면 true.
	bool gainExp();

	//void vectorinitialize();
};

