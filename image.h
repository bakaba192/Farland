#pragma once

//=================================================================================================
//	##	이미지 [ Image ] (헤드)	##
//=================================================================================================

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,			//리소스로 로딩 (사용안함)
		LOAD_FILE,					//파일로 로딩
		LOAD_EMPTY,					//빈비트맵 로딩
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		resID;			//리소스 ID
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
		BYTE		loadType;		//이미지 로드타입

		//초기화
		tagImage()
		{
			resID = 0;
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
			loadType = LOAD_RESOURCE;
		}

	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	//일반 랜더 관련
	LPIMAGE_INFO	_imageInfo;		//이미지 정보
	CHAR*			_fileName;		//이미지 이름
	BOOL			_isTrans;		//배경색 유무 묻기(투명과 관련)
	COLORREF		_transColor;	//배경색 없앨 RGB값 (마젠타 = RGB(255, 0, 255))

	//알파 블렌드 기능 관련
	BLENDFUNCTION	_blendFunc;		//알파 블렌드 기능
	LPIMAGE_INFO	_blendImage;	//알파 블렌드 이미지

	//특수 렌더 관련
	//LPIMAGE_INFO	_spaceImage;


public:
	image();
	~image();

//=================================================================================================
//	##	[ 초기화 ]	##
//=================================================================================================

	//빈 비트맵 초기화
	HRESULT init(int width, int height);
	//이미지 리소스로 초기화(사용 안함)
	HRESULT init(const DWORD resID, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//이미지 파일로 초기화(주로 사용)
	HRESULT init(const CHAR* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//이미지 파일로 초기화(주로 사용) - 시작지점까지 초기화 가능
	HRESULT init(const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//프레임 이미지 초기화(주로 사용)
	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//프레임 이미지 초기화(주로 사용) - 시작지점까지 초기화 가능
	HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));


	//알파블렌드 초기화
	HRESULT initForAlphaBlend(void);


	//스케일 렌더 초기화 (!!특수 렌더!!)
	HRESULT scaleInit(int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//투명색 셋팅(배경색을 날릴꺼냐?, 어떤 색을 날릴꺼냐?)
	void setTransColor(BOOL isTrans, COLORREF transColor);

	//해제
	void release(void);

//=================================================================================================
//	## [ 일반 렌더 ] ##
//=================================================================================================

	//렌더(좌표에 이미지 출력)
	void render(HDC hdc);											//좌표 기본설정()
	void render(HDC hdc, int destX, int destY);						//좌표 직접 입력
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);		//잘라 붙이기

	

//=================================================================================================
//	## [ 알파 렌더 ] ##
//=================================================================================================

	//알파 렌더
	void alphaRender(HDC hdc, BYTE alpha);							//좌표 기본설정()
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);	//좌표 직접 입력
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);		//잘라 붙이기


//=================================================================================================
//	## [ 프레임 렌더 ] ##
//=================================================================================================

	//프레임 랜더
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

//====================================================================
//	## [ 루프렌더 ] ##
//====================================================================

	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);


//=================================================================================================
//	## [ 사이즈 렌더 ] ##
//=================================================================================================

	void sizeRender(HDC hdc, int sizeW, int sizeH);
	void sizeRender(HDC hdc, int destX, int destY, int sizeW, int sizeH);

//=================================================================================================
//	## [  트렌스 렌더 ] ##
//=================================================================================================

	void transRender(HDC hdc, bool isTrans, COLORREF color);
	void transRender(HDC hdc, int destX, int destY, bool isTrans, COLORREF color);


//=================================================================================================
//	## [ 특수 ] ##
//================================================================================================

	void setImageDC(HDC hdc, int sizeW, int sizeH);

	void frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);
	

//=================================================================================================
//	## [ 인라인 함수 ] (겟터, 셋터) ##
//=================================================================================================

	//DC얻기
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	//DC 세팅
	inline void setMemDC(HDC setHDC) { _imageInfo->hMemDC = setHDC; }

	//이미지 x좌표
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }

	//이미지 y좌표
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	//이미지 x,y 시작 좌표 세팅
	inline void setStartPoint(float x, float y) { _imageInfo->x = x; _imageInfo->y = y; }

	//이미지 중심 좌표
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//이미지 가로, 세로크기
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	//이미지 가로, 세로크기 조정
	inline void setWidth(int width) { _imageInfo->width = width; }
	inline void setHeight(int height) { _imageInfo->height = height; }

	//이미지 가로, 세로크기 동시
	inline void setSize(int width, int height) { _imageInfo->width = width; _imageInfo->height = height; }

	//바운딩 박스(충돌용 렉트)
	inline RECT frameBox(void)
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
					(int)_imageInfo->x + _imageInfo->frameWidth,
					(int)_imageInfo->y + _imageInfo->frameHeight };

		return rc;
	}

	//바운딩 박스(충돌용 렉트)
	inline RECT boundingBox(void)
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->width,
			(int)_imageInfo->y + _imageInfo->height };

		return rc;
	}



	// !! [ 프레임 관련 함수 ] !! ================================================================================================= 

	//프레임 X
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	//프레임 Y
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	//이미지 1프레임 가로, 세로 크기
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	//최대프레임 x,y 갯수
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

};//클래스 끝

