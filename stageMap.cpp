#include "stdafx.h"
#include "stageMap.h"


HRESULT stageMap::init()
{
	MAPDATA->setPick(0, 0);

	searchInit();

	x = 0;
	y = 0;

	MAPDATA->loadMap(MAPDATA->getStageNumber());

	return S_OK;
}

void stageMap::release(void)
{
}

void stageMap::update(void)
{
	FOCUSMANAGER->FocusByMouse();

	//pickTile();

	MAPDATA->pickTile();

	//setTilePosUpdate();
}

void stageMap::render(void)
{
}

void stageMap::setTilePosUpdate()
{
	for (int i = 0; i < TILEMAXI; i++)
	{
		for (int j = 0; j < TILEMAXJ; j++)
		{
			/*MAPDATA->getTileData(i,j)->x = WINSIZEX / 2 - TILEWIDTH / 2 + (TILEWIDTH / 2)*(i - j) + FOCUSMANAGER->getFocusX();
			MAPDATA->getTileData(i,j)->y = 50 - TILEHEIGHT / 2 + (TILEHEIGHT / 2) *(i + j) + FOCUSMANAGER->getFocusY();
			MAPDATA->getTileData(i,j)->pivotX = MAPDATA->getTileData(i,j)->x + TILEWIDTH / 2;
			MAPDATA->getTileData(i,j)->pivotY = MAPDATA->getTileData(i,j)->y + TILEHEIGHT / 2;*/

			//MAPDATA->getTileData(i, j)->rc = RectMake(MAPDATA->getTileData(i, j)->x,
			//	MAPDATA->getTileData(i, j)->y - MAPDATA->getTileData(i, j)->z * 16,
			//	TILEWIDTH,
			//	TILEHEIGHT);
			//MAPDATA->getTileData(i,j)->z = 0;//높이값
			//MAPDATA->getTileData(i,j)->TileNumValue = 0;
			//MAPDATA->getTileData(i, j)->poly[0] = { MAPDATA->getTileData(i,j)->pivotX - TILEWIDTH / 2 + FOCUSMANAGER->getFocusX(), MAPDATA->getTileData(i,j)->pivotY - MAPDATA->getTileData(i,j)->z * 16 + FOCUSMANAGER->getFocusY() - MAPDATA->getTileData(i,j)->objectZ }; //left
			//MAPDATA->getTileData(i, j)->poly[1] = { MAPDATA->getTileData(i,j)->pivotX + FOCUSMANAGER->getFocusX(), MAPDATA->getTileData(i,j)->pivotY - TILEHEIGHT / 2 - MAPDATA->getTileData(i,j)->z * 16 + FOCUSMANAGER->getFocusY() - MAPDATA->getTileData(i,j)->objectZ }; //top
			//MAPDATA->getTileData(i, j)->poly[2] = { MAPDATA->getTileData(i,j)->pivotX + TILEWIDTH / 2 + FOCUSMANAGER->getFocusX(), MAPDATA->getTileData(i,j)->pivotY - MAPDATA->getTileData(i,j)->z * 16 + FOCUSMANAGER->getFocusY() - MAPDATA->getTileData(i,j)->objectZ }; //right
			//MAPDATA->getTileData(i, j)->poly[3] = { MAPDATA->getTileData(i,j)->pivotX + FOCUSMANAGER->getFocusX(), MAPDATA->getTileData(i,j)->pivotY + TILEHEIGHT / 2 - MAPDATA->getTileData(i,j)->z * 16 + FOCUSMANAGER->getFocusY() - MAPDATA->getTileData(i,j)->objectZ }; //bottom
		}
	}
}

void stageMap::showBlock(int i, int j)
{
	/*
		if (!IntersectRect(&rc, &MAPDATA->getTileData(i, j)->rc, &_clipingRc)) return;
		else*/

	int minZ = 0;
	int delta = 0;
	if (i == 29 || j == 29)
	{
		minZ = 0;
	}
	else
	{
		if (MAPDATA->getTileData(i + 1, j)->z < MAPDATA->getTileData(i, j + 1)->z)
		{
			minZ = MAPDATA->getTileData(i + 1, j)->z;
		}
		else
		{
			minZ = MAPDATA->getTileData(i, j + 1)->z;
		}
	}

	delta = MAPDATA->getTileData(i, j)->z - minZ;

	for (int a = 0; a < delta; a++)
	{
		switch (MAPDATA->getTileData(i, j)->tileT)
		{
		case T_GRASS:
			if (a == 0)
			{
				IMAGEMANAGER->focusRender("블록2", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top + (a + 1) * 16);
			}
			else
			{
				IMAGEMANAGER->focusRender("블록3", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top + (a + 1) * 16);
			}
			break;
		case T_ROCK:
			IMAGEMANAGER->focusRender("블록3", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top + (a + 1) * 16);
			break;
		case T_SNOW:
			IMAGEMANAGER->focusRender("블록4", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top + (a + 1) * 16);
			break;
		default:
			break;
		}
	}
}

