#include "stdafx.h"
#include "image.h"
#pragma comment(lib, "msimg32.lib") //���ĺ��带 ����ϱ� ���ؼ� ���̺귯�� �߰�

//=================================================================================================
//	##	�̹��� [ Image ] (Ŭ����)	##
//=================================================================================================

//������ �ʱ�ȭ
image::image() : _imageInfo(NULL), _fileName(NULL), _isTrans(FALSE), _transColor(RGB(0, 0, 0))
{
}
image::~image()
{
}

//�� ��Ʈ������ �ʱ�ȭ
HRESULT image::init(int width, int height)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ���ٰ�!
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� ���� �� �ʱ�ȭ�ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//��¼ӵ������� ���� �޸� ���� �Ҵ�
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//�����̸�
	_fileName = NULL;

	//����Ű �÷� ����
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	//���ҽ� ��� ���µ� ���н� ���
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//�̹��� ���ҽ��� �ʱ�ȭ(������)
HRESULT image::init(const DWORD resID, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ���ٰ�!
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� ���� �� �ʱ�ȭ�ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//��¼ӵ������� ���� �޸� ���� �Ҵ�
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID));
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//�����̸�
	_fileName = NULL;

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ��� ���µ� ���н� ���
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//=================================================================================================
//	## [ �̹����� ���� �ʱ�ȭ ] (�ַ� ���)  ##
//=================================================================================================

