#pragma once
#include "gameNode.h"
#include "F_TileMapTool.h"
#include "stageScene.h"
#include "F_loadingScene.h"
#include "mainScene.h"
#include "gameoverScene.h"
#include "EndingScene.h"

//��� ���� �߰�

// ===== ## [ ���ΰ��� Ŭ���� ��� ] ## =====


//#define ImgMaxSizeW		3000			//�̹��� �ִ� ����ũ��

class mainGame : public gameNode
{
private:
	

public:
	//�ʼ�
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//������, �Ҹ���
	mainGame()  {}
	~mainGame() {}
};
