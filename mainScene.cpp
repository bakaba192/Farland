#include "stdafx.h"
#include "mainScene.h"


HRESULT mainScene::init()
{
	//_nextScene = nullptr;
	_isSceneChange = false;
	_alpha = 255;
	_black = IMAGEMANAGER->findImage("검은화면");
	_town = IMAGEMANAGER->findImage("마을");

	

	_stage[0] = RectMake(60, 360, 128, 64); 
	_stage[1] = RectMake(500, 10, 128, 64);
	_stage[2] = RectMake(500, 300, 128, 64);
	_stage[3] = RectMake(300, 180, 128, 64);//맵툴

	_mouse = RectMake(_ptMouse.x, _ptMouse.y, 40, 20);

	return S_OK;
}

void mainScene::release(void)
{

}

void mainScene::update(void)
{

	if (ENDINGMANAGER->getStageClear()[0] && ENDINGMANAGER->getStageClear()[1] && ENDINGMANAGER->getStageClear()[2])
	{
		_nextScene = "엔딩";
		_isSceneChange = true;
	}

	_mouse = RectMake(_ptMouse.x, _ptMouse.y, 40, 20);

	if (PtInRect(&_stage[0], _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !ENDINGMANAGER->getStageClear()[0])
		{
			MAPDATA->getStageNumber() = 1;
			_nextScene = "스테이지1";
			_isSceneChange = true;
		}
	}

	if (PtInRect(&_stage[1], _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !ENDINGMANAGER->getStageClear()[1])
		{
			MAPDATA->getStageNumber() = 2;
			_nextScene = "스테이지1";
			_isSceneChange = true;
		}
	}

	if (PtInRect(&_stage[2], _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !ENDINGMANAGER->getStageClear()[2])
		{
			MAPDATA->getStageNumber() = 3;
			_nextScene = "스테이지1";
			_isSceneChange = true;
		}
	}

	if (PtInRect(&_stage[3], _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_nextScene = "맵툴";
			MAPDATA->getStageNumber() = 1;
			_isSceneChange = true;
		}
	}

	if (_isSceneChange)
	{
		_alpha += 4;
		if (_alpha >= 255)
		{			
			SCENEMANAGER->changeScene(_nextScene);
		}
	}
	else
	{
		_alpha -= 4;
		if (_alpha < 0)
		{
			_alpha = 0;
		}
	}
}

void mainScene::render(void)
{
	_town->render(getMemDC());

	//RectangleMake(getMemDC(), _mouse.left + 20, _mouse.top, 30, 40);
	//TextOut(getMemDC(), _mouse.left + 20, _mouse.top, to_string(_ptMouse.x).c_str(), strlen(to_string(_ptMouse.x).c_str()));
	//TextOut(getMemDC(), _mouse.left + 20, _mouse.top + 20, to_string(_ptMouse.y).c_str(), strlen(to_string(_ptMouse.y).c_str()));

	if (KEYMANAGER->isToggleKey(VK_F4))
	{
		for (int i = 0; i < 4; i++)
		{
			IMAGEMANAGER->frameRender("표지판", getMemDC(), _stage[i].left, _stage[i].top, 0, i);
		}
	}


	for (int i = 0; i < 4; i++)
	{
		if (PtInRect(&_stage[i], _ptMouse))
		{
			IMAGEMANAGER->frameRender("표지판", getMemDC(), _stage[i].left, _stage[i].top,0,i);
		}
	}

	_black->alphaRender(getMemDC(), _alpha);
}
