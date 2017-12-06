#pragma once
#include "gameNode.h"
#include "F_TileMapTool.h"
#include "stageScene.h"
#include "F_loadingScene.h"
#include "mainScene.h"
#include "gameoverScene.h"
#include "EndingScene.h"

//헤더 파일 추가

// ===== ## [ 메인게임 클래스 헤드 ] ## =====


//#define ImgMaxSizeW		3000			//이미지 최대 가로크기

class mainGame : public gameNode
{
private:
	

public:
	//필수
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//생성자, 소멸자
	mainGame()  {}
	~mainGame() {}
};
