#include "stdafx.h"
#include "progressBar.h"


//ü�¹� �ʱ�ȭ(ü�¹� ���̹���Ű, ü�¹� ���̹���Ű, x, y, ���α���, ���α���)
HRESULT progressBar::init(char * frontImageKey, char * backImageKey, int x, int y, int width, int height)
{
	//ü�¹� ��ġ��ǥ �ʱ�ȭ
	_x = x;
	_y = y;

	//ü�¹� ����, ���α��� �ʱ�ȭ
	_width = width;
	_height = height;

	//ü�¹� ��Ʈ ��ġ �� ũ�� �ʱ�ȭ
	_rcProgress = RectMakeCP(x, y, width, height);

	//Ű������ �̹����̸�(~.bmp)�� �ٷ� �ʱ�ȭ
	char frontImage[128];
	char backImage[128];
	//�޸� ����ϰ� �о��ֱ�
	ZeroMemory(frontImage, sizeof(frontImage));
	ZeroMemory(backImage, sizeof(backImage));
	//~.bmp�� �����
	sprintf_s(frontImage, "%s", frontImageKey);
	sprintf_s(backImage, "%s", backImageKey);

	//ü�¹� �̹��� �ʱ�ȭ
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
	//������ �Ǵ� ������ ���ؼ� �ڿ� �ִ� �̹��� ���� ������Ų��
	_progressBarBack->render(getMemDC(), _rcProgress.left, _y);
	//�տ� �������� ü�¹� �̹��� ����
	_progressBarFront->render(getMemDC(), _rcProgress.left, _y,
		0, 0, _width, _progressBarFront->getHeight());
}

//ü�¹� ������ �����ϱ�
void progressBar::setGauge(float currentHp, float maxHp)
{
	_width = (currentHp / maxHp) * _progressBarBack->getWidth();
}

