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

	int _alpha; //�� ü������ ���İ�.

	bool _isVictory;
	int _VictoryAlpha;

	bool _isDefeat;

	bool _dark;

	bool _isSceneChange; //�� ü���� ���ۉ�°�?
	int _SceneChangeAlPha;
	
	int _gainExp;
	int _totalExp;//�̹� �Ͽ� ��� ��Ż ����ġ. �� ĳ���ʹ� 0���� �����. �̰� ������ó���ұ�?
	bool _isLvUp;

	int _deleyCount;

public:
	stageScene() {};
	~stageScene() {};

	HRESULT init();
	void release(void);
	void update(void);
	void render(void);

	void playerBehavior();//���¿� ���� �÷��̾��� �ൿ

	bool showMeleeAttackRange(int i, int j);
	void showCharaState();

	void stageSave();
	void stageLoad();
	void stageInitialize();
	void WinLose();


	//����ġ�������� gain��ŭ �ö󰡴� �����̸� true.
	bool gainExp();

	//void vectorinitialize();
};