// !! [ �̹��� ���Ϸ� �ʱ�ȭ(�� ���) ] !! =================================================================================================
HRESULT image::init(const CHAR * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ���ٰ�!
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� ���� �� �ʱ�ȭ�ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//��¼ӵ������� ���� �޸� ���� �Ҵ�
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ��� ���µ� ���н� ���
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

// !! [ �̹��� ���Ϸ� �ʱ�ȭ(�ַ� ���) ] - ������������ �ʱ�ȭ ���� !! =================================================================================================
HRESULT image::init(const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ���ٰ�!
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� ���� �� �ʱ�ȭ�ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//��¼ӵ������� ���� �޸� ���� �Ҵ�
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ��� ���µ� ���н� ���
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

// !! [ ������ �̹��� �ʱ�ȭ(�ַ� ���) ] !! ================================================================================================= 
HRESULT image::init(const char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ���ٰ�!
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� ���� �� �ʱ�ȭ�ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//��¼ӵ������� ���� �޸� ���� �Ҵ�
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

	//�����̸�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ��� ���µ� ���н� ���
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

// !! [ ������ �̹��� �ʱ�ȭ(�ַ� ���) ] - ������������ �ʱ�ȭ ���� !! =================================================================================================
HRESULT image::init(const char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ���ٰ�!
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� ���� �� �ʱ�ȭ�ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//��¼ӵ������� ���� �޸� ���� �Ҵ�
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

	//�����̸�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ��� ���µ� ���н� ���
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}


// !! [ ���� �귻�� �ʱ�ȭ ] !! =================================================================================================
HRESULT image::initForAlphaBlend(void)
{
	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//���ĺ��� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;	//���� ȥ�չ��(����ä�� ������?)

	//�̹��� ���� ���� ������ �ʱ�ȭ�ϱ�
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}


//������ �̹��� �ʱ�ȭ (!!Ư��!!)
HRESULT image::scaleInit(int width, int height, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ���ٰ�!
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� ���� �� �ʱ�ȭ�ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//��¼ӵ������� ���� �޸� ���� �Ҵ�
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//�����̸�
	_fileName = NULL;

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ��� ���µ� ���н� ���
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}




//����� ����(������ ��������?, � ���� ��������?)
void image::setTransColor(BOOL isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}

//�̹��� ���� ����
void image::release(void)
{
	//�̹��� ������ ������ ���� ���Ѷ�
	if (_imageInfo)
	{
		//�̹��� ����
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//����Ʈ ����
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		//�����÷�Ű �ʱ�ȭ
		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}
}


//=================================================================================================
// ## [ �Ϲ� ���� ] ##
//=================================================================================================

//���� (0, 0������ ���)
void image::render(HDC hdc)
{
	//����� ���� ������ ���� �۵�

	if (_isTrans)	//���� �۵�
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư�������� �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt
		(
			hdc,					//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			_imageInfo->x,			//����� ��ǥ ����x
			_imageInfo->y,			//����� ��ǥ ����y
			_imageInfo->width,		//����� �̹��� ����ũ��
			_imageInfo->height,		//����� �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� �޸�DC
			0, 0,					//���� ��������
			_imageInfo->width,		//���� ���� ����ũ��
			_imageInfo->height,		//���� ���� ����ũ��
			_transColor				//�����Ҷ� ������ ����(����Ÿ ���� �����)
		);
	}
	else//���� ���۵�
	{
		//BitBlt : DC���� �������� ���� ��Ӻ��� ���ִ� �Լ�
		BitBlt(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}


//���� (���� ������ ��ǥ�� �̹��� ����Ѵ�)
void image::render(HDC hdc, int destX, int destY)
{
	//����� ���� ������ ���� �۵�

	if (_isTrans)	//���� �۵�
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư�������� �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt
		(
			hdc,					//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			destX, destY,			//����� ��ǥ ����x, y
			_imageInfo->width,		//����� �̹��� ����ũ��
			_imageInfo->height,		//����� �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� �޸�DC
			0, 0,					//���� ��������
			_imageInfo->width,		//���� ���� ����ũ��
			_imageInfo->height,		//���� ���� ����ũ��
			_transColor				//�����Ҷ� ������ ����(����Ÿ ���� �����)
		);
	}
	else//���� ���۵�
	{
		//BitBlt : DC���� �������� ���� ��Ӻ��� ���ִ� �Լ�
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

//���� (���� �ٿ��ֱ�)
void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//����� ���� ������ ���� �۵�

	if (_isTrans)	//���� �۵�
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư�������� �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt
		(
			hdc,					//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			destX, destY,			//����� ��ǥ ����x, y
			sourWidth,				//����� �̹��� ����ũ��
			sourHeight,				//����� �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� �޸�DC
			sourX, sourY,			//���� ��������
			sourWidth,				//���� ���� ����ũ��
			sourHeight,				//���� ���� ����ũ��
			_transColor				//�����Ҷ� ������ ����(����Ÿ ���� �����)
		);
	}
	else//���� ���۵�
	{
		//BitBlt : DC���� �������� ���� ��Ӻ��� ���ִ� �Լ�
		BitBlt(hdc, destX, destY, sourWidth, sourHeight, _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}


//=================================================================================================
// ## [ ���ķ��� ] ## 
//=================================================================================================

//���� ���� (0, 0������ ���)
void image::alphaRender(HDC hdc, BYTE alpha)
{
	//���ĺ��� ó������ϳ�?
	//���ĺ��� ����� �� �ֵ��� �ʱ�ȭ �ض�
	if (!_blendImage) initForAlphaBlend();

	//���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)	//���� �۵�
	{
		//1. ����ؾ� �� DC�� �׷��� �ִ� ������ �����̹����� �׸���
		BitBlt
		(
			_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc, _imageInfo->x, _imageInfo->y,
			SRCCOPY
		);
		//2. �����̹����� ����� ������ �����̹����� �׸���
		GdiTransparentBlt
		(
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_transColor
		);
		//3. �����̹����� ȭ�鿡 �׸���
		AlphaBlend
		(
			hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendFunc
		);
	}
	else//���� ���۵�
	{
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

//���� ���� (���ϴ� ��ǥ�� ���)
void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	//���ĺ��� ó������ϳ�?
	//���ĺ��� ����� �� �ֵ��� �ʱ�ȭ �ض�
	if (!_blendImage) initForAlphaBlend();

	//���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)	//���� �۵�
	{
		//1. ����ؾ� �� DC�� �׷��� �ִ� ������ �����̹����� �׸���
		BitBlt
		(
			_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc, destX, destY,
			SRCCOPY
		);
		//2. �����̹����� ����� ������ �����̹����� �׸���
		GdiTransparentBlt
		(
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_transColor
		);
		//3. �����̹����� ȭ�鿡 �׸���
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else//���� ���۵�
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

//���� ���� (�߶� �ٿ��ֱ�)
void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//���ĺ��� ó������ϳ�?
	//���ĺ��� ����� �� �ֵ��� �ʱ�ȭ �ض�
	if (!_blendImage) initForAlphaBlend();

	//���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)	//���� �۵�
	{
		//1. ����ؾ� �� DC�� �׷��� �ִ� ������ �����̹����� �׸���
		BitBlt
		(
			_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc, destX, destY,//0,0�ص� ���� �ʳ�?
			SRCCOPY
		);
		//2. �����̹����� ����� ������ �����̹����� �׸���
		GdiTransparentBlt
		(
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_transColor
		);
		//3. �����̹����� ȭ�鿡 �׸���
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, _blendImage->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
	}
	else//���� ���۵�
	{
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, _imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
	}
}


//=================================================================================================
//	## [ ������ ���� ] ##
//=================================================================================================

//������ ����(������ ������ - ��� �ݺ�)
void image::frameRender(HDC hdc, int destX, int destY)
{
	//����� ���� ������ ���� �۵�

	if (_isTrans)	//���� �۵�
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư�������� �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt
		(
			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			destX, destY,											//����� ��ǥ ����x, y
			_imageInfo->frameWidth,									//����� �̹��� ����ũ��
			_imageInfo->frameHeight,								//����� �̹��� ����ũ��
			_imageInfo->hMemDC,										//����� ��� �޸�DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//���� �������� X
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//���� �������� Y
			_imageInfo->frameWidth,									//���� ���� ����ũ��
			_imageInfo->frameHeight,								//���� ���� ����ũ��
			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
		);
	}
	else//���� ���۵�
	{
		//BitBlt : DC���� �������� ���� ��Ӻ��� ���ִ� �Լ�
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

//������ ����(������ ���� - ���ϴ� ������ ����)
void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//�̹��� ����ó�� - �Է� ���� ������ ������ �ִ� ������ �������� Ŭ �� �۵���
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

	//����� ���� ������ ���� �۵�

	if (_isTrans)	//���� �۵�
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư�������� �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt
		(
			hdc,													//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			destX, destY,											//����� ��ǥ ����x, y
			_imageInfo->frameWidth,									//����� �̹��� ����ũ��
			_imageInfo->frameHeight,								//����� �̹��� ����ũ��
			_imageInfo->hMemDC,										//����� ��� �޸�DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//���� �������� X
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//���� �������� Y			
			_imageInfo->frameWidth,									//���� ���� ����ũ��
			_imageInfo->frameHeight,								//���� ���� ����ũ��
			_transColor												//�����Ҷ� ������ ����(����Ÿ ���� �����)
		);
	}
	else//���� ���۵�
	{
		//BitBlt : DC���� �������� ���� ��Ӻ��� ���ִ� �Լ�
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}


//====================================================================
//	## [ �������� ] ##
//====================================================================

void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//offset ���� ������ ��� �����ϱ�
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//�׷����� ���� ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� DC ���� (ȭ��ũ��)
	RECT rcDest;

	//�׷��� �� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//���� ��������
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�ҽ� ������ ���� ���
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������� ��������)
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �׸��� ����ŭ ���Ұ��� �÷��ش�
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ��������
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ� ������ ���� ���
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������� ��������)
			if (x + sourWidth > drawAreaW)
			{
				//�Ѿ �׸��� ����ŭ ���Ұ��� �÷��ش�
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//�׷����� ����
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//�׷�����(�Ϲݷ���-�̹����߶󼭺��̱�)
			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);
		}
	}
}

void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
}



//=================================================================================================
//	## [ ������ ���� ] ##
//=================================================================================================


void image::sizeRender(HDC hdc, int sizeW, int sizeH)
{
	SetStretchBltMode(hdc, COLORONCOLOR);	//�̹��� ����� ������ ��!
	StretchBlt(hdc, _imageInfo->x, _imageInfo->y, sizeW, sizeH, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
}

void image::sizeRender(HDC hdc, int destX, int destY, int sizeW, int sizeH)
{
	SetStretchBltMode(hdc, COLORONCOLOR);	//�̹��� ����� ������ ��!
	StretchBlt(hdc, destX, destY, sizeW, sizeH, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
	//_imageInfo->x = destX;
	//_imageInfo->y = destY;
}

//=================================================================================================
//	## [ Ʈ���� ���� ] ##
//=================================================================================================


void image::transRender(HDC hdc, bool isTrans = false, COLORREF color = RGB(0, 0, 0))
{
	//����� ���� ������ ���� �۵�

	if (isTrans)	//���� �۵�
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư�������� �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt
		(
			hdc,					//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			_imageInfo->x,			//����� ��ǥ ����x
			_imageInfo->y,			//����� ��ǥ ����y
			_imageInfo->width,		//����� �̹��� ����ũ��
			_imageInfo->height,		//����� �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� �޸�DC
			0, 0,					//���� ��������
			_imageInfo->width,		//���� ���� ����ũ��
			_imageInfo->height,		//���� ���� ����ũ��
			color					//�����Ҷ� ������ ����(����Ÿ ���� �����)
		);
	}
	else//���� ���۵�
	{
		//BitBlt : DC���� �������� ���� ��Ӻ��� ���ִ� �Լ�
		BitBlt(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}


void image::transRender(HDC hdc, int destX, int destY, bool isTrans = false, COLORREF color = RGB(0,0,0))
{
	//����� ���� ������ ���� �۵�

	if (isTrans)	//���� �۵�
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư�������� �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt
		(
			hdc,					//������ ����� DC (ȭ�鿡 �������� ȭ��DC)
			destX, destY,			//����� ��ǥ ����x, y
			_imageInfo->width,		//����� �̹��� ����ũ��
			_imageInfo->height,		//����� �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� �޸�DC
			0, 0,					//���� ��������
			_imageInfo->width,		//���� ���� ����ũ��
			_imageInfo->height,		//���� ���� ����ũ��
			color					//�����Ҷ� ������ ����(����Ÿ ���� �����)
		);
	}
	else//���� ���۵�
	{
		//BitBlt : DC���� �������� ���� ��Ӻ��� ���ִ� �Լ�
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

//=================================================================================================
//	## [ Ư�� ] ##
//=================================================================================================



void image::setImageDC(HDC hdc, int sizeW, int sizeH)
{
	//��� ����
	RECT BK_ColorRC = { 0,0, _imageInfo->width, _imageInfo->height };
	//����� �̹���DC�� �׷���
	setRectangle(_imageInfo->hMemDC, BK_ColorRC, _transColor, true);

	SetStretchBltMode(_imageInfo->hMemDC, COLORONCOLOR);	//�̹��� ����� ������ ��!
	StretchBlt(_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc, 0, 0, sizeW, sizeH, SRCCOPY);
}



//===========================================================================================================
//											#������ ���� ����
//===========================================================================================================
void image::frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	if(!_blendImage) initForAlphaBlend();

	//���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;

	//�̹��� ����ó��
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

	if(_isTrans)//���� ���ٲ���?
	{
		BitBlt(//�̹� �׷����ִ� �͵��� ���� �׸���.
			   _blendImage->hMemDC,
			   0,
			   0,
			   _imageInfo->frameWidth,		//���� ���� ����ũ��
			   _imageInfo->frameHeight,	//���� ���� ����ũ��
			   hdc,						//�̸� �׷��� �ִ� DC
			   destX,						//�׷����ִ� DC�� �κн����� + ���� WIDTH��ŭ _blendimage�� ����
			   destY,
			   SRCCOPY
		);
		//�� ���� �׸��� ���� ���� �̹�����
		//GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư�������� �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt(
			_blendImage->hMemDC,
			0,
			0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,  //���� ��������
			_imageInfo->currentFrameY * _imageInfo->frameHeight, //���� ��������
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
		//3. �����̹����� ȭ�鿡 �׸���
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
	else//���� �̹��� �״�� ����Ҳ���?
	{
		//BitBlt : DC���� �������� ���� ��Ӻ��� ���ִ� �Լ�
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			   _imageInfo->hMemDC,
			   _imageInfo->currentFrameX * _imageInfo->frameWidth,
			   _imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

