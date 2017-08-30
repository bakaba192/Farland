#include "stdafx.h"
#include "d2dImage.h"




//=================================================================================================
//	##	D2D 이미지 [ D2D Image ] (클래스)	##
//=================================================================================================
d2dImage::d2dImage() : _d2dInfo(NULL)
{
}

d2dImage::~d2dImage()
{
}


//=================================================================================================
//	##	초기화	##
//=================================================================================================

//일반 초기화
HRESULT d2dImage::init(const WCHAR * fileName)
{
	// 재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 해줄것!
	if (_d2dInfo != NULL) this->release();

	//d2d 만들기
	this->createD2D(fileName);

	//이미지 정보 새로 생성 후 초기화하기
	_d2dInfo = new D2D_INFO;
	//렌더 넣기
	//_d2dInfo->pDCRT->CreateBitmapFromWicBitmap(pWicBitmap,NULL, &_d2dInfo->pD2DBitmap);
	//pDCRT->CreateBitmapFromWicBitmap(pWicBitmap, NULL, &pD2DBitmap);
	UINT sizeW;
	UINT sizeH;
	pWicBitmap->GetSize(&sizeW, &sizeH);
	_d2dInfo->width = sizeW;
	_d2dInfo->height = sizeH;
	_d2dInfo->RectF = { 0,0, (float)sizeW , (float)sizeH };

	//디코더들 해제
	pWicImageDecoder->Release();
	pWicFrameDecoder->Release();
	//pWicBitmap->Release();

	//wic팩토리 해제
	pWicFactory->Release();

	return S_OK;
}

//일반 초기화 - 위치좌표
HRESULT d2dImage::init(const WCHAR * fileName, float x, float y)
{
	// 재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 해줄것!
	if (_d2dInfo != NULL) this->release();

	//d2d 만들기
	this->createD2D(fileName);

	//이미지 정보 새로 생성 후 초기화하기
	_d2dInfo = new D2D_INFO;
	UINT sizeW;
	UINT sizeH;
	pWicBitmap->GetSize(&sizeW, &sizeH);
	_d2dInfo->width = sizeW;
	_d2dInfo->height = sizeH;
	_d2dInfo->RectF = { 0,0, (float)sizeW , (float)sizeH };
	_d2dInfo->x = x;
	_d2dInfo->x = y;

	//디코더들 해제
	pWicImageDecoder->Release();
	pWicFrameDecoder->Release();
	//pWicBitmap->Release();

	//wic팩토리 해제
	pWicFactory->Release();

	return S_OK;
}


HRESULT d2dImage::frameInit(const WCHAR * fileName, int maxFrameX, int maxFrameY)
{
	// 재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 해줄것!
	if (_d2dInfo != NULL) this->release();

	//d2d 만들기
	this->createD2D(fileName);

	//이미지 정보 새로 생성 후 초기화하기
	_d2dInfo = new D2D_INFO;
	UINT sizeW;
	UINT sizeH;

	pWicBitmap->GetSize(&sizeW, &sizeH);
	_d2dInfo->width = sizeW;
	_d2dInfo->height = sizeH;
	_d2dInfo->RectF = { 0,0, (float)sizeW , (float)sizeH };

	UINT frameSizeW = sizeW / maxFrameX;
	UINT frameSizeH = sizeH / maxFrameY;
	_d2dInfo->frameWidth = frameSizeW;
	_d2dInfo->frameHeight = frameSizeH;
	_d2dInfo->maxFrameX = maxFrameX;
	_d2dInfo->maxFrameY = maxFrameY;
	_d2dInfo->FrameRectF = { 0,0,(float)frameSizeW,(float)frameSizeH };


	//디코더들 해제
	pWicImageDecoder->Release();
	pWicFrameDecoder->Release();
	//pWicBitmap->Release();

	//wic팩토리 해제
	pWicFactory->Release();

	return S_OK;
}

