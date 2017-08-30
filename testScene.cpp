#include "stdafx.h"
#include "testScene.h"


//===== ## [ 테스트씬 클래스 ] ## =====

//=================================================================================================
//	##	초기화 init(void)	##
//=================================================================================================

HRESULT testScene::init(void)
{


	//커서 없애기
	//ShowCursor(false);

	//배경 이미지 초기화
	_back_img = IMAGEMANAGER->findImage("배경");
	_backMoveCount = 0;

	//두번째 배경 이미지 초기화
	_back_img01 = IMAGEMANAGER->addImage("배경01", "image/back_img01.bmp", ImgMaxSizeW, WINSIZEY, true, RGB(255, 0, 255));


	return S_OK;
}


//=================================================================================================
//	##	해제 release(void)	##
//=================================================================================================

void testScene::release(void)
{

}


//=================================================================================================
//	##	업데이트 update(void)	##
//=================================================================================================

void testScene::update(void)
{
	//배경 움직임
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
	//	//			//왼쪽 충돌검사
	//	//			if (i % MapTileX != 0)
	//	//			{
	//	//				if (_stageMapTile[i - 1].obj != OBJ_NONE && _enemy->getEnemy(j)->state == E_LEFT)
	//	//				{
	//	//					count++;
	//	//				}
	//	//			}
	//	//			//오른쪽 충돌 검사
	//	//			if ((i + 1) % MapTileX != 0)
	//	//			{
	//	//				if (_stageMapTile[i + 1].obj != OBJ_NONE && _enemy->getEnemy(j)->state == E_RIGHT)
	//	//				{
	//	//					count++;
	//	//				}
	//	//			}
	//	//			//위쪽 충돌 검사
	//	//			if (i > MapTileX)
	//	//			{
	//	//				if (_stageMapTile[i - MapTileX].obj != OBJ_NONE && _enemy->getEnemy(j)->state == E_UP)
	//	//				{
	//	//					count++;
	//	//				}

	//	//			}
	//	//			//아랫쪽 충돌 검사
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

	//		//적AI 움직임
	//		for (int i = 0; i < MapTileMax; i++)
	//		{
	//			for (int j = 0; j < EnemyMax; j++)
	//			{
	//				
	//				tileRCC.x = getRectCenterX(_stageMapTile[i].rc);
	//				tileRCC.y = getRectCenterY(_stageMapTile[i].rc);
	//				enemyRCC.x = getRectCenterX(_enemy->getEnemy(j)->rc);
	//				enemyRCC.y = getRectCenterY(_enemy->getEnemy(j)->rc);

	//				////적 상태에 따른 검사 위치
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

	//				//방향키 제어를 위한 충돌 검사

	//				//RECT RC;
	//				//if (IntersectRect(&RC, &_stageMapTile[i].rc, &_enemy->getEnemy(j)->rc) && _stageMapTile[i].obj != OBJ_NONE)
	//				//if (enemyRCC.x == tileRCC.x && enemyRCC.y == tileRCC.y && _stageMapTile[i].obj != OBJ_NONE)
	//				if (enemyRCC.x == tileRCC.x && enemyRCC.y == tileRCC.y)
	//				{
	//					_enemy->getEnemy(j)->state = (EnemyState)RND->getInt(4);

	//					//왼쪽 충돌검사
	//					if (i % MapTileX != 0)
	//					{
	//						if (_stageMapTile[i - 1].obj != OBJ_NONE && _enemy->getEnemy(j)->state == E_LEFT)
	//						{
	//							j--;
	//							continue;
	//						}
	//					}
	//					//오른쪽 충돌 검사
	//					if ((i + 1) % MapTileX != 0)
	//					{
	//						if (_stageMapTile[i + 1].obj != OBJ_NONE && _enemy->getEnemy(j)->state == E_RIGHT)
	//						{
	//							j--;
	//							continue;
	//						}
	//					}
	//					//위쪽 충돌 검사
	//					if (i > MapTileX)
	//					{
	//						if (_stageMapTile[i - MapTileX].obj != OBJ_NONE && _enemy->getEnemy(j)->state == E_UP)
	//						{
	//							j--;
	//							continue;
	//						}

	//					}
	//					//아랫쪽 충돌 검사
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

	//				}//방향키 제어를 위한 충돌 검사 END
	//			}//for_j end
	//		}//for_i end

	//	}
	//	//게임 종료조건
	//	if (_endCount <= 0) _gameEnd = true;


}

//=================================================================================================
//	##	랜더 render(HDC hdc)	##
//=================================================================================================

void testScene::render(void)
{
	//배경 띄우기
	_back_img->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _backMoveCount, 0);
	_back_img01->render(getMemDC());

}




//=================================================================================================
//	##	함수 Function	##
//=================================================================================================
