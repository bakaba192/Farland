#pragma once
#include "gameNode.h"

struct MonsterStatus {

	int lv;

	int hp;
	int maxHp;

	int mp;
	int maxMp;

	int def;

	int attack;

	int mAttack;

	int moveLimit;

	int forward;			//보고있는방향 0~3 0앞 1뒤 2좌 3우
	int moveForward;
	int currentFrame;		//현재 프레임

	int count;

	int range;				//공격범위
	
	bool isReadyToBehavior;
	bool isReadyToMove;
};


enum MonsterState {
	M_READY = 0,
	M_MOVE,
	M_ATTACK,
	M_JUMPUP,
	M_JUMPDOWN,
	M_DEMAGED,
	M_DEATH
};

enum MonsterName {
	MN_HYDRA = 0,
	MN_JACO1,
};

class F_monster : public gameNode
{
private:

	MonsterName _mName;
	string _name;

	MonsterStatus _mStatus;
	MonsterState _mState;
	MonsterState _mPreState;

	int _indexX;
	int _indexY;

	//int _tempX;						//캐릭터가 일시적으로 표시될 위치의 x y값
	//int _tempY;

	int _tempForward;				//임시적으로 캐릭터가 가질 방향

	int _alpha;

	bool _moveOn;

	int _moveCount;					//이동의 절반지점을 찾는 카운터
	int _jumpCount;					//점프이동에 사용할 카운터

	int _moveLimitCount;

	vector<POINT> _way;

	RECT _MoveRc;

	POINT _MovePoint;

	POINT _targetPoint;

	int _repeatCount;				//몇번 반복할 것인가?

	int _numberFrame;
	int _numberCount;
	int _numberUpUp;

	int hund;
	int ten;
	int one;

	bool isOnPrintDemage;

	bool _onAttack;

public:
	F_monster() {};
	~F_monster() {};

	HRESULT init(int x, int y, MonsterName name, int lv);
	void release(void);
	void update(void);
	void render(void);

	MonsterStatus& getMStatus() { return _mStatus; }
	MonsterState& getMState() { return _mState; }

	int& getPosX() { return _indexX; }
	int& getPosY() { return _indexY; }/*
	int& getTempPosX() { return _tempX; }
	int& getTempPosY() { return _tempY; }

	void setTempPos(int i, int j) { _tempX = i, _tempY = j; }*/
	
	vector<POINT>& getStack() { return _way; }

	void setWayStack(vector<POINT>& way) { _way = way; }

	void behaviorByState();//상태값에 따른 행동
						   //값에 따른 상태변화
						   
	void stateChange();
	void showCharaByState();
	void moveToWay();
	void jumpUp();
	void jumpDown();

	bool printDemage(int Demage);

	void DemageRender();

	int getAlpha() { return _alpha; }

	string getName() { return _name; }

	MonsterName& getMName() { return _mName; }

	bool& getOnAttack() { return _onAttack; }

	RECT getMoveRc() { return _MoveRc; }


};

