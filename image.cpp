#include "stdafx.h"
#include "image.h"
#pragma comment(lib, "msimg32.lib") //알파블렌드를 사용하기 위해서 라이브러리 추가

//=================================================================================================
//	##	이미지 [ Image ] (클래스)	##
//=================================================================================================

//생성자 초기화
image::image() : _imageInfo(NULL), _fileName(NULL), _isTrans(FALSE), _transColor(RGB(0, 0, 0))
{
}
image::~image()
{
}

//빈 비트맵으로 초기화
HRESULT image::init(int width, int height)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 해줄것!
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 새로 생성 후 초기화하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//출력속도개선을 위한 메모리 공간 할당
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	_fileName = NULL;

	//투명키 컬러 셋팅
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	//리소스 얻어 오는데 실패시 경고
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//이미지 리소스로 초기화(사용안함)
HRESULT image::init(const DWORD resID, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 해줄것!
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 새로 생성 후 초기화하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//출력속도개선을 위한 메모리 공간 할당
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID));
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	_fileName = NULL;

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻어 오는데 실패시 경고
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//=================================================================================================
//	## [ 이미지로 파일 초기화 ] (주로 사용)  ##
//=================================================================================================

// !! [ 이미지 파일로 초기화(주 사용) ] !! =================================================================================================
HRESULT image::init(const CHAR * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 해줄것!
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 새로 생성 후 초기화하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//출력속도개선을 위한 메모리 공간 할당
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻어 오는데 실패시 경고
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

// !! [ 이미지 파일로 초기화(주로 사용) ] - 시작지점까지 초기화 가능 !! =================================================================================================
HRESULT image::init(const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 해줄것!
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 새로 생성 후 초기화하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//출력속도개선을 위한 메모리 공간 할당
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻어 오는데 실패시 경고
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

// !! [ 프레임 이미지 초기화(주로 사용) ] !! ================================================================================================= 
HRESULT image::init(const char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 해줄것!
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 새로 생성 후 초기화하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//출력속도개선을 위한 메모리 공간 할당
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	//파일이름
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻어 오는데 실패시 경고
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

// !! [ 프레임 이미지 초기화(주로 사용) ] - 시작지점까지 초기화 가능 !! =================================================================================================
HRESULT image::init(const char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 해줄것!
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 새로 생성 후 초기화하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//출력속도개선을 위한 메모리 공간 할당
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	//파일이름
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻어 오는데 실패시 경고
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}


// !! [ 알파 브렌딩 초기화 ] !! =================================================================================================
HRESULT image::initForAlphaBlend(void)
{
	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//알파블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;	//원본 혼합방식(알파채널 미포함?)

	//이미지 정보 새로 생성후 초기화하기
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}


//스케일 이미지 초기화 (!!특수!!)
HRESULT image::scaleInit(int width, int height, BOOL isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 해줄것!
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 새로 생성 후 초기화하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//출력속도개선을 위한 메모리 공간 할당
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	_fileName = NULL;

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻어 오는데 실패시 경고
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}




//투명색 셋팅(배경색을 날릴꺼냐?, 어떤 색을 날릴꺼냐?)
void image::setTransColor(BOOL isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}

//이미지 정보 해제
void image::release(void)
{
	//이미지 정보가 있으면 해제 시켜라
	if (_imageInfo)
	{
		//이미지 삭제
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//포인트 삭제
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		//투명컬러키 초기화
		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}
}


//=================================================================================================
// ## [ 일반 렌더 ] ##
//=================================================================================================

//랜더 (0, 0지점에 출력)
void image::render(HDC hdc)
{
	//배경을 투명 유무에 따라 작동

	if (_isTrans)	//투명 작동
	{
		//GdiTransparentBlt : 비트맵을 불러올때 특정색상을 제외하고 복사해주는 함수
		GdiTransparentBlt
		(
			hdc,					//복사할 장소의 DC (화면에 보여지는 화면DC)
			_imageInfo->x,			//복사될 좌표 시작x
			_imageInfo->y,			//복사될 좌표 시작y
			_imageInfo->width,		//복사될 이미지 가로크기
			_imageInfo->height,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 메모리DC
			0, 0,					//복사 시작지점
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로크기
			_transColor				//복사할때 제외할 색상(마젠타 색상 지우기)
		);
	}
	else//투명 미작동
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사 해주는 함수
		BitBlt(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}


//렌더 (내가 지정한 좌표에 이미지 출력한다)
void image::render(HDC hdc, int destX, int destY)
{
	//배경을 투명 유무에 따라 작동

	if (_isTrans)	//투명 작동
	{
		//GdiTransparentBlt : 비트맵을 불러올때 특정색상을 제외하고 복사해주는 함수
		GdiTransparentBlt
		(
			hdc,					//복사할 장소의 DC (화면에 보여지는 화면DC)
			destX, destY,			//복사될 좌표 시작x, y
			_imageInfo->width,		//복사될 이미지 가로크기
			_imageInfo->height,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 메모리DC
			0, 0,					//복사 시작지점
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로크기
			_transColor				//복사할때 제외할 색상(마젠타 색상 지우기)
		);
	}
	else//투명 미작동
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사 해주는 함수
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

//렌더 (복사 붙여넣기)
void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//배경을 투명 유무에 따라 작동

	if (_isTrans)	//투명 작동
	{
		//GdiTransparentBlt : 비트맵을 불러올때 특정색상을 제외하고 복사해주는 함수
		GdiTransparentBlt
		(
			hdc,					//복사할 장소의 DC (화면에 보여지는 화면DC)
			destX, destY,			//복사될 좌표 시작x, y
			sourWidth,				//복사될 이미지 가로크기
			sourHeight,				//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 메모리DC
			sourX, sourY,			//복사 시작지점
			sourWidth,				//복사 영역 가로크기
			sourHeight,				//복사 영역 세로크기
			_transColor				//복사할때 제외할 색상(마젠타 색상 지우기)
		);
	}
	else//투명 미작동
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사 해주는 함수
		BitBlt(hdc, destX, destY, sourWidth, sourHeight, _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}


//=================================================================================================
// ## [ 알파렌더 ] ## 
//=================================================================================================

//알파 렌더 (0, 0지점에 출력)
void image::alphaRender(HDC hdc, BYTE alpha)
{
	//알파블렌드 처음사용하냐?
	//알파블렌드 사용할 수 있도록 초기화 해라
	if (!_blendImage) initForAlphaBlend();

	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)	//투명 작동
	{
		//1. 출력해야 될 DC에 그려져 있는 내용을 블렌드이미지에 그린다
		BitBlt
		(
			_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc, _imageInfo->x, _imageInfo->y,
			SRCCOPY
		);
		//2. 원본이미지의 배경을 없앤후 블렌드이미지에 그린다
		GdiTransparentBlt
		(
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_transColor
		);
		//3. 블렌드이미지를 화면에 그린다
		AlphaBlend
		(
			hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendFunc
		);
	}
	else//투명 미작동
	{
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

//알파 렌더 (원하는 좌표에 출력)
void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	//알파블렌드 처음사용하냐?
	//알파블렌드 사용할 수 있도록 초기화 해라
	if (!_blendImage) initForAlphaBlend();

	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)	//투명 작동
	{
		//1. 출력해야 될 DC에 그려져 있는 내용을 블렌드이미지에 그린다
		BitBlt
		(
			_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc, destX, destY,
			SRCCOPY
		);
		//2. 원본이미지의 배경을 없앤후 블렌드이미지에 그린다
		GdiTransparentBlt
		(
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_transColor
		);
		//3. 블렌드이미지를 화면에 그린다
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else//투명 미작동
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

//알파 렌더 (잘라 붙여넣기)
void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//알파블렌드 처음사용하냐?
	//알파블렌드 사용할 수 있도록 초기화 해라
	if (!_blendImage) initForAlphaBlend();

	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)	//투명 작동
	{
		//1. 출력해야 될 DC에 그려져 있는 내용을 블렌드이미지에 그린다
		BitBlt
		(
			_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc, destX, destY,//0,0해도 되지 않나?
			SRCCOPY
		);
		//2. 원본이미지의 배경을 없앤후 블렌드이미지에 그린다
		GdiTransparentBlt
		(
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_transColor
		);
		//3. 블렌드이미지를 화면에 그린다
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, _blendImage->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
	}
	else//투명 미작동
	{
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, _imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
	}
}


//=================================================================================================
//	## [ 프레임 렌더 ] ##
//=================================================================================================

//프레임 랜더(프레임 미조절 - 계속 반복)
void image::frameRender(HDC hdc, int destX, int destY)
{
	//배경을 투명 유무에 따라 작동

	if (_isTrans)	//투명 작동
	{
		//GdiTransparentBlt : 비트맵을 불러올때 특정색상을 제외하고 복사해주는 함수
		GdiTransparentBlt
		(
			hdc,													//복사할 장소의 DC (화면에 보여지는 화면DC)
			destX, destY,											//복사될 좌표 시작x, y
			_imageInfo->frameWidth,									//복사될 이미지 가로크기
			_imageInfo->frameHeight,								//복사될 이미지 세로크기
			_imageInfo->hMemDC,										//복사될 대상 메모리DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//복사 시작지점 X
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//복사 시작지점 Y
			_imageInfo->frameWidth,									//복사 영역 가로크기
			_imageInfo->frameHeight,								//복사 영역 세로크기
			_transColor												//복사할때 제외할 색상(마젠타 색상 지우기)
		);
	}
	else//투명 미작동
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사 해주는 함수
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

//프레임 랜더(프레임 조절 - 원하는 프레임 선정)
void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//이미지 예외처리 - 입력 받은 프레임 개수가 최대 프레임 개수보다 클 때 작동됨
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	//배경을 투명 유무에 따라 작동

	if (_isTrans)	//투명 작동
	{
		//GdiTransparentBlt : 비트맵을 불러올때 특정색상을 제외하고 복사해주는 함수
		GdiTransparentBlt
		(
			hdc,													//복사할 장소의 DC (화면에 보여지는 화면DC)
			destX, destY,											//복사될 좌표 시작x, y
			_imageInfo->frameWidth,									//복사될 이미지 가로크기
			_imageInfo->frameHeight,								//복사될 이미지 세로크기
			_imageInfo->hMemDC,										//복사될 대상 메모리DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//복사 시작지점 X
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//복사 시작지점 Y			
			_imageInfo->frameWidth,									//복사 영역 가로크기
			_imageInfo->frameHeight,								//복사 영역 세로크기
			_transColor												//복사할때 제외할 색상(마젠타 색상 지우기)
		);
	}
	else//투명 미작동
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사 해주는 함수
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}


//====================================================================
//	## [ 루프렌더 ] ##
//====================================================================

void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//offset 값이 음수인 경우 보정하기
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//그려지는 영역 세팅
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려지는 DC 영역 (화면크기)
	RECT rcDest;

	//그려야 할 전체 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//소스 영역의 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 바텀값을 올려준다
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 루프영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//소스 영역의 높이 계산
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
			if (x + sourWidth > drawAreaW)
			{
				//넘어간 그림의 값만큼 바텀값을 올려준다
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//그려지는 영역
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//그려주자(일반렌더-이미지잘라서붙이기)
			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);
		}
	}
}

void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
}



