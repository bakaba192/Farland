#include "stdafx.h"
#include "F_TileMapTool.h"

HRESULT F_TileMapTool::init(void)
{
	/*
	IMAGEMANAGER->addImage("���", "image/���.bmp", 64, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���2", "image/���2.bmp", 64, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���3", "image/���3.bmp", 64, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���4", "image/���4.bmp", 64, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "image/TileSelectTrue2.bmp", 64, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����2", "image/TileSelectFalse2.bmp", 64, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����3", "image/TileSelectTrue.bmp", 64, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����4", "image/TileSelectFalse.bmp", 64, 32, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Ÿ��1", "image/GrassTile.bmp", 320, 192, 5, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Ÿ��2", "image/SnowTile.bmp", 1120, 48, 16, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("������Ʈ", "image/������Ʈ.bmp", 640, 128, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������Ʈ2", "image/������Ʈ2.bmp", 448, 140, 7, 1, true, RGB(255, 0, 255));
	*/

	//MAPDATA->getStageNumber() = 1;

	

	_selectedTile = T_GRASS;
	_selectedObject = OBJ2_NULL;

	searchInit();

	_map = new stageMap;
	_map->init();

	_isFolding = true;

	_UIgoLeft = false;
	_UIgoRight = false;

	
	//_clipingRc = { 0 - FOCUSMANAGER->getFocusX() - 100,0 - FOCUSMANAGER->getFocusY() - 100, -FOCUSMANAGER->getFocusX() + WINSIZEX - 200, WINSIZEY - FOCUSMANAGER->getFocusY() + 100 };


	_UIrect = { WINSIZEX, 0, WINSIZEX, WINSIZEY };
	
	setUIpos();


	return S_OK;
}

void F_TileMapTool::release(void)
{

}

void F_TileMapTool::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		SCENEMANAGER->changeScene("����");
	}

	setUIpos();

	UIDrag();

	UIcontrol();

	FOCUSMANAGER->FocusByMouse();

	MAPDATA->pickTile();

	setTilePosUpdate();

	setTileType();

	setTile_Z_Order();

	setObject();

	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		SCENEMANAGER->changeScene("��������1");
	}
}

void F_TileMapTool::render(void)
{
	RECT rc;

	for (int i = 0; i < TILEMAXI; i++)
	{
		for (int j = 0; j < TILEMAXJ; j++)
		{
			if (IntersectRect(&rc, &MAPDATA->getTileData(i, j)->rc, &_clipingRc))
			{
				_map->showBlock(i, j);
				_map->showTile(i, j);
				_map->showRange(i, j);
				_map->showObject(i, j);
			}

		}
	}
	_map->showSelectedTile();

	//UI�� �׷�����.
	UIrender();


	TextOut(getMemDC(), _ptMouse.x + 20, _ptMouse.y, to_string(MAPDATA->getPickI()).c_str(), strlen(to_string(MAPDATA->getPickI()).c_str()));
	TextOut(getMemDC(), _ptMouse.x + 40, _ptMouse.y, to_string(MAPDATA->getPickJ()).c_str(), strlen(to_string(MAPDATA->getPickJ()).c_str()));
}

void F_TileMapTool::setTile_Z_Order()
{
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (MAPDATA->getPickI() < TILEMAXI && MAPDATA->getPickJ() < TILEMAXJ)
		{
			MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->z++;

			return;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		if (MAPDATA->getPickI() < TILEMAXI && MAPDATA->getPickJ() < TILEMAXJ)
		{
			if (MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->z > 0)
			{
				MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->z--;
			}
			return;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		for (int i = 0; i < TILEMAXI; i++)
		{
			for (int j = 0; j < TILEMAXJ; j++)
			{
				MAPDATA->getTileData(i, j)->z = MAPDATA->getTileData(i, j)->z + 1;
			}
		}
	}


	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		for (int i = 0; i < TILEMAXI; i++)
		{
			for (int j = 0; j < TILEMAXJ; j++)
			{
				MAPDATA->getTileData(i, j)->z = MAPDATA->getTileData(i, j)->z - 1;
			}
		}
	}
}