void stageMap::showTile(int i, int j)
{
	int tempFrameX = 0;
	/*
		if (IntersectRect(&rc, &MAPDATA->getTileData(i, j)->rc, &_clipingRc))
		{*/
	switch (MAPDATA->getTileData(i, j)->tileT)
	{
	case T_GRASS:
		if (j > 0)
		{
			//검사.. 검사.. 
			if (MAPDATA->getTileData(i, j - 1)->z < MAPDATA->getTileData(i, j)->z)
			{

				tempFrameX += 2;
			}
			else if (MAPDATA->getTileData(i, j - 1)->z > MAPDATA->getTileData(i, j)->z)
			{
				tempFrameX += 4;
			}
		}

		if (i > 0)
		{
			if (MAPDATA->getTileData(i - 1, j)->z < MAPDATA->getTileData(i, j)->z)
			{
				tempFrameX += 1;
			}
		}

		IMAGEMANAGER->focusFrameRender("타일1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 0, tempFrameX);

		break;
	case T_ROCK:
		if (j > 0)
		{
			if (MAPDATA->getTileData(i, j - 1)->z > MAPDATA->getTileData(i, j)->z)
			{
				tempFrameX += 4;
				if (i > 0)
				{
					if (MAPDATA->getTileData(i - 1, j)->z < MAPDATA->getTileData(i, j)->z)
					{
						//왼쪽위 선
						tempFrameX += 1;
						IMAGEMANAGER->focusFrameRender("타일1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 1, tempFrameX);
						return;
					}
				}
				IMAGEMANAGER->focusFrameRender("타일1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 1, tempFrameX);
				return;
			}
			else if (MAPDATA->getTileData(i, j - 1)->z < MAPDATA->getTileData(i, j)->z)
			{
				tempFrameX += 2;
				if (i > 0)
				{
					if (MAPDATA->getTileData(i - 1, j)->z < MAPDATA->getTileData(i, j)->z)
					{
						//왼쪽위 선
						tempFrameX += 1;
						IMAGEMANAGER->focusFrameRender("타일1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 1, tempFrameX);
						return;
					}
				}
				IMAGEMANAGER->focusFrameRender("타일1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 1, tempFrameX);
				return;
			}
		}

		if (i > 0)
		{
			if (MAPDATA->getTileData(i - 1, j)->z < MAPDATA->getTileData(i, j)->z)
			{
				//왼쪽위 선
				tempFrameX += 1;
				IMAGEMANAGER->focusFrameRender("타일1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 1, tempFrameX);
				return;
			}
		}
		//=====================================================================================================================//
		if (j > 0)
		{
			if (MAPDATA->getTileData(i, j - 1)->z > MAPDATA->getTileData(i, j)->z)
			{
				IMAGEMANAGER->focusFrameRender("타일1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 1, 1);
				break;
			}
			else if (MAPDATA->getTileData(i, j - 1)->tileT == T_GRASS  && MAPDATA->getTileData(i, j - 1)->z == MAPDATA->getTileData(i, j)->z)
			{
				_search[0] = true;
			}
		}
		if (j < TILEMAXJ - 1)
		{
			if (MAPDATA->getTileData(i, j + 1)->tileT == T_GRASS && MAPDATA->getTileData(i, j + 1)->z == MAPDATA->getTileData(i, j)->z)
			{
				_search[3] = true;
			}
		}
		if (i > 0)
		{
			if (MAPDATA->getTileData(i - 1, j)->tileT == T_GRASS && MAPDATA->getTileData(i - 1, j)->z == MAPDATA->getTileData(i, j)->z)
			{
				_search[1] = true;
			}
		}
		if (i < TILEMAXI - 1)
		{
			if (MAPDATA->getTileData(i + 1, j)->tileT == T_GRASS && MAPDATA->getTileData(i + 1, j)->z == MAPDATA->getTileData(i, j)->z)
			{
				_search[2] = true;
			}
		}
		if (_search[0] == true)//앞이 풀?
		{
			if (_search[1] == true)//왼쪽도 풀?
			{
				IMAGEMANAGER->focusFrameRender("타일1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 3, 2);
				break;
			}
			else if (_search[2] == true)//오른쪽도 풀?
			{
				IMAGEMANAGER->focusFrameRender("타일1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 3, 3);
				break;
			}
			else
			{
				IMAGEMANAGER->focusFrameRender("타일1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 3, 0);
				break;
			}
		}
		if (_search[1] == true)//왼쪽이 풀?
		{
			if (_search[3] == true)//뒤쪽이 풀?
			{
				IMAGEMANAGER->focusFrameRender("타일1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 2, 2);
				break;
			}
			else//왼쪽만 풀
			{
				IMAGEMANAGER->focusFrameRender("타일1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 2, 0);
				break;
			}
		}
		if (_search[2] == true)//오른쪽이 풀?
		{
			if (_search[3] == true)//뒤쪽이 풀?
			{
				IMAGEMANAGER->focusFrameRender("타일1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 2, 3);
				break;
			}
			else//오른쪽만 풀
			{
				IMAGEMANAGER->focusFrameRender("타일1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 3, 1);
				break;
			}
		}
		if (_search[3] == true)
		{
			IMAGEMANAGER->focusFrameRender("타일1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 2, 1);
			break;
		}
		else
		{
			IMAGEMANAGER->focusFrameRender("타일1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 1, 0);
			break;
		}

		break;
	case T_SNOW:

		if (j > 0)
		{
			if (MAPDATA->getTileData(i, j - 1)->z < MAPDATA->getTileData(i, j)->z)
			{
				//_search[0] = true;
				tempFrameX += 1;
			}
		}
		else
		{
			tempFrameX += 1;
		}

		if (j < TILEMAXJ - 1)
		{
			if (MAPDATA->getTileData(i, j + 1)->z < MAPDATA->getTileData(i, j)->z)
			{
				//_search[3] = true;
				tempFrameX += 8;
			}
		}
		else
		{
			tempFrameX += 8;
		}

		if (i > 0)
		{
			if (MAPDATA->getTileData(i - 1, j)->z < MAPDATA->getTileData(i, j)->z)
			{
				//_search[1] = true;
				tempFrameX += 2;
			}
		}
		else
		{
			tempFrameX += 2;
		}


		if (i < TILEMAXI - 1)
		{
			if (MAPDATA->getTileData(i + 1, j)->z < MAPDATA->getTileData(i, j)->z)
			{
				_search[2] = true;
				tempFrameX += 4;
			}
		}
		else
		{
			tempFrameX += 4;
		}

		IMAGEMANAGER->focusFrameRender("타일2", getMemDC(), MAPDATA->getTileData(i, j)->rc.left - 3, MAPDATA->getTileData(i, j)->rc.top, tempFrameX, 0);

		break;
	default:
		break;
	}
	//}
	searchInit();
}

void stageMap::showSelectedTile()
{
	if (MAPDATA->getPickI() < TILEMAXI && MAPDATA->getPickJ() < TILEMAXJ)
	{
		if (MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->classify != CL_ENEMY)
		{
			IMAGEMANAGER->focusRender("선택", getMemDC(), MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->rc.left, MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->rc.top - MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->objectZ);
		}
		else
		{
			IMAGEMANAGER->focusRender("선택2", getMemDC(), MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->rc.left, MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->rc.top - MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->objectZ);
		}
	}
}

void stageMap::showObject(int i, int j)
{
	if (MAPDATA->getTileData(i, j)->objIndex2 != OBJ2_NULL)
	{
		IMAGEMANAGER->focusFrameRender("오브젝트2", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top - 112, MAPDATA->getTileData(i, j)->objIndex2, 0);
	}
	else
	{
		if (MAPDATA->getTileData(i, j)->objIndex1 != OBJ1_NULL)
		{
			IMAGEMANAGER->focusFrameRender("오브젝트", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top - 32, MAPDATA->getTileData(i, j)->objIndex1, 0);
		}
	}
}

void stageMap::pickTile() {
	bool selectback = false;
	if (!KEYMANAGER->isStayKeyDown(VK_SHIFT))
	{
		for (int i = TILEMAXI - 1; i >= 0; i--)
		{
			for (int j = TILEMAXJ - 1; j >= 0; j--)
			{
				HRGN Region;
				Region = CreatePolygonRgn(MAPDATA->getTileData(i, j)->poly, 4, ALTERNATE);
				if (PtInRegion(Region, _ptMouse.x, _ptMouse.y))
				{
					MAPDATA->setPick(i, j);
					DeleteObject(Region);
					return;
				}
				DeleteObject(Region);
			}
		}
	}
	else
	{
		for (int i = TILEMAXI - 1; i >= 0; i--)
		{
			for (int j = TILEMAXJ - 1; j >= 0; j--)
			{
				HRGN Region;
				Region = CreatePolygonRgn(MAPDATA->getTileData(i, j)->poly, 4, ALTERNATE);
				if (PtInRegion(Region, _ptMouse.x, _ptMouse.y))
				{
					if (selectback == false)
					{
						selectback = true;
					}
					else
					{
						MAPDATA->setPick(i, j);
						DeleteObject(Region);
						return;
					}
				}
				DeleteObject(Region);
			}
		}
	}
}

void stageMap::searchInit()
{
	for (int i = 0; i < 4; i++)
	{
		_search[i] = false;
	}
}

void stageMap::showRange(int i, int j)
{
	switch (MAPDATA->getTileData(i, j)->tSELECT)
	{
	case S_NONE:
		break;
	case S_TRUE1:
		IMAGEMANAGER->focusRender("선택", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top - MAPDATA->getTileData(i, j)->objectZ);
		break;
	case S_FALSE1:
		IMAGEMANAGER->focusRender("선택2", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top - MAPDATA->getTileData(i, j)->objectZ);
		break;
	case S_TRUE2:
		IMAGEMANAGER->focusRender("선택3", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top - MAPDATA->getTileData(i, j)->objectZ);
		break;
	case S_FALSE2:
		IMAGEMANAGER->focusRender("선택4", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top - MAPDATA->getTileData(i, j)->objectZ);
		break;
	default:
		break;
	}

}