//해제
void d2dImage::release(void)
{
	if (_d2dInfo)
	{
		//팩토리 해제
		pD2DFactory->Release();
		//포맷 컨버터 해제(win비트맵 해제)
		pWicBitmap->Release();
		//비트맵 해제
		pWicBitmap->Release();

		//d2d 삭제
		SAFE_DELETE(_d2dInfo);
	}
}


//=================================================================================================
// ## [ 일반 렌더 ] ##
//=================================================================================================


// 기본형 알파 렌더
void d2dImage::render(HDC hdc, float alpha)
{

	//DC용 렌더 타겟 선언
	ID2D1DCRenderTarget* pDCRT = NULL;
	pD2DBitmap = NULL;
	//렌더타겟 설정
	pD2DFactory->CreateDCRenderTarget(&propertiesDC, &pDCRT);
	//wic비트맵을 d2d비트맵으로 변환
	pDCRT->CreateBitmapFromWicBitmap(pWicBitmap, NULL, &pD2DBitmap);

	//윈도우 크기 가져오기
	RECT winRC;
	GetClientRect(_hWnd, &winRC);
	//DC선언
	pDCRT->BindDC(hdc, &winRC);

	//그리기 시작
	pDCRT->BeginDraw();


	pDCRT->DrawBitmap(pD2DBitmap, _d2dInfo->RectF, alpha);
	pDCRT->EndDraw();

	//뻥날 확률 있음~
	pDCRT->Release();
}


//기본형 알파 렌더 - 위치
void d2dImage::render(HDC hdc, float destX, float destY, float alpha)
{

	//DC용 렌더 타겟 선언
	ID2D1DCRenderTarget* pDCRT = NULL;
	pD2DBitmap = NULL;
	//렌더타겟 설정
	pD2DFactory->CreateDCRenderTarget(&propertiesDC, &pDCRT);
	//wic비트맵을 d2d비트맵으로 변환
	pDCRT->CreateBitmapFromWicBitmap(pWicBitmap, NULL, &pD2DBitmap);

	//위치좌표 선언
	D2D1_RECT_F rcF = D2D1::RectF(destX, destY, destX + pD2DBitmap->GetSize().width, destY + pD2DBitmap->GetSize().height);

	//윈도우 크기 가져오기
	RECT winRC;
	GetClientRect(_hWnd, &winRC);
	//DC선언
	pDCRT->BindDC(hdc, &winRC);

	//그리기 시작
	pDCRT->BeginDraw();

	pDCRT->DrawBitmap(pD2DBitmap, rcF, alpha);
	pDCRT->EndDraw();

	//뻥날 확률 있음~
	pDCRT->Release();
}



//=================================================================================================
// ## [ 회전 렌더 ] ##
//=================================================================================================

