#pragma once
#include "gameNode.h"

#define TileWidth 64
#define TileHeight 32

#define TileMAX 30


//Ÿ�ϸ��� ����
//posX posY Height�� �⺻���� ������.
//IsoX �� IsoY�� posX posY Height�� ���� �����ȴ�.
//�׸��� IsoX�� IsoY�� ���� �׷�����.
//x+y�� ���� ���ĵȴ�.

//ĳ���ʹ� x+y�϶� Ÿ���� �� �׸��� �׸���.
//�������� x+y��ŭ ��ȸ�Ѵ�. -> �ʹ������ʳ�?

/*
z������ ������ �׸��� ��ȸ
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

