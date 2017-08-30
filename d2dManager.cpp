#include "stdafx.h"
#include "d2dManager.h"


//=================================================================================================
//	##	d2d 매니저 함수 [ d2dManager ] (클래스)	##
//=================================================================================================

HRESULT d2dManager::init(void)
{
	return S_OK;
}
void d2dManager::release(void)
{
	//this->deleteAll();
}


//=================================================================================================
//	## [ 이미지 초기화 ] ##
//=================================================================================================

d2dImage* d2dManager::addImage(string strKey, const WCHAR* fileName)
{
	d2dImage* d2dImg = findImage(strKey);

	//추가하려는 이미지가 존재하는지 키값으로 확인
	//추가하려는 이미지가 이미 존재 한다면 새로 만들지 않고 바로 리턴
	if (d2dImg) return d2dImg;

	//없으면 이미지 새로 생성
	d2dImg = new d2dImage;
	if (FAILED(d2dImg->init(fileName)))
	{
		SAFE_DELETE(d2dImg);
		return NULL;
	}

	/*STL 맵에 삽입*/
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mD2DImgList.insert(make_pair(strKey, d2dImg));


	return d2dImg;
}

d2dImage * d2dManager::addFrameImage(string strKey, const WCHAR * fileName, int maxFrameX, int maxFrameY)
{
	d2dImage* d2dImg = findImage(strKey);

	//추가하려는 이미지가 존재하는지 키값으로 확인
	//추가하려는 이미지가 이미 존재 한다면 새로 만들지 않고 바로 리턴
	if (d2dImg) return d2dImg;

	//없으면 이미지 새로 생성
	d2dImg = new d2dImage;
	if (FAILED(d2dImg->frameInit(fileName, maxFrameX, maxFrameY)))
	{
		SAFE_DELETE(d2dImg);
		return NULL;
	}

	/*STL 맵에 삽입*/
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mD2DImgList.insert(make_pair(strKey, d2dImg));


	return d2dImg;
}




// !! [ 키값 찾기 및 삭제 ] !! =================================================================================================

//이미지 키값으로 찾기
d2dImage* d2dManager::findImage(string strKey)
{
	//해당키 검색
	mapD2DImgIter key = _mD2DImgList.find(strKey);

	//검색한 키를 찾음
	if (key != _mD2DImgList.end())
	{
		//값 반환
		return key->second;
	}

	//검색한 키로 이미지를 못찾았다면 NULL
	return NULL;
}

//이미지 키값으로 삭제
BOOL d2dManager::deleteImage(string strKey)
{
	//해당키 검색
	mapD2DImgIter key = _mD2DImgList.find(strKey);

	//검색한 키를 찾았다면
	if (key != _mD2DImgList.end())
	{
		//이미지 해제
		key->second->release();
		//메모리 해제
		SAFE_DELETE(key->second);
		//맵의 반복자 삭제
		_mD2DImgList.erase(key);

		return TRUE;
	}

	return FALSE;
}


//=================================================================================================
//	## [ 일반 렌더 ] ##
//=================================================================================================

void d2dManager::render(string strKey, HDC hdc, float alpha)
{
	//이미지를 찾아서 렌더
	d2dImage* d2dImg = findImage(strKey);
	if (d2dImg) d2dImg->render(hdc, alpha);
}

void d2dManager::render(string strKey, HDC hdc, float destX, float destY, float alpha)
{
	//이미지를 찾아서 렌더
	d2dImage* d2dImg = findImage(strKey);
	if (d2dImg) d2dImg->render(hdc, alpha);
}

//=================================================================================================
//	## [ 회전 렌더 ] ##
//=================================================================================================

void d2dManager::rotationRender(string strKey, HDC hdc, float destX, float destY, float angle, ROTATION_CP RCP, float alpha)
{
	//이미지를 찾아서 렌더
	d2dImage* d2dImg = findImage(strKey);
	if (d2dImg) d2dImg->rotationRender(hdc, destX, destY, angle, RCP, alpha);
}

void d2dManager::rotationRender(string strKey, HDC hdc, float destX, float destY, float rotationX, float rotationY, float angle, ROTATION_CP RCP, float alpha)
{
	//이미지를 찾아서 렌더
	d2dImage* d2dImg = findImage(strKey);
	if (d2dImg) d2dImg->rotationRender(hdc, destX, destY, angle, rotationX, rotationY, RCP, alpha);
}

////=================================================================================================
////	## [ 프레임 렌더 ] ##
////=================================================================================================

void d2dManager::frameRender(string strKey, HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float alpha)
{
	//이미지를 찾아서 렌더
	d2dImage* d2dImg = findImage(strKey);
	if (d2dImg) d2dImg->frameRender(hdc, destX, destY, currentFrameX, currentFrameY, alpha);
}

void d2dManager::rFrameRender(string strKey, HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float angle, ROTATION_CP RCP, float alpha)
{
	//이미지를 찾아서 렌더
	d2dImage* d2dImg = findImage(strKey);
	if (d2dImg) d2dImg->rFrameRender(hdc, destX, destY, currentFrameX, currentFrameY, angle, RCP, alpha);
}

void d2dManager::rFrameRender(string strKey, HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float rotationX, float rotationY, float angle, ROTATION_CP RCP, float alpha)
{
	//이미지를 찾아서 렌더
	d2dImage* d2dImg = findImage(strKey);
	if (d2dImg) d2dImg->rFrameRender(hdc, destX, destY, currentFrameX, currentFrameY, rotationX, rotationY, angle, RCP, alpha);
}


////=================================================================================================
////	## [ 특수 ] ##
////=================================================================================================

void d2dManager::xFrameRender(string strKey, HDC hdc, float destX, float destY, float lengthY, int currentFrameX, float angle, TELESCOPIC_DIRECTION TD, ROTATION_CP RCP, float rotationX, float rotationY, float alpha)
{
	//이미지를 찾아서 렌더
	d2dImage* d2dImg = findImage(strKey);
	if (d2dImg) d2dImg->xFrameRender(hdc, destX, destY, lengthY, currentFrameX, angle, TD ,RCP, rotationX, rotationY, alpha);
}
