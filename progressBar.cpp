#include "stdafx.h"
#include "progressBar.h"


//체력바 초기화(체력바 앞이미지키, 체력바 뒤이미지키, x, y, 가로길이, 세로길이)
HRESULT progressBar::init(char * frontImageKey, char * backImageKey, int x, int y, int width, int height)
{
	//체력바 위치좌표 초기화
	_x = x;
	_y = y;

	//체력바 가로, 세로길이 초기화
	_width = width;
	_height = height;

	//체력바 렉트 위치 및 크기 초기화
	_rcProgress = RectMakeCP(x, y, width, height);

	//키값으로 이미지이름(~.bmp)을 바로 초기화
	char frontImage[128];
	char backImage[128];
	//메모리 깔끔하게 밀어주기
	ZeroMemory(frontImage, sizeof(frontImage));
	ZeroMemory(backImage, sizeof(backImage));
	//~.bmp로 만들기
	sprintf_s(frontImage, "%s", frontImageKey);
	sprintf_s(backImage, "%s", backImageKey);

	//체력바 이미지 초기화
	_progressBarFront = IMAGEMANAGER->addImage(frontImageKey, frontImage, x, y, width, height, true, RGB(255, 0, 255));
	_progressBarBack = IMAGEMANAGER->addImage(backImageKey, backImage, x, y, width, height, true, RGB(255, 0, 255));

	return S_OK;
}

void progressBar::release(void)
{
}

void progressBar::update(void)
{
	_rcProgress = RectMakeCP(_x + _progressBarBack->getWidth() / 2,
		_y + _progressBarBack->getHeight() / 2,
		_progressBarBack->getWidth(),
		_progressBarBack->getHeight());
}

void progressBar::render(void)
{
	//렌더링 되는 순서의 의해서 뒤에 있는 이미지 먼저 렌더시킨다
	_progressBarBack->render(getMemDC(), _rcProgress.left, _y);
	//앞에 보여지는 체력바 이미지 렌더
	_progressBarFront->render(getMemDC(), _rcProgress.left, _y,
		0, 0, _width, _progressBarFront->getHeight());
}

//체력바 게이지 세팅하기
void progressBar::setGauge(float currentHp, float maxHp)
{
	_width = (currentHp / maxHp) * _progressBarBack->getWidth();
}

