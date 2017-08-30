#include "stdafx.h"
#include "testScene.h"


//===== ## [ �׽�Ʈ�� Ŭ���� ] ## =====

//=================================================================================================
//	##	�ʱ�ȭ init(void)	##
//=================================================================================================

HRESULT testScene::init(void)
{


	//Ŀ�� ���ֱ�
	//ShowCursor(false);

	//��� �̹��� �ʱ�ȭ
	_back_img = IMAGEMANAGER->findImage("���");
	_backMoveCount = 0;

	//�ι�° ��� �̹��� �ʱ�ȭ
	_back_img01 = IMAGEMANAGER->addImage("���01", "image/back_img01.bmp", ImgMaxSizeW, WINSIZEY, true, RGB(255, 0, 255));


	return S_OK;
}


//=================================================================================================
//	##	���� release(void)	##
//=================================================================================================

void testScene::release(void)
{

}


//=================================================================================================
//	##	������Ʈ update(void)	##
//=================================================================================================

void testScene::update(void)
{
	//��� ������
	_backMoveCount += 1;





	//	bool collisoin = false;
	//	for (int i = 0; i < MapTileMax; i++)
	//	{
	//		for (int j = 0; j < EnemyMax; j++)
	//		{
	//			RECT RC;
	//			if (IntersectRect(&RC, &_stageMapTile[i].rc, &_enemy->getEnemy(j)->rc) && _stageMapTile[i].obj != OBJ_NONE)
	//			{
	//				collisoin = true;
	//				if (_enemy->getEnemy(j)->state == E_RIGHT)
	//				{
	//					_enemy->getEnemy(j)->rc.left -= SPEED;
	//					_enemy->getEnemy(j)->rc.right -= SPEED;
	//					continue;
	//				}
	//				if (_enemy->getEnemy(j)->state == E_LEFT)
	//				{
	//					_enemy->getEnemy(j)->rc.left += SPEED;
	//					_enemy->getEnemy(j)->rc.right += SPEED;
	//					continue;
	//				}
	//				if (_enemy->getEnemy(j)->state == E_UP)
	//				{
	//					_enemy->getEnemy(j)->rc.top += SPEED;
	//					_enemy->getEnemy(j)->rc.bottom += SPEED;
	//					continue;
	//				}
	//				if (_enemy->getEnemy(j)->state == E_DOWN)
	//				{
	//					_enemy->getEnemy(j)->rc.top -= SPEED;
	//					_enemy->getEnemy(j)->rc.bottom -= SPEED;
	//					continue;
	//				}
	//				
	//			}

	//		}
	//	}

	//	POINT enemyRCC;
	//	POINT tileRCC;
	//	//for (int i = 0; i < MapTileMax; i++)
	//	//{
	//	//	for (int j = 0; j < EnemyMax; j++)
	//	//	{
	//	//		int count = 0;
	//	//		tileRCC.x = getRectCenterX(_stageMapTile[i].rc);
	//	//		tileRCC.y = getRectCenterY(_stageMapTile[i].rc);
	//	//		enemyRCC.x = getRectCenterX(_enemy->getEnemy(j)->rc);
	//	//		enemyRCC.y = getRectCenterY(_enemy->getEnemy(j)->rc);

	//	//		if (enemyRCC.x == tileRCC.x && enemyRCC.y == tileRCC.y)
	//	//		{
	//	//			//���� �浹�˻�
	//	//			if (i % MapTileX != 0)
	//	//			{
	//	//				if (_stageMapTile[i - 1].obj != OBJ_NONE && _enemy->getEnemy(j)->state == E_LEFT)
	//	//				{
	//	//					count++;
	//	//				}
	//	//			}
	//	//			//������ �浹 �˻�
	//	//			if ((i + 1) % MapTileX != 0)
	//	//			{
	//	//				if (_stageMapTile[i + 1].obj != OBJ_NONE && _enemy->getEnemy(j)->state == E_RIGHT)
	//	//				{
	//	//					count++;
	//	//				}
	//	//			}
	//	//			//���� �浹 �˻�
	//	//			if (i > MapTileX)
	//	//			{
	//	//				if (_stageMapTile[i - MapTileX].obj != OBJ_NONE && _enemy->getEnemy(j)->state == E_UP)
	//	//				{
	//	//					count++;
	//	//				}

	//	//			}
	//	//			//�Ʒ��� �浹 �˻�
	//	//			if (i < MapTileMax - MapTileX)
	//	//			{
	//	//				if (_stageMapTile[i + MapTileX].obj != OBJ_NONE && _enemy->getEnemy(j)->state == E_DOWN)
	//	//				{
	//	//					count++;
	//	//				}
	//	//			}
	//	//		}
	//	//	}
	//	//}
	//	if (collisoin)
	//	{

	//		//��AI ������
	//		for (int i = 0; i < MapTileMax; i++)
	//		{
	//			for (int j = 0; j < EnemyMax; j++)
	//			{
	//				
	//				tileRCC.x = getRectCenterX(_stageMapTile[i].rc);
	//				tileRCC.y = getRectCenterY(_stageMapTile[i].rc);
	//				enemyRCC.x = getRectCenterX(_enemy->getEnemy(j)->rc);
	//				enemyRCC.y = getRectCenterY(_enemy->getEnemy(j)->rc);

	//				////�� ���¿� ���� �˻� ��ġ
	//				//if (_enemy->getEnemy(j)->state == E_RIGHT)
	//				//{
	//				//	tileRCC.x = getRectCenterX(_stageMapTile[i].rc) + TileSize;
	//				//	tileRCC.y = getRectCenterY(_stageMapTile[i].rc);
	//				//}
	//				//if (_enemy->getEnemy(j)->state == E_LEFT)
	//				//{
	//				//	tileRCC.x = getRectCenterX(_stageMapTile[i].rc) - TileSize;
	//				//	tileRCC.y = getRectCenterY(_stageMapTile[i].rc);

	//				//}
	//				//if (_enemy->getEnemy(j)->state == E_UP)
	//				//{
	//				//	tileRCC.x = getRectCenterX(_stageMapTile[i].rc);
	//				//	tileRCC.y = getRectCenterY(_stageMapTile[i].rc) - TileSize;

	//				//}
	//				//if (_enemy->getEnemy(j)->state == E_DOWN)
	//				//{
	//				//	tileRCC.x = getRectCenterX(_stageMapTile[i].rc);
	//				//	tileRCC.y = getRectCenterY(_stageMapTile[i].rc) + TileSize;
	//				//}

	//				/*if (KEYMANAGER->isToggleKey(VK_SPACE))
	//				{
	//					cout << "pX : " << enemyRCC.x << endl;
	//					cout << "pY : " << enemyRCC.y << endl << endl;
	//					cout << "eX : " << tileRCC.x << endl;
	//					cout << "eY : " << tileRCC.y << endl<< endl;
	//				}*/

	//				//����Ű ��� ���� �浹 �˻�

	//				//RECT RC;
	//				//if (IntersectRect(&RC, &_stageMapTile[i].rc, &_enemy->getEnemy(j)->rc) && _stageMapTile[i].obj != OBJ_NONE)
	//				//if (enemyRCC.x == tileRCC.x && enemyRCC.y == tileRCC.y && _stageMapTile[i].obj != OBJ_NONE)
	//				if (enemyRCC.x == tileRCC.x && enemyRCC.y == tileRCC.y)
	//				{
	//					_enemy->getEnemy(j)->state = (EnemyState)RND->getInt(4);

	//					//���� �浹�˻�
	//					if (i % MapTileX != 0)
	//					{
	//						if (_stageMapTile[i - 1].obj != OBJ_NONE && _enemy->getEnemy(j)->state == E_LEFT)
	//						{
	//							j--;
	//							continue;
	//						}
	//					}
	//					//������ �浹 �˻�
	//					if ((i + 1) % MapTileX != 0)
	//					{
	//						if (_stageMapTile[i + 1].obj != OBJ_NONE && _enemy->getEnemy(j)->state == E_RIGHT)
	//						{
	//							j--;
	//							continue;
	//						}
	//					}
	//					//���� �浹 �˻�
	//					if (i > MapTileX)
	//					{
	//						if (_stageMapTile[i - MapTileX].obj != OBJ_NONE && _enemy->getEnemy(j)->state == E_UP)
	//						{
	//							j--;
	//							continue;
	//						}

	//					}
	//					//�Ʒ��� �浹 �˻�
	//					if (i < MapTileMax - MapTileX)
	//					{
	//						if (_stageMapTile[i + MapTileX].obj != OBJ_NONE && _enemy->getEnemy(j)->state == E_DOWN)
	//						{
	//							j--;
	//							continue;
	//						}
	//					}

	//					//_enemy[i].state = (EnemyState)RND->getInt(4);
	///*
	//					if (_enemy->getEnemy(j)->state == E_RIGHT)
	//					{
	//						_enemy->getEnemy(j)->rc.left -= SPEED;
	//						_enemy->getEnemy(j)->rc.right -= SPEED;


	//					}
	//					if (_enemy->getEnemy(j)->state == E_LEFT)
	//					{
	//						_enemy->getEnemy(j)->rc.left += SPEED;
	//						_enemy->getEnemy(j)->rc.right += SPEED;


	//					}
	//					if (_enemy->getEnemy(j)->state == E_UP)
	//					{
	//						_enemy->getEnemy(j)->rc.top += SPEED;
	//						_enemy->getEnemy(j)->rc.bottom += SPEED;

	//					}
	//					if (_enemy->getEnemy(j)->state == E_DOWN)
	//					{
	//						_enemy->getEnemy(j)->rc.top -= SPEED;
	//						_enemy->getEnemy(j)->rc.bottom -= SPEED;
	//					}*/

	//				}//����Ű ��� ���� �浹 �˻� END
	//			}//for_j end
	//		}//for_i end

	//	}
	//	//���� ��������
	//	if (_endCount <= 0) _gameEnd = true;


}

//=================================================================================================
//	##	���� render(HDC hdc)	##
//=================================================================================================

void testScene::render(void)
{
	//��� ����
	_back_img->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _backMoveCount, 0);
	_back_img01->render(getMemDC());

}




//=================================================================================================
//	##	�Լ� Function	##
//=================================================================================================
