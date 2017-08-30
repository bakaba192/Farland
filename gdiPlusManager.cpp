#include "stdafx.h"
#include "gdiPlusManager.h"

//=================================================================================================
//	##	GDI 이미지 매니저 [ gdiPlusManager ] (클래스)	##
//=================================================================================================

HRESULT gdiPlusManager::init(void)
{
	return S_OK;
}

void gdiPlusManager::release(void)
{
	this->deleteAll();
}


//=================================================================================================
//	## [ 이미지 초기화 ] ##
//=================================================================================================

gdipImage * gdiPlusManager::addImage(string strKey, const WCHAR* fileName, int maxFrameX, int maxFrameY)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	gdipImage* gdiImg = findImage(strKey);

	//추가하려는 이미지가 이미 존재 한다면 새로 만들지 않고 바로 리턴
	if (gdiImg) return gdiImg;

	//없으면 이미지 새로 생성
	gdiImg = new gdipImage;
	if (FAILED(gdiImg->init(fileName, maxFrameX, maxFrameY)))
	{
		SAFE_DELETE(gdiImg);
		return NULL;
	}

	/*STL 맵에 삽입*/
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mGdipImgList.insert(make_pair(strKey, gdiImg));

	return gdiImg;
}



// !! [ 키값 찾기 및 삭제 ] !! =================================================================================================

//이미지 키값으로 찾기
gdipImage * gdiPlusManager::findImage(string strKey)
{
	//해당키 검색
	mapGdipImgIter key = _mGdipImgList.find(strKey);

	//검색한 키를 찾음
	if (key != _mGdipImgList.end())
	{
		//값 반환
		return key->second;
	}

	//검색한 키로 이미지를 못찾았다면 NULL
	return NULL;
}

//삭제
BOOL gdiPlusManager::deleteAll()
{
	//맵 전체를 돌면서 지운다
	mapGdipImgIter iter = _mGdipImgList.begin();
	//for(;;)  == while(true)
	for (; iter != _mGdipImgList.end();)
	{
		//이미지가 있으면
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mGdipImgList.erase(iter);
		}
		else //없으면
		{
			++iter;
		}
	}

	//맵 전체를 삭제
	_mGdipImgList.clear();

	return TRUE;
}




//렌더
void gdiPlusManager::gdiFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiFrameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

