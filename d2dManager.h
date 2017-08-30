#pragma once
#include "singletonBase.h"
#include "d2dImage.h"

//=================================================================================================
//	##	이미지 매니저 함수 [ imageManager ] (헤드)	##
//=================================================================================================

class d2dManager : public singletonBase<d2dManager>
{
private:
	typedef map<string, d2dImage*> mapD2DImgList;				//맵으로 만든 이미지목록
	typedef map<string, d2dImage*>::iterator mapD2DImgIter;		//맵으로 만든 이미지목록의 반복자

private:
	mapD2DImgList _mD2DImgList;		//실제 이미지클래스를 담을 맵

public:

	//=================================================================================================
	//	##	[ d2d이미지 초기화 ]	##
	//=================================================================================================

	//이미지 매니저 초기화
	HRESULT init(void);
	//이미지 매니저 해제
	void release(void);


	//d2d이미지로 초기화 및 추가
	d2dImage* addImage(string strKey, const WCHAR* fileName);
	d2dImage* addFrameImage(string strKey, const WCHAR * fileName, int maxFrameX, int maxFrameY);



	// ## << 키값 찾기 및 삭제 >> ##
	//이미지 키값으로 찾기
	d2dImage* findImage(string strKey);
	//이미지 키값으로 삭제
	BOOL deleteImage(string strKey);
	////이미지 전체 삭제
	//BOOL deleteAll();


	//=================================================================================================
	//	## [ 일반 렌더 ] ##
	//=================================================================================================

	//렌더(좌표에 이미지 출력)
	void render(string strKey, HDC hdc, float alpha = 1.0);											//좌표 기본설정()
	void render(string strKey, HDC hdc, float destX, float destY, float alpha = 1.0);						//좌표 직접 입력
	//void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);		//잘라 붙이기

	//=================================================================================================
	//	## [ 회전 렌더 ] ##
	//=================================================================================================

	void rotationRender(string strKey, HDC hdc, float destX, float destY, float angle, ROTATION_CP RCP = RCP_CENTER, float alpha = 1.0);
	void rotationRender(string strKey, HDC hdc, float destX, float destY, float rotationX, float rotationY, float angle, ROTATION_CP RCP = RCP_CENTER, float alpha = 1.0);

	////=================================================================================================
	////	## [ 프레임 렌더 ] ##
	////=================================================================================================

	////프레임 랜더
	//void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float alpha = 1.0);
	void rFrameRender(string strKey, HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float angle, ROTATION_CP RCP = RCP_CENTER, float alpha = 1.0);
	void rFrameRender(string strKey, HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float rotationX, float rotationY, float angle, ROTATION_CP RCP = RCP_CENTER, float alpha = 1.0);

	////====================================================================
	////			## 루프렌더 ##
	////====================================================================

	//void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	//void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	////=================================================================================================
	////	## [ 사이즈 렌더 ] ##
	////=================================================================================================

	////사이즈 렌더
	//void sizeRender(string strKey, HDC hdc, int sizeW, int sizeH);
	//void sizeRender(string strKey, HDC hdc, int destX, int destY, int sizeW, int sizeH);

	////=================================================================================================
	////	## [  트렌스 렌더 ] ##
	////=================================================================================================

	//void transRender(string strKey, HDC hdc, bool isTrans, COLORREF color);
	//void transRender(string strKey, HDC hdc, int destX, int destY, bool isTrans, COLORREF color);


	////=================================================================================================
	////	## [ 특수 ] ##
	////=================================================================================================

	void xFrameRender(string strKey, HDC hdc, float destX, float destY, float lengthY, int currentFrameX, float angle, TELESCOPIC_DIRECTION TD = TD_CENTER, ROTATION_CP RCP = RCP_CENTER, float rotationX = 0.0f, float rotationY = 0.0f, float alpha = 1.0);
	//void setImageDC(string strKey, HDC hdc, int sizeW, int sizeH);


	//생성자, 소멸자
	d2dManager() {}
	~d2dManager() {}
};

