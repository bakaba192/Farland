#include "stdafx.h"
#include "stateBar.h"

HRESULT stateBar::init(char * frontImageKey, char * backImageKey, int x, int y)
{
	//체력바 위치좌표 초기화
	_x = x;
	_y = y;

	
	

	//자르기 시작지점 초기화
	_cutStartX = 0;
	_cutStartY = 0;

	//체력바 렉트 위치 및 크기 초기화
	//_rcProgress = RectMakeCenter(x, y, width, height);

	//키값으로 이미지이름(~.bmp)을 바로 초기화
	char frontImage[128];
	char backImage[128];
	//메모리 깔끔하게 밀어주기
	//ZeroMemory(frontImage, sizeof(frontImage));
	//ZeroMemory(backImage, sizeof(backImage));
	////~.bmp로 만들기
	//sprintf(frontImage, "%s.bmp", frontImageKey);
	//sprintf(backImage, "%s.bmp", backImageKey);

	//체력바 이미지 초기화
	_progressBarFront = IMAGEMANAGER->findImage(frontImageKey);
	_progressBarBack = IMAGEMANAGER->findImage(backImageKey);

	//체력바 가로, 세로길이 초기화
	_width = _progressBarBack->getWidth();
	_height = _progressBarBack->getHeight();
	_maxWidth = _progressBarBack->getWidth();

	return S_OK;
}

void stateBar::release(void)
{
}

void stateBar::update(void)
{
}

void stateBar::render(void)
{
	//렌더링 되는 순서의 의해서 뒤에 있는 이미지 먼저 렌더시킨다
	_progressBarBack->render(getMemDC(), _x, _y, 0,0,_maxWidth, _height);
	//앞에 보여지는 체력바 이미지 렌더
	_progressBarFront->render(getMemDC(), _x + _cutStartX, _y + _cutStartY,
		_cutStartX, _cutStartY, _width - _cutStartX, _height - _cutStartY);
}

void stateBar::setGauge(float currentNum, float maxNum, enumBarState barState)
{
	_maxWidth = maxNum;
	if (currentNum >= maxNum) currentNum = maxNum;
	if (currentNum <= 0) currentNum = 0;
	if (barState == BAR_RIGHT)
	{
		_width = currentNum;//   (currentNum /  maxNum) * _progressBarBack->getWidth();
	}
	else if (barState == BAR_LEFT)
	{
		_cutStartX = _progressBarBack->getWidth() - ((currentNum / maxNum) * _progressBarBack->getWidth());

	}
	else if (barState == BAR_UP)
	{
		_cutStartY = _progressBarBack->getHeight() - ((currentNum / maxNum) * _progressBarBack->getHeight());
	}
	

}