void F_TileMapTool::setObject() {
	/*
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		if (MAPDATA->getPickI() < TILEMAXI && MAPDATA->getPickJ() < TILEMAXJ)
		{
			if (MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->z > 0)
			{
				MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->objIndex1 = OBJ1_BOX2;
			}
			return;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('T'))
	{
		if (MAPDATA->getPickI() < TILEMAXI && MAPDATA->getPickJ() < TILEMAXJ)
		{
			if (MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->z > 0)
			{
				MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->objIndex2 = OBJ2_SIGN2;
			}
			return;
		}
	}
	*/
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (MAPDATA->getPickI() < TILEMAXI && MAPDATA->getPickJ() < TILEMAXJ)
		{
			if (MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->z > 0)
			{
				MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->objIndex1 = OBJ1_NULL;
				MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->objIndex2 = OBJ2_NULL;
			}
			return;
		}
	}

	for (int i = TILEMAXJ - 1; i >= 0; i--)
	{
		for (int j = TILEMAXJ - 1; j >= 0; j--)
		{
			switch (MAPDATA->getTileData(i, j)->objIndex1)
			{
			case OBJ1_PANEL1:
				MAPDATA->getTileData(i, j)->objectZ = 10;
				break;

			case OBJ1_PANEL2:
				MAPDATA->getTileData(i, j)->objectZ = 10;
				break;

			case OBJ1_BOX1:
				MAPDATA->getTileData(i, j)->objectZ = 16;
				break;

			case OBJ1_BOX2:
				MAPDATA->getTileData(i, j)->objectZ = 32;
				break;

			case OBJ1_DRUM:
				MAPDATA->getTileData(i, j)->objectZ = 32;
				break;
			default:
				MAPDATA->getTileData(i, j)->objectZ = 0;
				break;
			}

			if (MAPDATA->getTileData(i, j)->objIndex2 != OBJ2_NULL)
			{
				MAPDATA->getTileData(i, j)->classify = CL_NONE;
				MAPDATA->getTileData(i, j)->objIndex1 = OBJ1_NULL;
			}
			else
			{
				MAPDATA->getTileData(i, j)->classify = CL_OBJECT;
			}
		}
	}
}

void F_TileMapTool::drawMap()
{
	for (int i = 0; i < TILEMAXI; i++)
	{
		for (int j = 0; j < TILEMAXJ; j++)
		{
			if (MAPDATA->getTileData(i, j)->z > 0)
			{
				for (int a = 0; a < MAPDATA->getTileData(i, j)->z; a++)
				{
					switch (MAPDATA->getTileData(i, j)->tileT)
					{
					case T_GRASS:
						if (a == 0)
						{
							IMAGEMANAGER->focusRender("���2", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top + (a + 1) * 16);
						}
						else
						{
							IMAGEMANAGER->focusRender("���3", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top + (a + 1) * 16);
						}
						break;
					case T_ROCK:
						IMAGEMANAGER->focusRender("���3", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top + (a + 1) * 16);
						break;
					case T_SNOW:
						IMAGEMANAGER->focusRender("���4", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top + (a + 1) * 16);
						break;
					default:
						break;
					}
				}
			}
			//���� �� �κп� Ÿ�ϱ׸��⸦ ����� ��. �ٵ� Ÿ�� ������ �� ���� �ȵ�� ����..
			showTile(i, j);
			showObject(i, j);

			if (KEYMANAGER->isToggleKey(VK_F1))
			{
				Polygon(getMemDC(), MAPDATA->getTileData(i, j)->poly, 4);
			}
		}
	}
}

