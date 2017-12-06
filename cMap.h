#pragma once
#include "gameNode.h"

#define TileWidth 64
#define TileHeight 32

#define TileMAX 30


//타일맵의 구성
//posX posY Height를 기본으로 가진다.
//IsoX 와 IsoY가 posX posY Height에 의해 결정된다.
//그릴때 IsoX와 IsoY에 의해 그려진다.
//x+y에 의해 정렬된다.

//캐릭터는 x+y일때 타일을 다 그리고 그린다.
//렌더링시 x+y만큼 순회한다. -> 너무많지않나?

/*
z오더가 있을때 그리기 순회
*/

struct ST_TILE
{
	int x;
	int y;

	int Height;

	int isoX;
	int isoY;

	int F;
	int G;
	int H;

	WAYSTATE state;
	TILETYPE type;

	OBJ1 obj1;
	OBJ2 obj2;
	OBJ3 obj3;

	bool operator< (const ST_TILE& anotherTile)
	{
		if (this->F < anotherTile.F)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator> (const ST_TILE& anotherTile)
	{
		if (this->F > anotherTile.F)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class cMap : public gameNode
{
private:
	ST_TILE m_Map[TileMAX][TileMAX];

	cHeap<ST_TILE> m_OpenList;

public:
	cMap();
	~cMap();




	void InitAstar();



	inline ST_TILE& getTile(int i, int j) { return m_Map[i][j]; }
};

