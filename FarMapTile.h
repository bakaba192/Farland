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

//NONBLOCK 오브젝트
enum OBJ1
{
	OB1_EMPTY = 0,
	OB1_GRASS1,
	OB1_GRASS2,
	OB1_GRASS3,
	OB1_GRASS4,
	OB1_GRASS5,
};

//Height오브젝트
enum OBJ2
{
	OB2_EMPTY = 0,
	OB2_PANEL1,
	OB2_PANEL2,
	OB2_BOX1,
	OB2_BOX2,
	OB2_DRUM
};

//BLOCK 오브젝트 -> 이 오브젝트가 Empty가 아니면 WAYstate가 block이 된다.
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
//폐기예정
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
	//저장되어야 하는 값들
	int x, y;				//타일(rect)의 left,top

	int z;					//타일의 높이값

	int objectZ;			//오브젝트가 위치함으로써 생기는 추가적인 높이값

	TILETYPE tileT;			//그릴 타일의 종류
	TILESELECT tSELECT;		//타일선택 상태
	CLASSIFY classify;		//타일위에 놓여인는 오브젝트(유닛,논유닛) 종류
	OBJECT1 objIndex1;		//비충돌 오브젝트
	OBJECT2 objIndex2;		//충돌 오브젝트

public:
	POINT idx;				//타일의 인덱스

	tagFarTile* parentNode;	//타일의 부모노드

	int pivotX, pivotY;		//타일 중점

	int AstarH;
	int AstarG;
	int AstarF;

	POINT poly[4];			//폴리곤을 이룰 리전(region)
	RECT rc;				//타일의 렉트

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