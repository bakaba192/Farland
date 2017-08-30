#include "stdafx.h"
#include "loading.h"


//=============================================================
//	## loadItem ## (�ε������ Ŭ����)
//=============================================================
HRESULT loadItem::initForImage(string keyName, int width, int height)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_0;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_1;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_2;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, const char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = maxFrameX;
	_imageResource.frameY = maxFrameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, const char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = maxFrameX;
	_imageResource.frameY = maxFrameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

//=============================================================
//	## loading ## (�ε� Ŭ����)
//=============================================================

HRESULT loading::init(void)
{
	//�ε�ȭ�� ��׶��� �̹��� �ʱ�ȭ
	_background = IMAGEMANAGER->addImage("��׶���", "image/�ý���/title.bmp", WINSIZEX, WINSIZEY);

	////�ε��� �ʱ�ȭ
	_loadingBar = new progressBar;
	_loadingBar->init("image/�ý���/�����_��.bmp", "image/�ý���/�����_��.bmp", 20 , WINSIZEY - 50 , 600, 24);
	_loadingBar->setGauge(0, 0);

	//�ۼ�Ʈ �ʱ�ȭ
	//_loadingNumberImg = IMAGEMANAGER->addFrameImage("�ε�_����", "image/loadingNumberImg.bmp", 352, 36, 11, 1, true, RGB(255, 0, 255));


	//���� ������ �ʱ�ȭ
	_currentGauge = 0;

	return S_OK;
}

void loading::release(void)
{
	//�ε��� ����
	SAFE_DELETE(_loadingBar);
}

void loading::update(void)
{
	//�ε��� ������Ʈ
	_loadingBar->update();
}

void loading::render(void)
{
	//��׶��� ����
	_background->render(getMemDC());

	//�ε��� ����
	
	if (!_DoneLoading)
	{
		_loadingBar->render();
	}

	////�ε����� ����
	//if (_currentNumber >= 100) _loadingNumberImg->frameRender(getMemDC(), _loadingBar->getRect().right + 10, _loadingBar->getRect().top - 13, _currentNumber / 100, 1);
	//if (_currentNumber >= 10)_loadingNumberImg->frameRender(getMemDC(), _loadingBar->getRect().right + 42, _loadingBar->getRect().top - 13, _currentNumber % 100 / 10, 1);
	//_loadingNumberImg->frameRender(getMemDC(), _loadingBar->getRect().right + 74, _loadingBar->getRect().top - 13, _currentNumber % 10, 1);
	//_loadingNumberImg->frameRender(getMemDC(), _loadingBar->getRect().right + 106, _loadingBar->getRect().top - 13, 10, 1);

	//���� ��� ����
	//
	//char str[255];
	//GetCurrentDirectory(sizeof(str),str);

	////sprintf(str, "%s/%s", str, _currentFilName.c_str());
	//sprintf(str, "%s/%s", str, _currentKeyName.c_str());

	////strcpy(rote, _currentKeyName.c_str());
	////strcat(szDir, "\\env_sample.ini");

	//setFont(getMemDC(), 12, str, _loadingBar->getRect().left + 20, _loadingBar->getRect().top + 6, RGB(0, 0, 0));

}

void loading::loadImage(string keyName, int width, int height)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, width, height);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, x, y, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, x, y, width, height, maxFrameX, maxFrameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

/*�߿���*/
//�ε��Ϸ� �Ƴ�? (�ε��Ϸ��� ȭ����ȯ)
BOOL loading::loadingDone(void)
{
	//�ε��� �Ϸ� ��
	if (_currentGauge >= _vLoadItem.size())
	{
		_DoneLoading = true;
		return TRUE;
	}

	loadItem* item = _vLoadItem[_currentGauge];

	switch (item->getLoadingKind())
	{
	case LOAD_KIND_IMAGE_0:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
	}
	break;
	case LOAD_KIND_IMAGE_1:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.trans, img.transColor);
	}
	break;

	case LOAD_KIND_IMAGE_2:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.trans, img.transColor);
	}
	break;

	case LOAD_KIND_FRAMEIMAGE_0:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
	}
	break;

	case LOAD_KIND_FRAMEIMAGE_1:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
	}
	break;

	case LOAD_KIND_SOUND:
		break;
	}

	//��������� 1������
	_currentGauge++;

	//�ε��� �̹��� ����
	_loadingBar->setGauge(_currentGauge, _vLoadItem.size());

	//���� ��� ����
	//tagImageResource img = item->getImageResource();
	//_currentFilName = img.fileName;
	//_currentKeyName = img.keyName;
	
	//�ε� �����̹��� ���� - �� �Ȱ��� �ǹ�
	//_numberPerOne = _vLoadItem.size() / 100;
	//_currentNumber = _currentGauge / _numberPerOne;

	_currentNumber = _currentGauge * 100 / _vLoadItem.size();
	//_currentNumber = _currentGauge / (_vLoadItem.size() / 100);

	

	return FALSE;
}