//기본형 회전렌더
void d2dImage::rotationRender(HDC hdc, float destX, float destY, float angle, ROTATION_CP RCP, float alpha)
{

	//DC용 렌더 타겟 선언
	ID2D1DCRenderTarget* pDCRT = NULL;
	pD2DBitmap = NULL;
	//렌더타겟 설정
	pD2DFactory->CreateDCRenderTarget(&propertiesDC, &pDCRT);
	//wic비트맵을 d2d비트맵으로 변환
	pDCRT->CreateBitmapFromWicBitmap(pWicBitmap, NULL, &pD2DBitmap);

	//위치좌표 선언
	D2D1_RECT_F rcF = D2D1::RectF(destX, destY, destX + pD2DBitmap->GetSize().width, destY + pD2DBitmap->GetSize().height);

	//회전좌표 선언
	D2D1_POINT_2F rotationCP;
	if (RCP == RCP_CENTER)	rotationCP = Point2F(destX + pD2DBitmap->GetSize().width / 2, destY + pD2DBitmap->GetSize().height / 2);
	if (RCP == RCP_LEFT)	rotationCP = Point2F(destX, destY + pD2DBitmap->GetSize().height / 2);
	if (RCP == RCP_RIGHT)	rotationCP = Point2F(destX + pD2DBitmap->GetSize().width, destY + pD2DBitmap->GetSize().height / 2);
	if (RCP == RCP_TOP)		rotationCP = Point2F(destX + pD2DBitmap->GetSize().width / 2, destY);
	if (RCP == RCP_BOTTOM)	rotationCP = Point2F(destX + pD2DBitmap->GetSize().width / 2, destY + pD2DBitmap->GetSize().height);
	if (RCP == RCP_LT)		rotationCP = Point2F(destX, destY);
	if (RCP == RCP_RT)		rotationCP = Point2F(destX + pD2DBitmap->GetSize().width, destY);
	if (RCP == RCP_LB)		rotationCP = Point2F(destX, destY + pD2DBitmap->GetSize().height);
	if (RCP == RCP_RB)		rotationCP = Point2F(destX + pD2DBitmap->GetSize().width, destY + pD2DBitmap->GetSize().height);
	if (RCP == RCP_NONE)	rotationCP = Point2F(0, 0);

	//윈도우 크기 가져오기
	RECT winRC;
	GetClientRect(_hWnd, &winRC);
	//DC선언
	pDCRT->BindDC(hdc, &winRC);

	//그리기 시작
	pDCRT->BeginDraw();
	pDCRT->SetTransform(Matrix3x2F::Rotation(angle, rotationCP));
	pDCRT->DrawBitmap(pD2DBitmap, rcF, alpha);
	pDCRT->EndDraw();

	//해제
	pDCRT->Release();
}

void d2dImage::rotationRender(HDC hdc, float destX, float destY, float rotationX, float rotationY, float angle, ROTATION_CP RCP, float alpha)
{

	//DC용 렌더 타겟 선언
	ID2D1DCRenderTarget* pDCRT = NULL;
	pD2DBitmap = NULL;
	//렌더타겟 설정
	pD2DFactory->CreateDCRenderTarget(&propertiesDC, &pDCRT);
	//wic비트맵을 d2d비트맵으로 변환
	pDCRT->CreateBitmapFromWicBitmap(pWicBitmap, NULL, &pD2DBitmap);

	//위치좌표 선언
	D2D1_RECT_F rcF = D2D1::RectF(destX, destY, destX + pD2DBitmap->GetSize().width, destY + pD2DBitmap->GetSize().height);

	//회전좌표 선언
	D2D1_POINT_2F rotationCP;
	if (RCP == RCP_CENTER)	rotationCP = Point2F(rotationX + destX + pD2DBitmap->GetSize().width / 2, rotationY + destY + pD2DBitmap->GetSize().height / 2);
	if (RCP == RCP_LEFT)	rotationCP = Point2F(rotationX + destX, rotationY + destY + pD2DBitmap->GetSize().height / 2);
	if (RCP == RCP_RIGHT)	rotationCP = Point2F(rotationX + destX + pD2DBitmap->GetSize().width, rotationY + destY + pD2DBitmap->GetSize().height / 2);
	if (RCP == RCP_TOP)		rotationCP = Point2F(rotationX + destX + pD2DBitmap->GetSize().width / 2, rotationY + destY);
	if (RCP == RCP_BOTTOM)	rotationCP = Point2F(rotationX + destX + pD2DBitmap->GetSize().width / 2, rotationY + destY + pD2DBitmap->GetSize().height);
	if (RCP == RCP_LT)		rotationCP = Point2F(rotationX + destX, rotationY + destY);
	if (RCP == RCP_RT)		rotationCP = Point2F(rotationX + destX + pD2DBitmap->GetSize().width, rotationY + destY);
	if (RCP == RCP_LB)		rotationCP = Point2F(rotationX + destX, rotationY + destY + pD2DBitmap->GetSize().height);
	if (RCP == RCP_RB)		rotationCP = Point2F(rotationX + destX + pD2DBitmap->GetSize().width, rotationY + destY + pD2DBitmap->GetSize().height);
	if (RCP == RCP_NONE)	rotationCP = Point2F(rotationX, rotationY);

	//윈도우 크기 가져오기
	RECT winRC;
	GetClientRect(_hWnd, &winRC);
	//DC선언
	pDCRT->BindDC(hdc, &winRC);

	//그리기 시작
	pDCRT->BeginDraw();
	pDCRT->SetTransform(Matrix3x2F::Rotation(angle, rotationCP));
	pDCRT->DrawBitmap(pD2DBitmap, rcF, alpha);
	pDCRT->EndDraw();

	//뻥날 확률 있음~
	pDCRT->Release();
}


