#include "stdafx.h"
#include "gdipImage.h"



//=================================================================================================
//	##	GDI+ 이미지 [ gdiPlusImage ] (클래스)	##
//=================================================================================================
gdipImage::gdipImage() : _gdiInfo(NULL), _fileName(NULL)
{
}
gdipImage::~gdipImage()
{
}



//=================================================================================================
//	##	[ 초기화 ]	##
//=================================================================================================

HRESULT gdipImage::init(int maxFrameX, int maxFrameY)
{
	return S_OK;
}

HRESULT gdipImage::init(const WCHAR* fileName, int maxFrameX, int maxFrameY)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 해줄것!
	if (_gdiInfo != NULL) this->release();
	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 새로 생성 후 초기화하기
	_gdiInfo = new GDI_INFO;
	//_gdiInfo->hMemDC = CreateCompatibleDC(hdc);		//출력속도개선을 위한 메모리 공간 할당

	//== ## [ 유니코드 문자열로 변환 ] ## ==
	//USES_CONVERSION;
	//WCHAR* wstr;
	//char str[100];
	//wsprintf(str, fileName);
	//wstr = A2W(str);
	//== ## [ 파일 저장 ] ## ==
	_gdiImg = new Image(fileName);

	//_gdiInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _gdiImg->GetWidth() , _gdiImg->GetHeight());
	//_gdiInfo->hOBit = (HBITMAP)SelectObject(_gdiInfo->hMemDC, _gdiInfo->hBit);

	//== ## [ 그리기 ] ## ==
	//_gdi = new Graphics(_gdiInfo->hMemDC);
	//_gdi->DrawImage(_gdiImg, 0, 0 ,_gdiImg->GetWidth(), _gdiImg->GetHeight());

	_gdiInfo->width = _gdiImg->GetWidth();
	_gdiInfo->height = _gdiImg->GetHeight();
	_gdiInfo->currentFrameX = 0;
	_gdiInfo->currentFrameY = 0;
	_gdiInfo->maxFrameX = maxFrameX - 1;
	_gdiInfo->maxFrameY = maxFrameY - 1;
	_gdiInfo->frameWidth = _gdiImg->GetWidth() / maxFrameX;
	_gdiInfo->frameHeight = _gdiImg->GetHeight() / maxFrameY;

	//파일이름
	/*int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);*/

	//DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void gdipImage::release(void)
{
	//이미지 정보가 있으면 해제 시켜라
	if (_gdiInfo)
	{
		//이미지 삭제
		DeleteDC(_gdiInfo->hMemDC);

		//포인트 삭제
		SAFE_DELETE(_gdiInfo);
		SAFE_DELETE(_gdiImg);
		//SAFE_DELETE_ARRAY(_fileName);
	}
}


//=================================================================================================
//	## [ GDI+프레임 렌더 ] ##
//=================================================================================================

//프레임 랜더(프레임 조절 - 원하는 프레임 선정)
void gdipImage::gdiFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//이미지 예외처리 - 입력 받은 프레임 개수가 최대 프레임 개수보다 클 때 작동됨
	_gdiInfo->currentFrameX = currentFrameX;
	_gdiInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _gdiInfo->maxFrameX)
	{
		_gdiInfo->currentFrameX = _gdiInfo->maxFrameX;
	}
	if (currentFrameY > _gdiInfo->maxFrameY)
	{
		_gdiInfo->currentFrameY = _gdiInfo->maxFrameY;
	}
	
	//CreateCompatibleDC(hdc);
	_gdiRender = new Graphics(hdc);
	_gdiRender->DrawImage(_gdiImg, destX, destY,
		_gdiInfo->currentFrameX * _gdiInfo->frameWidth,
		_gdiInfo->currentFrameY * _gdiInfo->frameHeight,
		_gdiInfo->frameWidth, _gdiInfo->frameHeight, UnitPixel);
	SAFE_DELETE(_gdiRender);


	//BitBlt : DC간의 영역끼리 서로 고속복사 해주는 함수
	/*BitBlt(hdc, destX, destY, _gdiInfo->frameWidth, _gdiInfo->frameHeight,
		_gdiInfo->hMemDC,
		_gdiInfo->currentFrameX * _gdiInfo->frameWidth,
		_gdiInfo->currentFrameY * _gdiInfo->frameHeight,
		SRCCOPY);*/

}

