#pragma once
#include "stdafx.h"

#define TILEWIDTH 64
#define TILEHEIGHT 32

#define TILEMAXI 30
#define TILEMAXJ 30



//======

enum TILESELECT
{
	S_NONE = 0,
	S_TRUE1,
	S_TRUE2,
	S_FALSE1,
	S_FALSE2
};

enum WAYSTATE
{
	WAY_EMPTY = 0,
	WAY_BLOCK,
	WAY_OPEN,
	WAY_CLOSE
};

enum TILETYPE
{
	T_BLANK = 0,
	T_GRASS,
	T_ROCK,
	T_SNOW
};

//NONBLOCK ������Ʈ
enum OBJ1
{
	OB1_EMPTY = 0,
	OB1_GRASS1,
	OB1_GRASS2,
	OB1_GRASS3,
	OB1_GRASS4,
	OB1_GRASS5,
};

//Height������Ʈ
enum OBJ2
{
	OB2_EMPTY = 0,
	OB2_PANEL1,
	OB2_PANEL2,
	OB2_BOX1,
	OB2_BOX2,
	OB2_DRUM
};

//BLOCK ������Ʈ -> �� ������Ʈ�� Empty�� �ƴϸ� WAYstate�� block�� �ȴ�.
enum OBJ3
{
	OB3_EMPTY = 0,
	OB3_TREE1,
	OB3_TREE2,
	OB3_TREE3,
	OB3_SIGN1,
	OB3_SIGN2,
	OB3_SIGN3,
	OB3_SIGN4,
};

enum CLASSIFY
{
	CL_NONE = 0,
	CL_FRIEND,
	CL_ENEMY,
	CL_OBJECT
};

//=======
//��⿹��
enum OBJECT1
{
	OBJ1_GRASS1 = 0,
	OBJ1_GRASS2,
	OBJ1_GRASS3,
	OBJ1_GRASS4,
	OBJ1_GRASS5,
	OBJ1_PANEL1,
	OBJ1_PANEL2,
	OBJ1_BOX1,
	OBJ1_BOX2,
	OBJ1_DRUM,
	OBJ1_NULL
};

enum OBJECT2
{
	OBJ2_TREE1 = 0,
	OBJ2_TREE2,
	OBJ2_TREE3,
	OBJ2_SIGN1,
	OBJ2_SIGN2,
	OBJ2_SIGN3,
	OBJ2_SIGN4,
	OBJ2_NULL
};
//=======

struct tagFarTile
{
public:
	//����Ǿ�� �ϴ� ����
	int x, y;				//Ÿ��(rect)�� left,top

	int z;					//Ÿ���� ���̰�

	int objectZ;			//������Ʈ�� ��ġ�����ν� ����� �߰����� ���̰�

	TILETYPE tileT;			//�׸� Ÿ���� ����
	TILESELECT tSELECT;		//Ÿ�ϼ��� ����
	CLASSIFY classify;		//Ÿ������ �����δ� ������Ʈ(����,������) ����
	OBJECT1 objIndex1;		//���浹 ������Ʈ
	OBJECT2 objIndex2;		//�浹 ������Ʈ

public:
	POINT idx;				//Ÿ���� �ε���

	tagFarTile* parentNode;	//Ÿ���� �θ���

	int pivotX, pivotY;		//Ÿ�� ����

	int AstarH;
	int AstarG;
	int AstarF;

	POINT poly[4];			//�������� �̷� ����(region)
	RECT rc;				//Ÿ���� ��Ʈ

	WAYSTATE wayState;

public:

	bool operator< (const tagFarTile tile)
	{
		if (this->AstarF < tile.AstarF)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator<= (const tagFarTile tile)
	{
		if (this->AstarF <= tile.AstarF)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator> (const tagFarTile tile)
	{
		if (this->AstarF > tile.AstarF)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator>= (const tagFarTile tile)
	{
		if (this->AstarF >= tile.AstarF)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};