//=================================================================================================
// ## [ 프레임 렌더 ] ##
//=================================================================================================

void d2dImage::frameRender(HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float alpha)
{
	//DC용 렌더 타겟 선언
	ID2D1DCRenderTarget* pDCRT = NULL;
	pD2DBitmap = NULL;
	//렌더타겟 설정
	pD2DFactory->CreateDCRenderTarget(&propertiesDC, &pDCRT);
	//wic비트맵을 d2d비트맵으로 변환
	pDCRT->CreateBitmapFromWicBitmap(pWicBitmap, NULL, &pD2DBitmap);

	//프레임 예외처리
	if (currentFrameX >= _d2dInfo->maxFrameX) currentFrameX = _d2dInfo->maxFrameX - 1;
	if (currentFrameY >= _d2dInfo->maxFrameY) currentFrameY = _d2dInfo->maxFrameY - 1;

	//위치좌표 선언
	D2D1_RECT_F rcF = D2D1::RectF(destX, destY, destX + _d2dInfo->frameWidth, destY + _d2dInfo->frameHeight);

	D2D1_RECT_F frameRcF = D2D1::RectF(_d2dInfo->frameWidth *currentFrameX, _d2dInfo->frameHeight *currentFrameY,
		_d2dInfo->frameWidth *currentFrameX + _d2dInfo->frameWidth, _d2dInfo->frameHeight *currentFrameY + _d2dInfo->frameHeight);


	//윈도우 크기 가져오기
	RECT winRC;
	GetClientRect(_hWnd, &winRC);
	//DC선언
	pDCRT->BindDC(hdc, &winRC);

	//그리기 시작
	pDCRT->BeginDraw();
	pDCRT->DrawBitmap(pD2DBitmap, rcF, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, frameRcF);
	pDCRT->EndDraw();

	//해제
	pDCRT->Release();
}

void d2dImage::rFrameRender(HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float angle, ROTATION_CP RCP, float alpha)
{
	//DC용 렌더 타겟 선언
	ID2D1DCRenderTarget* pDCRT = NULL;
	pD2DBitmap = NULL;
	//렌더타겟 설정
	pD2DFactory->CreateDCRenderTarget(&propertiesDC, &pDCRT);
	//wic비트맵을 d2d비트맵으로 변환
	pDCRT->CreateBitmapFromWicBitmap(pWicBitmap, NULL, &pD2DBitmap);

	//프레임 예외처리
	if (currentFrameX >= _d2dInfo->maxFrameX) currentFrameX = _d2dInfo->maxFrameX - 1;
	if (currentFrameY >= _d2dInfo->maxFrameY) currentFrameY = _d2dInfo->maxFrameY - 1;

	//위치좌표 선언
	D2D1_RECT_F rcF = D2D1::RectF(destX, destY, destX + _d2dInfo->frameWidth, destY + _d2dInfo->frameHeight);

	D2D1_RECT_F frameRcF = D2D1::RectF(_d2dInfo->frameWidth *currentFrameX, _d2dInfo->frameHeight *currentFrameY,
		_d2dInfo->frameWidth *currentFrameX + _d2dInfo->frameWidth, _d2dInfo->frameHeight *currentFrameY + _d2dInfo->frameHeight);


	//회전좌표 선언
	D2D1_POINT_2F rotationCP;
	if (RCP == RCP_CENTER)	rotationCP = Point2F(destX + _d2dInfo->frameWidth / 2, destY + _d2dInfo->frameHeight / 2);
	if (RCP == RCP_LEFT)	rotationCP = Point2F(destX, destY + _d2dInfo->frameHeight / 2);
	if (RCP == RCP_RIGHT)	rotationCP = Point2F(destX + _d2dInfo->frameWidth, destY + _d2dInfo->frameHeight / 2);
	if (RCP == RCP_TOP)		rotationCP = Point2F(destX + _d2dInfo->frameWidth / 2, destY);
	if (RCP == RCP_BOTTOM)	rotationCP = Point2F(destX + _d2dInfo->frameWidth / 2, destY + _d2dInfo->frameHeight);
	if (RCP == RCP_LT)		rotationCP = Point2F(destX, destY);
	if (RCP == RCP_RT)		rotationCP = Point2F(destX + _d2dInfo->frameWidth, destY);
	if (RCP == RCP_LB)		rotationCP = Point2F(destX, destY + pD2DBitmap->GetSize().height);
	if (RCP == RCP_RB)		rotationCP = Point2F(destX + _d2dInfo->frameWidth, destY + _d2dInfo->frameHeight);
	if (RCP == RCP_NONE)	rotationCP = Point2F(0, 0);

	//윈도우 크기 가져오기
	RECT winRC;
	GetClientRect(_hWnd, &winRC);
	//DC선언
	pDCRT->BindDC(hdc, &winRC);

	//그리기 시작
	pDCRT->BeginDraw();
	pDCRT->SetTransform(Matrix3x2F::Rotation(angle, rotationCP));
	pDCRT->DrawBitmap(pD2DBitmap, rcF, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, frameRcF);
	pDCRT->EndDraw();

	//해제
	pDCRT->Release();
}

