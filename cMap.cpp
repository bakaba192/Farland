#include "stdafx.h"
#include "cMap.h"


cMap::cMap()
{
	//����
	for (int i = 0; i < TileMAX; i++)
	{
		//j�� ����
		for (int j = 0; j < TileMAX; j++)
		{
			memset(&m_Map[i][j],0,sizeof(ST_TILE));
		}
	}
}


cMap::~cMap()
{
}

void cMap::InitAstar()
{
}
