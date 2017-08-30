#include "stdafx.h"
#include "stateBar.h"

HRESULT stateBar::init(char * frontImageKey, char * backImageKey, int x, int y)
{
	//ü�¹� ��ġ��ǥ �ʱ�ȭ
	_x = x;
	_y = y;

	
	

	//�ڸ��� �������� �ʱ�ȭ
	_cutStartX = 0;
	_cutStartY = 0;

	//ü�¹� ��Ʈ ��ġ �� ũ�� �ʱ�ȭ
	//_rcProgress = RectMakeCenter(x, y, width, height);

	//Ű������ �̹����̸�(~.bmp)�� �ٷ� �ʱ�ȭ
	char frontImage[128];
	char backImage[128];
	//�޸� ����ϰ� �о��ֱ�
	//ZeroMemory(frontImage, sizeof(frontImage));
	//ZeroMemory(backImage, sizeof(backImage));
	////~.bmp�� �����
	//sprintf(frontImage, "%s.bmp", frontImageKey);
	//sprintf(backImage, "%s.bmp", backImageKey);

	//ü�¹� �̹��� �ʱ�ȭ
	_progressBarFront = IMAGEMANAGER->findImage(frontImageKey);
	_progressBarBack = IMAGEMANAGER->findImage(backImageKey);

	//ü�¹� ����, ���α��� �ʱ�ȭ
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
	//������ �Ǵ� ������ ���ؼ� �ڿ� �ִ� �̹��� ���� ������Ų��
	_progressBarBack->render(getMemDC(), _x, _y, 0,0,_maxWidth, _height);
	//�տ� �������� ü�¹� �̹��� ����
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