void d2dImage::rFrameRender(HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float rotationX, float rotationY, float angle, ROTATION_CP RCP, float alpha)
{
	//DC용 렌더 타겟 선언
	ID2D1DCRenderTarget* pDCRT = NULL;
	pD2DBitmap = NULL;
	//렌더타겟 설정
	pD2DFactory->CreateDCRenderTarget(&propertiesDC, &pDCRT);
	//wic비트맵을 d2d비트맵으로 변환
	pDCRT->CreateBitmapFromWicBitmap(pWicBitmap, NULL, &pD2DBitmap);

	//프레임 예외처리
	if (currentFrameX >= _d2dInfo->maxFrameX) currentFrameX = _d2dInfo->maxFrameX - 1;
	if (currentFrameY >= _d2dInfo->maxFrameY) currentFrameY = _d2dInfo->maxFrameY - 1;

	//위치좌표 선언
	D2D1_RECT_F rcF = D2D1::RectF(destX, destY, destX + _d2dInfo->frameWidth, destY + _d2dInfo->frameHeight);

	D2D1_RECT_F frameRcF = D2D1::RectF(_d2dInfo->frameWidth *currentFrameX, _d2dInfo->frameHeight *currentFrameY,
		_d2dInfo->frameWidth *currentFrameX + _d2dInfo->frameWidth, _d2dInfo->frameHeight *currentFrameY + _d2dInfo->frameHeight);


	//회전좌표 선언
	D2D1_POINT_2F rotationCP;
	if (RCP == RCP_CENTER)	rotationCP = Point2F(rotationX + destX + _d2dInfo->frameWidth / 2, rotationY + destY + _d2dInfo->frameHeight / 2);
	if (RCP == RCP_LEFT)	rotationCP = Point2F(rotationX + destX, rotationY + destY + _d2dInfo->frameHeight / 2);
	if (RCP == RCP_RIGHT)	rotationCP = Point2F(rotationX + destX + _d2dInfo->frameWidth, rotationY + destY + _d2dInfo->frameHeight / 2);
	if (RCP == RCP_TOP)		rotationCP = Point2F(rotationX + destX + _d2dInfo->frameWidth / 2, rotationY + destY);
	if (RCP == RCP_BOTTOM)	rotationCP = Point2F(rotationX + destX + _d2dInfo->frameWidth / 2, rotationY + destY + _d2dInfo->frameHeight);
	if (RCP == RCP_LT)		rotationCP = Point2F(rotationX + destX, rotationY + destY);
	if (RCP == RCP_RT)		rotationCP = Point2F(rotationX + destX + _d2dInfo->frameWidth, rotationY + destY);
	if (RCP == RCP_LB)		rotationCP = Point2F(rotationX + destX, rotationY + destY + _d2dInfo->frameHeight);
	if (RCP == RCP_RB)		rotationCP = Point2F(rotationX + destX + _d2dInfo->frameWidth, rotationY + destY + _d2dInfo->frameHeight);
	if (RCP == RCP_NONE)	rotationCP = Point2F(rotationX, rotationY);

	//윈도우 크기 가져오기
	RECT winRC;
	GetClientRect(_hWnd, &winRC);
	//DC선언
	pDCRT->BindDC(hdc, &winRC);

	//그리기 시작
	pDCRT->BeginDraw();
	pDCRT->SetTransform(Matrix3x2F::Rotation(angle, rotationCP));
	pDCRT->DrawBitmap(pD2DBitmap, rcF, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, frameRcF);
	pDCRT->EndDraw();

	//해제
	pDCRT->Release();
}


