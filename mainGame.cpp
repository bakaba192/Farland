#include "stdafx.h"
#include "mainGame.h"

//===== ## [ ���ΰ��� Ŭ���� ] ## =====

//=================================================================================================
//	##	�ʱ�ȭ init(void)	##
//=================================================================================================

HRESULT mainGame::init(void)
{
	//���ӳ�� �ʱ�ȭ
	gameNode::init(TRUE);

	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	//�� �߰�
	SCENEMANAGER->addScene("����", new F_TileMapTool);
	SCENEMANAGER->addScene("��������1", new stageScene);
	SCENEMANAGER->addScene("�ε�", new F_loadingScene);
	SCENEMANAGER->addScene("����", new mainScene);
	SCENEMANAGER->addScene("���ӿ���", new gameoverScene);
	SCENEMANAGER->addScene("����", new EndingScene);

	//����� �ʱ�ȭ
	SCENEMANAGER->changeScene("�ε�");

	return S_OK;
}


//=================================================================================================
//	##	���� release(void)	##
//=================================================================================================

void mainGame::release(void)
{
	//���ӳ�� ����
	gameNode::release();
}


//=================================================================================================
//	##	������Ʈ update(void)	##
//=================================================================================================

void mainGame::update(void)
{
	//���ӳ�� ������Ʈ
	gameNode::update();

	//�� �Ŵ��� ������Ʈ
	SCENEMANAGER->update();

	//_mapTool->update();
	SOUNDMANAGER->update();

	
	//SCENEMANAGER->update();
}

//=================================================================================================
//	##	���� render(HDC hdc)	##
//=================================================================================================

void mainGame::render(void)
{

	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);



	//�� �Ŵ��� ����
	SCENEMANAGER->render();


	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		TIMEMANAGER->render(getMemDC());
	}
	else
	{
		SetTextColor(getMemDC(), RGB(255, 255, 255));
	}


	// ## [ �� ] ## =================================================================================================

	this->getBackBuffer()->render(getHDC());

}




//=================================================================================================
//	##	�Լ� Function	##
//=================================================================================================
