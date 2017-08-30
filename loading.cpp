#include "stdafx.h"
#include "loading.h"


//=============================================================
//	## loadItem ## (로드아이템 클래스)
//=============================================================
HRESULT loadItem::initForImage(string keyName, int width, int height)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_0;

	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_1;

	//이미지 구조체 초기화
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
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_2;

	//이미지 구조체 초기화
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
	//로딩종류 초기화
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	//이미지 구조체 초기화
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
	//로딩종류 초기화
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	//이미지 구조체 초기화
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
//	## loading ## (로딩 클래스)
//=============================================================

HRESULT loading::init(void)
{
	//로딩화면 백그라운드 이미지 초기화
	_background = IMAGEMANAGER->addImage("백그라운드", "image/시스템/title.bmp", WINSIZEX, WINSIZEY);

	////로딩바 초기화
	_loadingBar = new progressBar;
	_loadingBar->init("image/시스템/진행바_앞.bmp", "image/시스템/진행바_뒤.bmp", 20 , WINSIZEY - 50 , 600, 24);
	_loadingBar->setGauge(0, 0);

	//퍼센트 초기화
	//_loadingNumberImg = IMAGEMANAGER->addFrameImage("로딩_숫자", "image/loadingNumberImg.bmp", 352, 36, 11, 1, true, RGB(255, 0, 255));


	//현재 게이지 초기화
	_currentGauge = 0;

	return S_OK;
}

void loading::release(void)
{
	//로딩바 해제
	SAFE_DELETE(_loadingBar);
}

void loading::update(void)
{
	//로딩바 업데이트
	_loadingBar->update();
}

void loading::render(void)
{
	//백그라운드 렌더
	_background->render(getMemDC());

	//로딩바 렌더
	
	if (!_DoneLoading)
	{
		_loadingBar->render();
	}

	////로딩숫자 렌더
	//if (_currentNumber >= 100) _loadingNumberImg->frameRender(getMemDC(), _loadingBar->getRect().right + 10, _loadingBar->getRect().top - 13, _currentNumber / 100, 1);
	//if (_currentNumber >= 10)_loadingNumberImg->frameRender(getMemDC(), _loadingBar->getRect().right + 42, _loadingBar->getRect().top - 13, _currentNumber % 100 / 10, 1);
	//_loadingNumberImg->frameRender(getMemDC(), _loadingBar->getRect().right + 74, _loadingBar->getRect().top - 13, _currentNumber % 10, 1);
	//_loadingNumberImg->frameRender(getMemDC(), _loadingBar->getRect().right + 106, _loadingBar->getRect().top - 13, 10, 1);

	//파일 경로 렌더
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

/*중요함*/
//로딩완료 됐냐? (로딩완료후 화면전환)
BOOL loading::loadingDone(void)
{
	//로딩이 완료 됨
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

	//현재게이지 1씩증가
	_currentGauge++;

	//로딩바 이미지 변경
	_loadingBar->setGauge(_currentGauge, _vLoadItem.size());

	//파일 경로 변경
	//tagImageResource img = item->getImageResource();
	//_currentFilName = img.fileName;
	//_currentKeyName = img.keyName;
	
	//로딩 숫자이미지 변경 - 다 똑같은 의미
	//_numberPerOne = _vLoadItem.size() / 100;
	//_currentNumber = _currentGauge / _numberPerOne;

	_currentNumber = _currentGauge * 100 / _vLoadItem.size();
	//_currentNumber = _currentGauge / (_vLoadItem.size() / 100);

	

	return FALSE;
}