//=================================================================================================
// ## [ 특수 렌더 ] ##
//=================================================================================================

//
void d2dImage::xFrameRender(HDC hdc, float destX, float destY, float lengthY, int currentFrameX, float angle, TELESCOPIC_DIRECTION TD, ROTATION_CP RCP, float rotationX, float rotationY, float alpha)
{
	//DC용 렌더 타겟 선언
	ID2D1DCRenderTarget* pDCRT = NULL;
	pD2DBitmap = NULL;
	//렌더타겟 설정
	pD2DFactory->CreateDCRenderTarget(&propertiesDC, &pDCRT);
	//wic비트맵을 d2d비트맵으로 변환
	pDCRT->CreateBitmapFromWicBitmap(pWicBitmap, NULL, &pD2DBitmap);

	//프레임 예외처리
	if (currentFrameX >= _d2dInfo->maxFrameX) currentFrameX = _d2dInfo->maxFrameX - 1;
	if (lengthY >= _d2dInfo->height) lengthY = _d2dInfo->height;


	//위치좌표 선언
	D2D1_RECT_F rcF;
	if (TD == TD_CENTER) rcF = D2D1::RectF(destX - _d2dInfo->frameWidth / 2, destY - lengthY / 2, destX - _d2dInfo->frameWidth / 2 + _d2dInfo->frameWidth, destY + lengthY / 2);
	if (TD == TD_UP) rcF = D2D1::RectF(destX - _d2dInfo->frameWidth / 2, destY - lengthY, destX - _d2dInfo->frameWidth / 2 + _d2dInfo->frameWidth, destY);
	if (TD == TD_DOWN) rcF = D2D1::RectF(destX - _d2dInfo->frameWidth / 2, destY, destX - _d2dInfo->frameWidth / 2 + _d2dInfo->frameWidth, destY + lengthY);

	D2D1_RECT_F frameRcF = D2D1::RectF(_d2dInfo->frameWidth *currentFrameX, 0,
		_d2dInfo->frameWidth *currentFrameX + _d2dInfo->frameWidth, lengthY);

	//회전좌표 선언
	D2D1_POINT_2F rotationCP;
	if (RCP != RCP_CENTER || RCP != RCP_LEFT || RCP != RCP_RIGHT) RCP = RCP_CENTER;
	if (RCP == RCP_CENTER)	rotationCP = Point2F(rotationX + destX, rotationY + destY);
	if (RCP == RCP_LEFT)	rotationCP = Point2F(rotationX + destX - _d2dInfo->frameWidth / 2, rotationY + destY);
	if (RCP == RCP_RIGHT)	rotationCP = Point2F(rotationX + destX + _d2dInfo->frameWidth / 2, rotationY + destY);


	//윈도우 크기 가져오기
	RECT winRC;
	GetClientRect(_hWnd, &winRC);
	//DC선언
	pDCRT->BindDC(hdc, &winRC);

	//그리기 시작
	pDCRT->BeginDraw();
	pDCRT->SetTransform(Matrix3x2F::Rotation(angle, rotationCP));
	pDCRT->DrawBitmap(pD2DBitmap, rcF, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, frameRcF);
	pDCRT->EndDraw();

	//해제
	pDCRT->Release();
}






