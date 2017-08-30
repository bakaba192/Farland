#pragma once

enum charaState  //애니메이션 상태
{
	C_READY = 0,
	C_STAY,
	C_MOVE,
	C_MOVETEMPORARY,//임시적으로 움직인상태
	C_JUMPUP,
	C_JUMPDOWN,
	C_ATTACK,
	C_SKILL1,
	C_SKILL2,
	C_SKILL3,
	C_DEMAGED,
	C_GUARD,
	C_MISS,
	C_FREEZE,
	C_PETRIFICATION,
	C_STUN
};

enum CharaName
{
	N_KARIN = 0,
	N_ARIS,
	N_AL
};

struct tagCharaStatus
{
	int lv;

	int hp;
	int maxHp;

	int mp;
	int maxMp;

	int attack;

	int mAttack;

	int def;

	int moveLimit;

	bool isReadyToBehavior;
	bool isReadyToMove;

	int forward;					//보고있는방향 0~3 0앞 1뒤 2좌 3우
	int currentFrame;		//현재 프레임

	int count;

	int range;

	int Exp;
};