void F_TileMapTool::showTile(int i, int j)
{
	int tempFrameX = 0;
	switch (MAPDATA->getTileData(i, j)->tileT)
	{
	case T_GRASS:
		if (j > 0)
		{
			//�˻�.. �˻�.. 
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

		IMAGEMANAGER->focusFrameRender("Ÿ��1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 0, tempFrameX);

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
						//������ ��
						tempFrameX += 1;
						IMAGEMANAGER->focusFrameRender("Ÿ��1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 1, tempFrameX);
						return;
					}
				}
				IMAGEMANAGER->focusFrameRender("Ÿ��1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 1, tempFrameX);
				return;
			}
			else if (MAPDATA->getTileData(i, j - 1)->z < MAPDATA->getTileData(i, j)->z)
			{
				tempFrameX += 2;
				if (i > 0)
				{
					if (MAPDATA->getTileData(i - 1, j)->z < MAPDATA->getTileData(i, j)->z)
					{
						//������ ��
						tempFrameX += 1;
						IMAGEMANAGER->focusFrameRender("Ÿ��1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 1, tempFrameX);
						return;
					}
				}
				IMAGEMANAGER->focusFrameRender("Ÿ��1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 1, tempFrameX);
				return;
			}
		}

		if (i > 0)
		{
			if (MAPDATA->getTileData(i - 1, j)->z < MAPDATA->getTileData(i, j)->z)
			{
				//������ ��
				tempFrameX += 1;
				IMAGEMANAGER->focusFrameRender("Ÿ��1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 1, tempFrameX);
				return;
			}
		}
		//=====================================================================================================================//
		if (j > 0)
		{
			if (MAPDATA->getTileData(i, j - 1)->z > MAPDATA->getTileData(i, j)->z)
			{
				IMAGEMANAGER->focusFrameRender("Ÿ��1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 1, 1);
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
		if (_search[0] == true)//���� Ǯ?
		{
			if (_search[1] == true)//���ʵ� Ǯ?
			{
				IMAGEMANAGER->focusFrameRender("Ÿ��1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 3, 2);
				break;
			}
			else if (_search[2] == true)//�����ʵ� Ǯ?
			{
				IMAGEMANAGER->focusFrameRender("Ÿ��1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 3, 3);
				break;
			}
			else
			{
				IMAGEMANAGER->focusFrameRender("Ÿ��1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 3, 0);
				break;
			}
		}
		if (_search[1] == true)//������ Ǯ?
		{
			if (_search[3] == true)//������ Ǯ?
			{
				IMAGEMANAGER->focusFrameRender("Ÿ��1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 2, 2);
				break;
			}
			else//���ʸ� Ǯ
			{
				IMAGEMANAGER->focusFrameRender("Ÿ��1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 2, 0);
				break;
			}
		}
		if (_search[2] == true)//�������� Ǯ?
		{
			if (_search[3] == true)//������ Ǯ?
			{
				IMAGEMANAGER->focusFrameRender("Ÿ��1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 2, 3);
				break;
			}
			else//�����ʸ� Ǯ
			{
				IMAGEMANAGER->focusFrameRender("Ÿ��1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 3, 1);
				break;
			}
		}
		if (_search[3] == true)
		{
			IMAGEMANAGER->focusFrameRender("Ÿ��1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 2, 1);
			break;
		}
		else
		{
			IMAGEMANAGER->focusFrameRender("Ÿ��1", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top, 1, 0);
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

		IMAGEMANAGER->focusFrameRender("Ÿ��2", getMemDC(), MAPDATA->getTileData(i, j)->rc.left - 3, MAPDATA->getTileData(i, j)->rc.top, tempFrameX, 0);

		break;
	default:
		break;
	}
	searchInit();
}

void F_TileMapTool::showSelectedTile()
{
	if (MAPDATA->getPickI() < TILEMAXI && MAPDATA->getPickJ() < TILEMAXJ)
	{
		if (MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->classify != CL_ENEMY)
		{
			IMAGEMANAGER->focusRender("����", getMemDC(), MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->rc.left, MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->rc.top - MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->objectZ);
		}
		else
		{
			IMAGEMANAGER->focusRender("����2", getMemDC(), MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->rc.left, MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->rc.top - MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->objectZ);
		}
	}
}

void F_TileMapTool::searchInit()
{
	for (int i = 0; i < 4; i++)
	{
		_search[i] = false;
	}
}


void F_TileMapTool::setTileType() {

	if (KEYMANAGER->isStayKeyDown('Q'))
	{
		_selectedTile = T_GRASS;
		/*if (MAPDATA->getPickI() < TILEMAXI && MAPDATA->getPickJ() < TILEMAXJ)
		{
			MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->tileT = T_GRASS;
			return;
		}*/
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_selectedTile = T_ROCK;
		/*
		if (MAPDATA->getPickI() < TILEMAXI && MAPDATA->getPickJ() < TILEMAXJ)
		{
			MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->tileT = T_ROCK;
			return;
		}*/
	}

	if (KEYMANAGER->isStayKeyDown('E'))//Ÿ��
	{
		_selectedTile = T_SNOW;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && PtInRect(&_clipingRc, { _ptMouse.x - FOCUSMANAGER->getFocusX(), _ptMouse.y - FOCUSMANAGER->getFocusY() }))
	{
		if (MAPDATA->getPickI() < TILEMAXI && MAPDATA->getPickJ() < TILEMAXJ)
		{
			MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->tileT = _selectedTile;
			MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->objIndex2 = _selectedObject;
			if (MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->objIndex2 != OBJ2_NULL)
			{
				MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->wayState = WAYSTATE::WAY_BLOCK;
			}
			return;
		}
	}
}

void F_TileMapTool::setTilePosUpdate()
{
	for (int i = 0; i < TILEMAXI; i++)
	{
		for (int j = 0; j < TILEMAXJ; j++)
		{
			/*MAPDATA->getTileData(i,j)->x = WINSIZEX / 2 - TILEWIDTH / 2 + (TILEWIDTH / 2)*(i - j) + FOCUSMANAGER->getFocusX();
			MAPDATA->getTileData(i,j)->y = 50 - TILEHEIGHT / 2 + (TILEHEIGHT / 2) *(i + j) + FOCUSMANAGER->getFocusY();
			MAPDATA->getTileData(i,j)->pivotX = MAPDATA->getTileData(i,j)->x + TILEWIDTH / 2;
			MAPDATA->getTileData(i,j)->pivotY = MAPDATA->getTileData(i,j)->y + TILEHEIGHT / 2;*/
			MAPDATA->getTileData(i, j)->rc = RectMake(MAPDATA->getTileData(i, j)->x,
				MAPDATA->getTileData(i, j)->y - MAPDATA->getTileData(i, j)->z * 16,
				TILEWIDTH,
				TILEHEIGHT);
			//MAPDATA->getTileData(i,j)->z = 0;//���̰�
			//MAPDATA->getTileData(i,j)->TileNumValue = 0;
			MAPDATA->getTileData(i, j)->poly[0] = { MAPDATA->getTileData(i,j)->pivotX - TILEWIDTH / 2 + FOCUSMANAGER->getFocusX(), MAPDATA->getTileData(i,j)->pivotY - MAPDATA->getTileData(i,j)->z * 16 + FOCUSMANAGER->getFocusY() - MAPDATA->getTileData(i,j)->objectZ }; //left
			MAPDATA->getTileData(i, j)->poly[1] = { MAPDATA->getTileData(i,j)->pivotX + FOCUSMANAGER->getFocusX(), MAPDATA->getTileData(i,j)->pivotY - TILEHEIGHT / 2 - MAPDATA->getTileData(i,j)->z * 16 + FOCUSMANAGER->getFocusY() - MAPDATA->getTileData(i,j)->objectZ }; //top
			MAPDATA->getTileData(i, j)->poly[2] = { MAPDATA->getTileData(i,j)->pivotX + TILEWIDTH / 2 + FOCUSMANAGER->getFocusX(), MAPDATA->getTileData(i,j)->pivotY - MAPDATA->getTileData(i,j)->z * 16 + FOCUSMANAGER->getFocusY() - MAPDATA->getTileData(i,j)->objectZ }; //right
			MAPDATA->getTileData(i, j)->poly[3] = { MAPDATA->getTileData(i,j)->pivotX + FOCUSMANAGER->getFocusX(), MAPDATA->getTileData(i,j)->pivotY + TILEHEIGHT / 2 - MAPDATA->getTileData(i,j)->z * 16 + FOCUSMANAGER->getFocusY() - MAPDATA->getTileData(i,j)->objectZ }; //bottom
		}
	}
}

//���
void F_TileMapTool::pickTile() {
	/*
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
					RECT rc;
					if (IntersectRect(&rc, &MAPDATA->getTileData(i, j)->rc, &_clipingRc))
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
	*/
}

void F_TileMapTool::showObject(int i, int j)
{
	if (MAPDATA->getTileData(i, j)->objIndex2 != OBJ2_NULL)
	{
		IMAGEMANAGER->focusFrameRender("������Ʈ2", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top - 112, MAPDATA->getTileData(i, j)->objIndex2, 0);
	}
	else
	{
		if (MAPDATA->getTileData(i, j)->objIndex1 != OBJ1_NULL)
		{
			IMAGEMANAGER->focusFrameRender("������Ʈ", getMemDC(), MAPDATA->getTileData(i, j)->rc.left, MAPDATA->getTileData(i, j)->rc.top - 32, MAPDATA->getTileData(i, j)->objIndex1, 0);
		}
	}
}



void F_TileMapTool::UIcontrol()
{
	//ui�� ��������.
	
	if (PtInRect(&_stageArrowLeftRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (MAPDATA->getStageNumber() > 1)
			{
				MAPDATA->getStageNumber()--;
				MAPDATA->loadMap(MAPDATA->getStageNumber());
			}
		}
	}
	
	if (PtInRect(&_stageArrowRightRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (MAPDATA->getStageNumber() < 3)
			{
				MAPDATA->getStageNumber()++;
				MAPDATA->loadMap(MAPDATA->getStageNumber());
			}
		}
	}

	if (PtInRect(&_tileArrowLeftRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_selectedTile == T_ROCK)
			{
				_selectedTile = T_GRASS;
			}
			else if (_selectedTile == T_SNOW)
			{
				_selectedTile = T_ROCK;
			}
		}
	}

	if (PtInRect(&_tileArrowRightRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_selectedTile == T_GRASS)
			{
				_selectedTile = T_ROCK;
			}
			else if (_selectedTile == T_ROCK)
			{
				_selectedTile = T_SNOW;
			}
		}
	}

	if (PtInRect(&_saveBtnRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			vector<tagFarTile> v;
			//���̺�

			string stage;

			stage = "ini/��������" + to_string(MAPDATA->getStageNumber());

			for (int i = 0; i < TILEMAXI; i++)
			{
				for (int j = 0; j < TILEMAXJ; j++)
				{
					v.push_back(*MAPDATA->getTileData(i, j));
				}
			}
			DATABASE->clearData(stage.c_str());
			DATABASE->saveMapData(stage.c_str(), v);
		}
	}

	if (PtInRect(&_loadBtnRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			vector<tagFarTile> v;
			//���̺�

			string stage;

			stage = "ini/��������" + to_string(MAPDATA->getStageNumber());

			for (int i = 0; i < TILEMAXI; i++)
			{
				for (int j = 0; j < TILEMAXJ; j++)
				{
					if (i*TILEMAXI + j < v.size())
					{
						MAPDATA->getTileData(i, j)->z = v[i*TILEMAXI + j].z;
						MAPDATA->getTileData(i, j)->tileT = v[i*TILEMAXI + j].tileT;
						MAPDATA->getTileData(i, j)->objIndex1 = v[i*TILEMAXI + j].objIndex1;
						MAPDATA->getTileData(i, j)->objIndex2 = v[i*TILEMAXI + j].objIndex2;
					}
					else
					{
						MAPDATA->getTileData(i, j)->z = 1;
						MAPDATA->getTileData(i, j)->tileT = T_GRASS;
						MAPDATA->getTileData(i, j)->objIndex1 = OBJ1_NULL;
						MAPDATA->getTileData(i, j)->objIndex2 = OBJ2_NULL;
					}
				}
			}
		}
	}

	if (PtInRect(&_objectArrowRightRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			switch (_selectedObject)
			{
			case OBJ2_TREE1:
				_selectedObject = OBJ2_TREE2;
				break;
			case OBJ2_TREE2:
				_selectedObject = OBJ2_TREE3;
				break;
			case OBJ2_TREE3:
				_selectedObject = OBJ2_SIGN1;
				break;
			case OBJ2_SIGN1:
				_selectedObject = OBJ2_SIGN2;
				break;
			case OBJ2_SIGN2:
				_selectedObject = OBJ2_SIGN3;
				break;
			case OBJ2_SIGN3:
				_selectedObject = OBJ2_SIGN4;
				break;
			case OBJ2_SIGN4:
				
				break;
			case OBJ2_NULL:
				_selectedObject = OBJ2_TREE1;
				break;
			default:
				break;
			}
		}
	}


	if (PtInRect(&_objectArrowLeftRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			switch (_selectedObject)
			{
			case OBJ2_TREE1:
				_selectedObject = OBJ2_NULL;
				break;
			case OBJ2_TREE2:
				_selectedObject = OBJ2_TREE1;
				break;
			case OBJ2_TREE3:
				_selectedObject = OBJ2_TREE2;
				break;
			case OBJ2_SIGN1:
				_selectedObject = OBJ2_TREE3;
				break;
			case OBJ2_SIGN2:
				_selectedObject = OBJ2_SIGN1;
				break;
			case OBJ2_SIGN3:
				_selectedObject = OBJ2_SIGN2;
				break;
			case OBJ2_SIGN4:
				_selectedObject = OBJ2_SIGN3;
				break;
			case OBJ2_NULL:
				
				break;
			default:
				break;
			}
		}
	}
}

void F_TileMapTool::UIrender()
{
	if (!KEYMANAGER->isToggleKey(VK_F3))
	{
		IMAGEMANAGER->render("�׵θ�", getMemDC(), _boundRect.left, _boundRect.top);
		//IMAGEMANAGER->render("UI���", getMemDC(), _UIrect.left, _UIrect.top);
		IMAGEMANAGER->frameRender("ȭ��ǥ", getMemDC(), _stageArrowLeftRc.left, _stageArrowLeftRc.top, 0, 0);
		IMAGEMANAGER->frameRender("ȭ��ǥ", getMemDC(), _stageArrowRightRc.left, _stageArrowRightRc.top, 1, 0);
		IMAGEMANAGER->frameRender("������Ʈ3", getMemDC(), _stageNumberRc.left, _stageNumberRc.top, 0, MAPDATA->getStageNumber());
		IMAGEMANAGER->frameRender("ȭ��ǥ", getMemDC(), _tileArrowLeftRc.left, _tileArrowLeftRc.top, 0, 0);
		IMAGEMANAGER->frameRender("ȭ��ǥ", getMemDC(), _tileArrowRightRc.left, _tileArrowRightRc.top, 1, 0);
		
		switch (_selectedTile)
		{
		case T_BLANK:
			break;
		case T_GRASS:
			IMAGEMANAGER->frameRender("Ÿ��1", getMemDC(), _UItileRc.left, _UItileRc.top + 16, 0, 0);
			break;
		case T_ROCK:
			IMAGEMANAGER->frameRender("Ÿ��1", getMemDC(), _UItileRc.left, _UItileRc.top + 16, 1, 0);
			break;
		case T_SNOW:
			IMAGEMANAGER->frameRender("Ÿ��2", getMemDC(), _UItileRc.left, _UItileRc.top + 16, 0, 0);
			break;
		default:
			break;
		}
		
		
		IMAGEMANAGER->render("���̺�", getMemDC(), _saveBtnRc.left, _saveBtnRc.top);
		IMAGEMANAGER->render("�ε�", getMemDC(), _loadBtnRc.left, _loadBtnRc.top);


		if (PtInRect(&_saveBtnRc, _ptMouse))
		{
			SetTextColor(getMemDC(), RGB(0, 0, 0));
			TextOut(getMemDC(), _saveBtnRc.left + 8, _saveBtnRc.top + 20, "���̺�", strlen("���̺�"));
		}

		if (PtInRect(&_loadBtnRc, _ptMouse))
		{
			SetTextColor(getMemDC(), RGB(0, 0, 0));
			TextOut(getMemDC(), _loadBtnRc.left + 10, _loadBtnRc.top + 20, " �ε� ", strlen(" �ε� "));
		}

		IMAGEMANAGER->frameRender("ȭ��ǥ", getMemDC(), _objectArrowLeftRc.left, _objectArrowLeftRc.top, 0, 0);
		IMAGEMANAGER->frameRender("ȭ��ǥ", getMemDC(), _objectArrowRightRc.left, _objectArrowRightRc.top, 1, 0);

		if (_selectedObject != OBJ2_NULL)
		{
			IMAGEMANAGER->frameRender("������Ʈ2", getMemDC(), _UIobjectRc.left, _UIobjectRc.top, _selectedObject, 0);
		}
		
	}
}

void F_TileMapTool::setUIpos()
{

	_boundRect = RectMake(_UIrect.left - 20, 0, 20, 480);

	_stageArrowLeftRc = RectMake(_UIrect.left + 4, _UIrect.top + 16, 64, 64);

	_stageArrowRightRc = RectMake(_stageArrowLeftRc.right + 64, _UIrect.top + 16, 64, 64);

	_stageNumberRc = RectMake(_stageArrowLeftRc.right + 16, _UIrect.top + 16, 32, 64);

	_tileArrowLeftRc = RectMake(_UIrect.left + 4, _stageArrowLeftRc.bottom + 16, 64, 64);

	_tileArrowRightRc = RectMake(_tileArrowLeftRc.right + 64, _stageArrowLeftRc.bottom + 16, 64, 64);

	_UItileRc = RectMake(_tileArrowLeftRc.right, _stageArrowLeftRc.bottom + 16, 64, 64);

	_saveBtnRc = RectMake(_UIrect.left + 20, WINSIZEY - 84 - 10, 64, 64);
	_loadBtnRc = RectMake(_saveBtnRc.right + 32, WINSIZEY - 84 - 10, 64, 64);

	_objectArrowLeftRc = RectMake(_UIrect.left + 4, _tileArrowLeftRc.bottom + 98, 64, 64);
	_UIobjectRc = RectMake(_objectArrowLeftRc.right, _tileArrowLeftRc.bottom + 48, 64, 64);
	_objectArrowRightRc = RectMake(_objectArrowLeftRc.right + 64, _tileArrowLeftRc.bottom + 98, 64, 64);

	_clipingRc = { 0 - FOCUSMANAGER->getFocusX() - 100,0 - FOCUSMANAGER->getFocusY() - 100,  _boundRect.left - 64 - FOCUSMANAGER->getFocusX(), WINSIZEY - FOCUSMANAGER->getFocusY() + 100 };
}


void F_TileMapTool::UIDrag()
{
	if (PtInRect(&_boundRect, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_isFolding)//��������.
			{
				_UIgoLeft = true;
			}
			else
			{
				_UIgoRight = true;
			}
		}
	}

	if (_UIgoLeft)
	{
		_UIrect = RectMake(_UIrect.left - 3, _UIrect.top, 200, 480);
		if (_UIrect.left < WINSIZEX - 200)
		{
			_UIrect.left = WINSIZEX - 200;
			_UIgoLeft = false;
			_isFolding = false;
		}
	}
	
	if(_UIgoRight)
	{
		_UIrect = RectMake(_UIrect.left + 3, _UIrect.top, 200, 480);
		if (_UIrect.left > WINSIZEX)
		{
			_UIrect.left = WINSIZEX;
			_UIgoRight = false;
			_isFolding = true;
		}
	}
}