//d2d 만들기
void d2dImage::createD2D(const WCHAR* fileName)
{


	//팩토리 생성 초기화
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
	// D2D1_FACTORY_TYPE_SINGLE_THREADED (0) : 싱글 스레드 기반의 Factory 객체 생성
	// D2D1_FACTORY_TYPE_MULTI_THREADED (1) : 멀티 스레드 기반의 Factory 객체 생성

	//윈도우창 클라이언트 영역 크기 가져오기
	RECT winRC;
	GetClientRect(_hWnd, &winRC);

	//윈도우창 클라이언트 영역 크기 계산하기
	D2D1_SIZE_U winSize = SizeU(winRC.right - winRC.left, winRC.bottom - winRC.top);


	//렌더 타겟 영역 생성 ->일반용
	//pD2DFactory->CreateHwndRenderTarget(RenderTargetProperties(), HwndRenderTargetProperties(_hWnd, winSize), &pRenderTarget);

	//DC에 그리기용 설정
	propertiesDC = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
		0,
		0,
		D2D1_RENDER_TARGET_USAGE_NONE,
		D2D1_FEATURE_LEVEL_DEFAULT);


	//DC용 렌더 타겟
	//pD2DFactory->CreateDCRenderTarget(&propertiesDC, &pDCRT);

	//WIC팩토리 선언
	pWicFactory = NULL;

	//COM라이브러리 초기화 - 핵심 중 하나
	CoInitialize(NULL);

	//팩토리 인터페이스 개체 생성
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pWicFactory));

	//이미지 해석할 디코더 생성 [ 비트맵 디코더 ] -> 파일 읽기위해 생성
	pWicImageDecoder = NULL;

	//이미지 읽기
	pWicFactory->CreateDecoderFromFilename(fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pWicImageDecoder);
	//CreateDecoderFromFilename(파일 경로, 디코더 벤더??(모름), 읽기 or 쓰기 or 읽고 쓰기 정함(현재 읽기용), 디코더 캐시 옵션??(모름), 디코더(아마도 로드한 이미지를 디코더에 담는 듯))

	//프레임단위로 해석할 디코더 생성 [ 프레임 디코더 ] -> ex) gif와 같이 여러장의 이미지가 들어간 것
	pWicFrameDecoder = NULL;

	//디코더에서 프레임 얻기 -> 아마도 프레임 디코더의 이미지가 gif라면 프레임 디코더에 넣는 듯....
	pWicImageDecoder->GetFrame(0, &pWicFrameDecoder);
	//getFrame(프레임 시작지점?,프레임의 이미지 넣기!)

	//포맷 컨버터 선언-> 로드한 이미지를 비트맵으로 변환하기 위한 것
	//IWICFormatConverter* pWicBitmap = NULL;

	//포맷 컨버터 개체 생성 ->아마도 wic용 비트맵을 생성하는 듯...
	pWicFactory->CreateFormatConverter(&pWicBitmap);

	//로드한 이미지의 첫 번째 프레임에 접근할 수 있는 프레임 디코더를 넘겨서 
	//로드한 이미지를  WIC용 비트맵으로 변화(포맷 컨버터 초기화)
	pWicBitmap->Initialize(pWicFrameDecoder, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);

	//변환된 이미지 형식을 사용하여 Direct2D용 비트맵으로 변환(렌더 타겟에서 변환)
	//변환을 위해서 렌더 타겟에서 Wic비트맵에서 가져와 d2d용 비트맵을 생성하는 전용 함수 사용
	//pBitmapRT->CreateBitmapFromWicBitmap(pWicFormatConverter, NULL, &pD2DBitmap);
}