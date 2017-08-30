#pragma once
#include "singletonBase.h"
#include "image.h"

//=================================================================================================
//	##	이미지 매니저 함수 [ imageManager ] (헤드)	##
//=================================================================================================

class imageManager : public singletonBase<imageManager>
{
private:
	typedef map<string, image*> mapImageList;				//맵으로 만든 이미지목록
	typedef map<string, image*>::iterator mapImageIter;		//맵으로 만든 이미지목록의 반복자

private:
	mapImageList _mImageList;		//실제 이미지클래스를 담을 맵

public:

//=================================================================================================
//	##	[ 이미지 초기화 ]	##
//=================================================================================================

	//이미지 매니저 초기화
	HRESULT init(void);
	//이미지 매니저 해제
	void release(void);

	//비 비트맵으로 초기화 및 추가
	image* addImage(string strKey, int width, int height);

	//이미지 파일로 초기화 및 추가(주로 사용)
	image* addImage(string strKey, const CHAR* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//이미지 파일로 초기화 및 추가(주로 사용) - 시작지점까지 초기화 가능
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//프레임 이미지 초기화 및 추가(주로 사용)
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//프레임 이미지 초기화 및 추가(주로 사용) - 시작지점까지 초기화 가능
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//스케일 이미지 초기화 (!!특수!!)
	image* addScaleImage(string strKey, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));


	// ## << 키값 찾기 및 삭제 >> ##
	//이미지 키값으로 찾기
	image* findImage(string strKey);
	//이미지 키값으로 삭제
	BOOL deleteImage(string strKey);
	//이미지 전체 삭제
	BOOL deleteAll();


//=================================================================================================
//	## [ 일반 렌더 ] ##
//=================================================================================================

	//렌더(좌표에 이미지 출력)
	void render(string strKey, HDC hdc);											//좌표 기본설정()
	void render(string strKey, HDC hdc, int destX, int destY);						//좌표 직접 입력
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);		//잘라 붙이기

	void focusRender(string strKey, HDC hdc, int destX, int destY);						//좌표 직접 입력

//=================================================================================================
//	## [ 알파 렌더 ] ##
//=================================================================================================

	//알파 렌더
	void alphaRender(string strKey, HDC hdc, BYTE alpha);							//좌표 기본설정()
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);	//좌표 직접 입력
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);		//잘라 붙이기
	
	void focusAlphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);	//좌표 직접 입력


//=================================================================================================
//	## [ 프레임 렌더 ] ##
//=================================================================================================

	//프레임 랜더
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void focusFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

//====================================================================
//			## 루프렌더 ##
//====================================================================

void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
void focusLoopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

//=================================================================================================
//	## [ 사이즈 렌더 ] ##
//=================================================================================================

	//사이즈 렌더
	void sizeRender(string strKey, HDC hdc, int sizeW, int sizeH);
	void sizeRender(string strKey, HDC hdc, int destX, int destY, int sizeW, int sizeH);

//=================================================================================================
//	## [  트렌스 렌더 ] ##
//=================================================================================================

	void transRender(string strKey, HDC hdc, bool isTrans, COLORREF color);
	void transRender(string strKey, HDC hdc, int destX, int destY, bool isTrans, COLORREF color);


//=================================================================================================
//	## [ 특수 ] ##
//=================================================================================================

	void setImageDC(string strKey,HDC hdc, int sizeW, int sizeH);

	void frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	void focusFrameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);
	



	//생성자, 소멸자
	imageManager() {}
	~imageManager() {}
};

