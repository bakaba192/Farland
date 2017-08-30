#pragma once

enum charaState  //�ִϸ��̼� ����
{
	C_READY = 0,
	C_STAY,
	C_MOVE,
	C_MOVETEMPORARY,//�ӽ������� �����λ���
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

	int forward;					//�����ִ¹��� 0~3 0�� 1�� 2�� 3��
	int currentFrame;		//���� ������

	int count;

	int range;

	int Exp;
};
