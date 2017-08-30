#pragma once
#include "stdafx.h"

#define TILEWIDTH 64
#define TILEHEIGHT 32

#define TILEMAXI 30
#define TILEMAXJ 30

enum T_SELECT
{
	S_NONE = 0,
	S_TRUE1,
	S_TRUE2,
	S_FALSE1,
	S_FALSE2
};

enum CLASSIFY
{
	CL_NONE = 0,
	CL_FRIEND,
	CL_ENEMY,
	CL_OBJECT
};

enum TILETYPE
{
	T_BLANK = 0,
	T_GRASS,
	T_ROCK,
	T_SNOW
};

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


struct tagFarTile
{
	POINT idx;

	//저장되어야 하는 값들
	int x, y;				//타일(rect)의 left,top

	int z;					//타일의 Z오더

	TILETYPE tileT;			//그릴 타일의 종류

	OBJECT1 objIndex1;
	OBJECT2 objIndex2;

	int objectZ;			//오브젝트가 위치함으로써 생기는 추가적인 z오더

							//저장되지 않아도 되는 값들.
	int pivotX, pivotY;		//타일 중점

	T_SELECT tSELECT;

	POINT poly[4];			//폴리곤을 이룰 리전(region)
	RECT rc;				//타일의 렉트

	CLASSIFY classify;

	int AstarH;
	int AstarG;
	int AstarF;

	bool isOpen;

	bool isOpenList;

	bool isEnemy;

	tagFarTile* parentNode;
};