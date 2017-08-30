#pragma once
#include "singletonBase.h"
#include "gdipImage.h"

//=================================================================================================
//	##	GDI 이미지 매니저 [ gdiPlusManager ] (헤드)	##
//=================================================================================================

class gdiPlusManager :	public singletonBase<gdiPlusManager>
{
private:
	typedef map<string, gdipImage*> mapGdipImgList;				//맵으로 만든 이미지목록
	typedef map<string, gdipImage*>::iterator mapGdipImgIter;		//맵으로 만든 이미지목록의 반복자

private:
	mapGdipImgList _mGdipImgList;		//실제 이미지클래스를 담을 맵

private:


public:
	//초기화
	HRESULT init(void);
	//삭제
	void release(void);


	//이미지 초기화
	gdipImage * addImage(string strKey, const WCHAR * fileName, int maxFrameX, int maxFrameY);
	//이미지 키값으로 찾기
	gdipImage * findImage(string strKey);

	BOOL deleteAll();

	//렌더
	void gdiFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	gdiPlusManager() {}
	~gdiPlusManager() {}
};

