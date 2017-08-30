#include "stdafx.h"
#include "EndingScene.h"


HRESULT EndingScene::init(void)
{
	_dark = false;
	_alpha = 255;
	return S_OK;
}

void EndingScene::release(void)
{
}

void EndingScene::update(void)
{
	if (!_dark)
	{
		_alpha -= 1;
		if (_alpha < 0)
		{
			_alpha = 0;
		}
	}
	else
	{
		_alpha += 1;
		if (_alpha > 255)
		{
			_alpha = 255;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_dark = true;
	}

	if ((_dark == true) && _alpha == 255)
	{
		//exit(0);
	}

}

void EndingScene::render(void)
{
	IMAGEMANAGER->render("엔딩", getMemDC(), 0, 50);
	IMAGEMANAGER->alphaRender("검은화면", getMemDC(), _alpha);

}
