#include "stdafx.h"
#include "gdipImage.h"



//=================================================================================================
//	##	GDI+ �̹��� [ gdiPlusImage ] (Ŭ����)	##
//=================================================================================================
gdipImage::gdipImage() : _gdiInfo(NULL), _fileName(NULL)
{
}
gdipImage::~gdipImage()
{
}



//=================================================================================================
//	##	[ �ʱ�ȭ ]	##
//=================================================================================================

HRESULT gdipImage::init(int maxFrameX, int maxFrameY)
{
	return S_OK;
}

HRESULT gdipImage::init(const WCHAR* fileName, int maxFrameX, int maxFrameY)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ���ٰ�!
	if (_gdiInfo != NULL) this->release();
	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� ���� �� �ʱ�ȭ�ϱ�
	_gdiInfo = new GDI_INFO;
	//_gdiInfo->hMemDC = CreateCompatibleDC(hdc);		//��¼ӵ������� ���� �޸� ���� �Ҵ�

	//== ## [ �����ڵ� ���ڿ��� ��ȯ ] ## ==
	//USES_CONVERSION;
	//WCHAR* wstr;
	//char str[100];
	//wsprintf(str, fileName);
	//wstr = A2W(str);
	//== ## [ ���� ���� ] ## ==
	_gdiImg = new Image(fileName);

	//_gdiInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _gdiImg->GetWidth() , _gdiImg->GetHeight());
	//_gdiInfo->hOBit = (HBITMAP)SelectObject(_gdiInfo->hMemDC, _gdiInfo->hBit);

	//== ## [ �׸��� ] ## ==
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

	//�����̸�
	/*int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);*/

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void gdipImage::release(void)
{
	//�̹��� ������ ������ ���� ���Ѷ�
	if (_gdiInfo)
	{
		//�̹��� ����
		DeleteDC(_gdiInfo->hMemDC);

		//����Ʈ ����
		SAFE_DELETE(_gdiInfo);
		SAFE_DELETE(_gdiImg);
		//SAFE_DELETE_ARRAY(_fileName);
	}
}


//=================================================================================================
//	## [ GDI+������ ���� ] ##
//=================================================================================================

//������ ����(������ ���� - ���ϴ� ������ ����)
void gdipImage::gdiFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//�̹��� ����ó�� - �Է� ���� ������ ������ �ִ� ������ �������� Ŭ �� �۵���
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


	//BitBlt : DC���� �������� ���� ��Ӻ��� ���ִ� �Լ�
	/*BitBlt(hdc, destX, destY, _gdiInfo->frameWidth, _gdiInfo->frameHeight,
		_gdiInfo->hMemDC,
		_gdiInfo->currentFrameX * _gdiInfo->frameWidth,
		_gdiInfo->currentFrameY * _gdiInfo->frameHeight,
		SRCCOPY);*/

}