//=================================================================================================
//	## [ 사이즈 렌더 ] ##
//=================================================================================================


void image::sizeRender(HDC hdc, int sizeW, int sizeH)
{
	SetStretchBltMode(hdc, COLORONCOLOR);	//이미지 깔끔이 나오게 함!
	StretchBlt(hdc, _imageInfo->x, _imageInfo->y, sizeW, sizeH, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
}

void image::sizeRender(HDC hdc, int destX, int destY, int sizeW, int sizeH)
{
	SetStretchBltMode(hdc, COLORONCOLOR);	//이미지 깔끔이 나오게 함!
	StretchBlt(hdc, destX, destY, sizeW, sizeH, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
	//_imageInfo->x = destX;
	//_imageInfo->y = destY;
}

//=================================================================================================
//	## [ 트렌스 렌더 ] ##
//=================================================================================================


void image::transRender(HDC hdc, bool isTrans = false, COLORREF color = RGB(0, 0, 0))
{
	//배경을 투명 유무에 따라 작동

	if (isTrans)	//투명 작동
	{
		//GdiTransparentBlt : 비트맵을 불러올때 특정색상을 제외하고 복사해주는 함수
		GdiTransparentBlt
		(
			hdc,					//복사할 장소의 DC (화면에 보여지는 화면DC)
			_imageInfo->x,			//복사될 좌표 시작x
			_imageInfo->y,			//복사될 좌표 시작y
			_imageInfo->width,		//복사될 이미지 가로크기
			_imageInfo->height,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 메모리DC
			0, 0,					//복사 시작지점
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로크기
			color					//복사할때 제외할 색상(마젠타 색상 지우기)
		);
	}
	else//투명 미작동
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사 해주는 함수
		BitBlt(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}


void image::transRender(HDC hdc, int destX, int destY, bool isTrans = false, COLORREF color = RGB(0,0,0))
{
	//배경을 투명 유무에 따라 작동

	if (isTrans)	//투명 작동
	{
		//GdiTransparentBlt : 비트맵을 불러올때 특정색상을 제외하고 복사해주는 함수
		GdiTransparentBlt
		(
			hdc,					//복사할 장소의 DC (화면에 보여지는 화면DC)
			destX, destY,			//복사될 좌표 시작x, y
			_imageInfo->width,		//복사될 이미지 가로크기
			_imageInfo->height,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 메모리DC
			0, 0,					//복사 시작지점
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로크기
			color					//복사할때 제외할 색상(마젠타 색상 지우기)
		);
	}
	else//투명 미작동
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사 해주는 함수
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

//=================================================================================================
//	## [ 특수 ] ##
//=================================================================================================



void image::setImageDC(HDC hdc, int sizeW, int sizeH)
{
	//배경 선언
	RECT BK_ColorRC = { 0,0, _imageInfo->width, _imageInfo->height };
	//배경을 이미지DC에 그려둠
	setRectangle(_imageInfo->hMemDC, BK_ColorRC, _transColor, true);

	SetStretchBltMode(_imageInfo->hMemDC, COLORONCOLOR);	//이미지 깔끔이 나오게 함!
	StretchBlt(_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc, 0, 0, sizeW, sizeH, SRCCOPY);
}



//===========================================================================================================
//											#프레임 알파 렌더
//===========================================================================================================
void image::frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	if(!_blendImage) initForAlphaBlend();

	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	//이미지 예외처리
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if(currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if(currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if(_isTrans)//배경색 없앨꺼냐?
	{
		BitBlt(//이미 그려져있는 것들을 먼저 그린다.
			   _blendImage->hMemDC,
			   0,
			   0,
			   _imageInfo->frameWidth,		//복사 영역 가로크기
			   _imageInfo->frameHeight,	//복사 영역 세로크기
			   hdc,						//미리 그려져 있던 DC
			   destX,						//그려져있던 DC의 부분시작점 + 위에 WIDTH만큼 _blendimage로 복사
			   destY,
			   SRCCOPY
		);
		//그 위에 그리기 위해 블랜드 이미지를
		//GdiTransparentBlt : 비트맵을 불러올때 특정색상을 제외하고 복사해주는 함수
		GdiTransparentBlt(
			_blendImage->hMemDC,
			0,
			0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,  //복사 시작지점
			_imageInfo->currentFrameY * _imageInfo->frameHeight, //복사 시작지점
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
		//3. 블렌드이미지를 화면에 그린다
		AlphaBlend(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendImage->hMemDC,
			0,
			0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendFunc);
	}
	else//원본 이미지 그대로 출력할꺼냐?
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사 해주는 함수
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			   _imageInfo->hMemDC,
			   _imageInfo->currentFrameX * _imageInfo->frameWidth,
			   _imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

