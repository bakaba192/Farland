#include "stdafx.h"
#include "gameoverScene.h"

HRESULT gameoverScene::init(void)
{
	_alpha = 255;
	_Count = 0;
	_brighttening = true;
	_dark = false;
	_changeScene = false;
	img = IMAGEMANAGER->findImage("검은화면");
	gameover = IMAGEMANAGER->findImage("게임오버");
	
	return S_OK;
}

void gameoverScene::release(void)
{

}

void gameoverScene::update(void)
{
	if (_brighttening)
	{
		_alpha -= 5;
		if (_alpha == 0)
		{
			_brighttening = false;
		}
	}
	else
	{
		_Count++;
		if (_Count > 100)
		{
			_dark = true;
		}
	}

	if (_dark)
	{
		_alpha += 5;
		if (_alpha == 255)
		{
			_dark = false;
			_changeScene = true;
		}
	}

	if(_changeScene)
	{
		SCENEMANAGER->changeScene("메인");
	}

}

void gameoverScene::render(void)
{
	gameover->render(getMemDC());
	img->alphaRender(getMemDC(),_alpha);
}
