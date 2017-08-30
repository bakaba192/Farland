#include "stdafx.h"
#include "imageManager.h"

//=================================================================================================
//	##	이미지 매니저 함수 [ imageManager ] (클래스)	##
//=================================================================================================

HRESULT imageManager::init(void)
{
	return S_OK;
}

void imageManager::release(void)
{
	this->deleteAll();
}


//=================================================================================================
//	## [ 이미지 초기화 ] ##
//=================================================================================================


// !! [ 빈 비트맵 초기화 ] !! =================================================================================================
image * imageManager::addImage(string strKey, int width, int height)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재 한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	//없으면 이미지 새로 생성
	img = new image;
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL 맵의 핵심*/
	//키, 값 을 잊지 말도록
	//첫번째 first -> 키
	//두번째 second -> 값
	//추가하는 방법은 insert를 사용하되 키와밸류 두개를 동시에 추가해야 하니 
	//pair, make_pair를 사용하여 추가하면 된다

	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// !! [ 이미지 파일로 초기화(주 사용) ] !! =================================================================================================
image * imageManager::addImage(string strKey, const CHAR * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재 한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	//없으면 이미지 새로 생성
	img = new image;
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL 맵에 삽입*/
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// !! [ 이미지 파일로 초기화(주로 사용) ] - 시작지점까지 초기화 가능 !! =================================================================================================
image * imageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재 한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	//없으면 이미지 새로 생성
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL 맵에 삽입*/
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}


// !! [ 프레임 이미지 초기화(주로 사용) ] !! =================================================================================================
image * imageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재 한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	//없으면 이미지 새로 생성
	img = new image;
	if (FAILED(img->init(fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL 맵에 삽입*/
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// !! [ 프레임 이미지 초기화(주로 사용) - 시작지점까지 초기화 가능 ] !! =================================================================================================
image * imageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재 한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	//없으면 이미지 새로 생성
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL 맵에 삽입*/
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//스케일 이미지 초기화 (!!특수!!)
image * imageManager::addScaleImage(string strKey, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재 한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	//없으면 이미지 새로 생성
	img = new image;
	if (FAILED(img->scaleInit(width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL 맵의 핵심*/

	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}



// !! [ 키값 찾기 및 삭제 ] !! =================================================================================================

//이미지 키값으로 찾기
image * imageManager::findImage(string strKey)
{
	//해당키 검색
	mapImageIter key = _mImageList.find(strKey);

	//검색한 키를 찾음
	if (key != _mImageList.end())
	{
		//값 반환
		return key->second;
	}

	//검색한 키로 이미지를 못찾았다면 NULL
	return NULL;
}

//이미지 키값으로 삭제
BOOL imageManager::deleteImage(string strKey)
{
	//해당키 검색
	mapImageIter key = _mImageList.find(strKey);

	//검색한 키를 찾았다면
	if (key != _mImageList.end())
	{
		//이미지 해제
		key->second->release();
		//메모리 해제
		SAFE_DELETE(key->second);
		//맵의 반복자 삭제
		_mImageList.erase(key);

		return TRUE;
	}

	return FALSE;
}

//이미지 전체 삭제
BOOL imageManager::deleteAll()
{
	//맵 전체를 돌면서 지운다
	mapImageIter iter = _mImageList.begin();
	//for(;;)  == while(true)
	for (; iter != _mImageList.end();)
	{
		//이미지가 있으면
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else //없으면
		{
			++iter;
		}
	}

	//맵 전체를 삭제
	_mImageList.clear();

	return TRUE;
}


//=================================================================================================
//	## [ 일반 렌더 ] ##
//=================================================================================================

//렌더(좌표에 이미지 출력)
void imageManager::render(string strKey, HDC hdc)
{
	//이미지를 찾아서 렌더
	image* img = findImage(strKey);
	if (img) img->render(hdc);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	//이미지를 찾아서 렌더
	image* img = findImage(strKey);

	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//이미지를 찾아서 렌더
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::focusRender(string strKey, HDC hdc, int destX, int destY)
{
	//이미지를 찾아서 렌더
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX + FOCUSMANAGER->getFocusX(), destY + FOCUSMANAGER->getFocusY());
}



//=================================================================================================
//	## [ 알파 렌더 ] ##
//=================================================================================================

//알파 렌더
void imageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	//이미지를 찾아서 렌더
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	//이미지를 찾아서 렌더
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//이미지를 찾아서 렌더
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

void imageManager::focusAlphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	//이미지를 찾아서 렌더
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX + FOCUSMANAGER->getFocusX(), destY + FOCUSMANAGER->getFocusY(), alpha);
}


//=================================================================================================
//	## [ 프레임 렌더 ] ##
//=================================================================================================

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	//이미지를 찾아서 렌더
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//이미지를 찾아서 렌더
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void imageManager::focusFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//이미지를 찾아서 렌더
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX + FOCUSMANAGER->getFocusX(), destY + FOCUSMANAGER->getFocusY(), currentFrameX, currentFrameY);
}

//====================================================================
//			## 루프렌더 ##
//====================================================================
void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//이미지를 찾아서 그냥 렌더시키면됨
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void imageManager::focusLoopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//이미지를 찾아서 그냥 렌더시키면됨
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX + FOCUSMANAGER->getFocusX(), offsetY + FOCUSMANAGER->getFocusY());
}

void imageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
}



//=================================================================================================
//	## [ 사이즈 렌더 ] ##
//=================================================================================================

void imageManager::sizeRender(string strKey, HDC hdc, int sizeW, int sizeH)
{
	image* img = findImage(strKey);
	if (img) img->sizeRender(hdc, sizeW, sizeH);
}

//사이즈 렌더
void imageManager::sizeRender(string strKey, HDC hdc, int destX, int destY, int sizeW, int sizeH)
{
	image* img = findImage(strKey);
	if (img) img->sizeRender(hdc, destX, destY, sizeW, sizeH);
}


//=================================================================================================
//	## [  트렌스 렌더 ] ##
//=================================================================================================

void imageManager::transRender(string strKey, HDC hdc, bool isTrans, COLORREF color)
{
	image* img = findImage(strKey);
	if (img) img->transRender(hdc, isTrans, color);
}

void imageManager::transRender(string strKey, HDC hdc, int destX, int destY, bool isTrans, COLORREF color)
{
	image* img = findImage(strKey);
	if (img) img->transRender(hdc, destX, destY, isTrans, color);
}


//=================================================================================================
//	## [ 특수 ] ##
//=================================================================================================




void imageManager::setImageDC(string strKey, HDC hdc, int sizeW, int sizeH)
{
	image* img = findImage(strKey);
	if (img) img->setImageDC(hdc, sizeW, sizeH);
}

//====================================================================
//			## 프레임알파렌더 ##
//====================================================================	
void imageManager::frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	image* img = findImage(strKey);
	if(img) img->frameAlphaRender(hdc, destX, destY, currentFrameX, currentFrameY, alpha);
}

void imageManager::focusFrameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->frameAlphaRender(hdc, destX + FOCUSMANAGER->getFocusX(), destY + FOCUSMANAGER->getFocusY(), currentFrameX, currentFrameY, alpha);
}
