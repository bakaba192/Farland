#include "stdafx.h"
#include "mainGame.h"

//===== ## [ 메인게임 클래스 ] ## =====

//=================================================================================================
//	##	초기화 init(void)	##
//=================================================================================================

HRESULT mainGame::init(void)
{
	//게임노드 초기화
	gameNode::init(TRUE);

	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	//씬 추가
	SCENEMANAGER->addScene("맵툴", new F_TileMapTool);
	SCENEMANAGER->addScene("스테이지1", new stageScene);
	SCENEMANAGER->addScene("로딩", new F_loadingScene);
	SCENEMANAGER->addScene("메인", new mainScene);
	SCENEMANAGER->addScene("게임오버", new gameoverScene);
	SCENEMANAGER->addScene("엔딩", new EndingScene);

	//현재씬 초기화
	SCENEMANAGER->changeScene("로딩");

	return S_OK;
}


//=================================================================================================
//	##	해제 release(void)	##
//=================================================================================================

void mainGame::release(void)
{
	//게임노드 해제
	gameNode::release();
}


//=================================================================================================
//	##	업데이트 update(void)	##
//=================================================================================================

void mainGame::update(void)
{
	//게임노드 업데이트
	gameNode::update();

	//씬 매니저 업데이트
	SCENEMANAGER->update();

	//_mapTool->update();
	SOUNDMANAGER->update();

	
	//SCENEMANAGER->update();
}

//=================================================================================================
//	##	랜더 render(HDC hdc)	##
//=================================================================================================

void mainGame::render(void)
{

	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);



	//씬 매니저 렌더
	SCENEMANAGER->render();


	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		TIMEMANAGER->render(getMemDC());
	}
	else
	{
		SetTextColor(getMemDC(), RGB(255, 255, 255));
	}


	// ## [ 끝 ] ## =================================================================================================

	this->getBackBuffer()->render(getHDC());

}




//=================================================================================================
//	##	함수 Function	##
//=================================================================================================
