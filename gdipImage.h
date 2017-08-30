#pragma once

//=================================================================================================
//	##	GDI+ 이미지 [ gdiPlusImage ] (헤드)	##
//=================================================================================================

class gdipImage
{
public:
	typedef struct tagGDI
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

		//초기화
		tagGDI()
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
		}

	}GDI_INFO, *LPGDI_INFO;

private:
	LPGDI_INFO		_gdiInfo;		//GDI정보
	CHAR*			_fileName;		//이미지 이름
	Graphics*		_gdi;
	Graphics*		_gdiRender;
	Image*			_gdiImg;

public:
	//초기화
	HRESULT init(int maxFrameX, int maxFrameY);
	HRESULT init(const WCHAR* fileName, int maxFrameX, int maxFrameY);
	//해제
	void release(void);

	//=================================================================================================
	//	## [ GDI+프레임 렌더 ] ##
	//=================================================================================================

	//프레임 랜더(프레임 조절 - 원하는 프레임 선정)
	void gdiFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	gdipImage();
	~gdipImage();
};







