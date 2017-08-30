#pragma once

//=================================================================================================
//	##	이미지 [ Image ] (헤더)	##
//=================================================================================================

//로테이션 좌표용
enum ROTATION_CP
{
	RCP_CENTER,
	RCP_LEFT,
	RCP_RIGHT,
	RCP_TOP,
	RCP_BOTTOM,
	RCP_LT,
	RCP_RT,
	RCP_LB,
	RCP_RB,
	RCP_NONE

};

//프레임용
enum TELESCOPIC_DIRECTION
{
	TD_CENTER,
	TD_UP,
	TD_DOWN,

};


//로테이션 좌표용
#define RCP_CENTER		RCP_CENTER
#define RCP_LEFT		RCP_LEFT
#define RCP_RIGHT		RCP_RIGHT
#define RCP_TOP			RCP_TOP
#define RCP_BOTTOM		RCP_BOTTOM
#define RCP_LT			RCP_LT
#define RCP_RT			RCP_RT
#define RCP_LB			RCP_LB
#define RCP_RB			RCP_RB
#define RCP_NONE		RCP_NONE

#define TD_CENTER		TD_CENTER
#define TD_UP			TD_UP
#define TD_DOWN			TD_DOWN

class d2dImage
{
public:
	typedef struct tagD2D
	{
		HDC			hMemDC;			//메모리 DC
		HBITMAP		hBit;			//비트맵
		HBITMAP		hOBit;			//올드비트맵
		float		x;				//이미지 x좌표(레프트)
		float		y;				//이미지 y좌표(탑)
		int			width;			//이미지 가로크기
		int			height;			//이미지 세로크기
		int			currentFrameX;	//현재프레임 x좌표
		int			currentFrameY;	//현재프레임 y좌표
		int			maxFrameX;		//최대프레임 x갯수
		int			maxFrameY;		//최대프레임 y갯수
		int			frameWidth;		//1프레임 가로크기
		int			frameHeight;	//1프레임 세로크기

		D2D1_RECT_F RectF;			//렉트, 기본
		D2D1_RECT_F FrameRectF;		//프레임용 렉트

		ID2D1DCRenderTarget* pDCRT;			//렌더타겟
		ID2D1Bitmap* pD2DBitmap = NULL;		//비트맵

		//초기화
		tagD2D()
		{
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;

			ID2D1DCRenderTarget* pDCRT = NULL;
			ID2D1Bitmap* pD2DBitmap = NULL;
		}

	}D2D_INFO, *LPD2D_INFO;

private:
	LPD2D_INFO		_d2dInfo;		//GDI정보
	//CHAR*			_fileName;		//이미지 이름

	//DC에 그리기용 설정
	D2D1_RENDER_TARGET_PROPERTIES propertiesDC;

	//D2D 팩토리 선언
	ID2D1Factory* pD2DFactory;

	//렌더 타겟 선언 ->렌더 타겟은 GPU에 메모리 할당하는 것[ d2d전용(GDI와 같이 못씀) ]
	//ID2D1HwndRenderTarget* pRenderTarget = NULL;	//선언만 하고 안쓸거임!!

	//DC용 렌더 타겟 선언 ->GDI용 DC를 같이 사용하기 위함(핵심)
	//ID2D1DCRenderTarget* pDCRT = NULL;

	//비트맵 렌더 타겟 선언->비트맵 저장용
	//ID2D1BitmapRenderTarget* pBitmapRT;

	//d2d용 비트맵 선언
	ID2D1Bitmap* pD2DBitmap;

	//포맷 컨버터 선언-> 로드한 이미지를 비트맵으로 변환하기 위한 것
	IWICFormatConverter* pWicBitmap;


private:
	//wic팩토리 선언
	IWICImagingFactory* pWicFactory;
	//프레임 데코더 선언
	IWICBitmapFrameDecode *pWicFrameDecoder;
	//이미지 디코더 선언
	IWICBitmapDecoder* pWicImageDecoder;



public:

	//=================================================================================================
	//	##	[ 초기화 ]	##
	//=================================================================================================


	//일반 초기화
	HRESULT init(const WCHAR* fileName);
	//일반 초기화 - 위치좌표
	HRESULT init(const WCHAR * fileName, float x, float y);

	//프레임 초기화
	HRESULT frameInit(const WCHAR * fileName, int maxFrameX, int maxFrameY);

	//해제
	void release(void);




	//=================================================================================================
	//	## [ 일반 렌더 ] ##
	//=================================================================================================

	//렌더
	void render(HDC hdc, float alpha = 1.0);
	void render(HDC hdc, float destX, float destY, float alpha = 1.0);



	//=================================================================================================
	// ## [ 회전 렌더 ] ##
	//=================================================================================================

	//기본형
	void rotationRender(HDC hdc, float destX, float destY, float angle, ROTATION_CP RCP = RCP_CENTER, float alpha = 1.0);
	//좌표축 설정형
	void rotationRender(HDC hdc, float destX, float destY, float rotationX, float rotationY, float angle, ROTATION_CP RCP = RCP_CENTER, float alpha = 1.0);

	//=================================================================================================
	// ## [ 스케일 렌더 ] ##
	//=================================================================================================

	//=================================================================================================
	// ## [ 프레임 렌더 ] ##
	//=================================================================================================

	void frameRender(HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float alpha = 1.0);
	void rFrameRender(HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float angle, ROTATION_CP RCP = RCP_CENTER, float alpha = 1.0);
	void rFrameRender(HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float rotationX, float rotationY, float angle, ROTATION_CP RCP = RCP_CENTER, float alpha = 1.0);



	//void frameRender(HDC hdc, int destX, int destY, );


	//=================================================================================================
	// ## [ 특수 렌더 ] ##
	//=================================================================================================
	void xFrameRender(HDC hdc, float destX, float destY, float lengthY, int currentFrameX, float angle, TELESCOPIC_DIRECTION TD = TD_CENTER, ROTATION_CP RCP = RCP_CENTER, float rotationX = 0, float rotationY = 0, float alpha = 1.0);
	//void sFrameRender(HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float rotationX, float rotationY, float angle, ROTATION_CP RCP = RCP_CENTER, float alpha = 1.0);



	//d2d 만들기
	void createD2D(const WCHAR * fileName);
	// 



	d2dImage();
	~d2dImage();
};

