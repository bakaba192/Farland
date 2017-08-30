#include "stdafx.h"
#include "d2dImage.h"




//=================================================================================================
//	##	D2D �̹��� [ D2D Image ] (Ŭ����)	##
//=================================================================================================
d2dImage::d2dImage() : _d2dInfo(NULL)
{
}

d2dImage::~d2dImage()
{
}


//=================================================================================================
//	##	�ʱ�ȭ	##
//=================================================================================================

//�Ϲ� �ʱ�ȭ
HRESULT d2dImage::init(const WCHAR * fileName)
{
	// ���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ���ٰ�!
	if (_d2dInfo != NULL) this->release();

	//d2d �����
	this->createD2D(fileName);

	//�̹��� ���� ���� ���� �� �ʱ�ȭ�ϱ�
	_d2dInfo = new D2D_INFO;
	//���� �ֱ�
	//_d2dInfo->pDCRT->CreateBitmapFromWicBitmap(pWicBitmap,NULL, &_d2dInfo->pD2DBitmap);
	//pDCRT->CreateBitmapFromWicBitmap(pWicBitmap, NULL, &pD2DBitmap);
	UINT sizeW;
	UINT sizeH;
	pWicBitmap->GetSize(&sizeW, &sizeH);
	_d2dInfo->width = sizeW;
	_d2dInfo->height = sizeH;
	_d2dInfo->RectF = { 0,0, (float)sizeW , (float)sizeH };

	//���ڴ��� ����
	pWicImageDecoder->Release();
	pWicFrameDecoder->Release();
	//pWicBitmap->Release();

	//wic���丮 ����
	pWicFactory->Release();

	return S_OK;
}

//�Ϲ� �ʱ�ȭ - ��ġ��ǥ
HRESULT d2dImage::init(const WCHAR * fileName, float x, float y)
{
	// ���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ���ٰ�!
	if (_d2dInfo != NULL) this->release();

	//d2d �����
	this->createD2D(fileName);

	//�̹��� ���� ���� ���� �� �ʱ�ȭ�ϱ�
	_d2dInfo = new D2D_INFO;
	UINT sizeW;
	UINT sizeH;
	pWicBitmap->GetSize(&sizeW, &sizeH);
	_d2dInfo->width = sizeW;
	_d2dInfo->height = sizeH;
	_d2dInfo->RectF = { 0,0, (float)sizeW , (float)sizeH };
	_d2dInfo->x = x;
	_d2dInfo->x = y;

	//���ڴ��� ����
	pWicImageDecoder->Release();
	pWicFrameDecoder->Release();
	//pWicBitmap->Release();

	//wic���丮 ����
	pWicFactory->Release();

	return S_OK;
}


HRESULT d2dImage::frameInit(const WCHAR * fileName, int maxFrameX, int maxFrameY)
{
	// ���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ���ٰ�!
	if (_d2dInfo != NULL) this->release();

	//d2d �����
	this->createD2D(fileName);

	//�̹��� ���� ���� ���� �� �ʱ�ȭ�ϱ�
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


	//���ڴ��� ����
	pWicImageDecoder->Release();
	pWicFrameDecoder->Release();
	//pWicBitmap->Release();

	//wic���丮 ����
	pWicFactory->Release();

	return S_OK;
}

//����
void d2dImage::release(void)
{
	if (_d2dInfo)
	{
		//���丮 ����
		pD2DFactory->Release();
		//���� ������ ����(win��Ʈ�� ����)
		pWicBitmap->Release();
		//��Ʈ�� ����
		pWicBitmap->Release();

		//d2d ����
		SAFE_DELETE(_d2dInfo);
	}
}


//=================================================================================================
// ## [ �Ϲ� ���� ] ##
//=================================================================================================


// �⺻�� ���� ����
void d2dImage::render(HDC hdc, float alpha)
{

	//DC�� ���� Ÿ�� ����
	ID2D1DCRenderTarget* pDCRT = NULL;
	pD2DBitmap = NULL;
	//����Ÿ�� ����
	pD2DFactory->CreateDCRenderTarget(&propertiesDC, &pDCRT);
	//wic��Ʈ���� d2d��Ʈ������ ��ȯ
	pDCRT->CreateBitmapFromWicBitmap(pWicBitmap, NULL, &pD2DBitmap);

	//������ ũ�� ��������
	RECT winRC;
	GetClientRect(_hWnd, &winRC);
	//DC����
	pDCRT->BindDC(hdc, &winRC);

	//�׸��� ����
	pDCRT->BeginDraw();


	pDCRT->DrawBitmap(pD2DBitmap, _d2dInfo->RectF, alpha);
	pDCRT->EndDraw();

	//���� Ȯ�� ����~
	pDCRT->Release();
}


//�⺻�� ���� ���� - ��ġ
void d2dImage::render(HDC hdc, float destX, float destY, float alpha)
{

	//DC�� ���� Ÿ�� ����
	ID2D1DCRenderTarget* pDCRT = NULL;
	pD2DBitmap = NULL;
	//����Ÿ�� ����
	pD2DFactory->CreateDCRenderTarget(&propertiesDC, &pDCRT);
	//wic��Ʈ���� d2d��Ʈ������ ��ȯ
	pDCRT->CreateBitmapFromWicBitmap(pWicBitmap, NULL, &pD2DBitmap);

	//��ġ��ǥ ����
	D2D1_RECT_F rcF = D2D1::RectF(destX, destY, destX + pD2DBitmap->GetSize().width, destY + pD2DBitmap->GetSize().height);

	//������ ũ�� ��������
	RECT winRC;
	GetClientRect(_hWnd, &winRC);
	//DC����
	pDCRT->BindDC(hdc, &winRC);

	//�׸��� ����
	pDCRT->BeginDraw();

	pDCRT->DrawBitmap(pD2DBitmap, rcF, alpha);
	pDCRT->EndDraw();

	//���� Ȯ�� ����~
	pDCRT->Release();
}



//=================================================================================================
// ## [ ȸ�� ���� ] ##
//=================================================================================================

//�⺻�� ȸ������
void d2dImage::rotationRender(HDC hdc, float destX, float destY, float angle, ROTATION_CP RCP, float alpha)
{

	//DC�� ���� Ÿ�� ����
	ID2D1DCRenderTarget* pDCRT = NULL;
	pD2DBitmap = NULL;
	//����Ÿ�� ����
	pD2DFactory->CreateDCRenderTarget(&propertiesDC, &pDCRT);
	//wic��Ʈ���� d2d��Ʈ������ ��ȯ
	pDCRT->CreateBitmapFromWicBitmap(pWicBitmap, NULL, &pD2DBitmap);

	//��ġ��ǥ ����
	D2D1_RECT_F rcF = D2D1::RectF(destX, destY, destX + pD2DBitmap->GetSize().width, destY + pD2DBitmap->GetSize().height);

	//ȸ����ǥ ����
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

	//������ ũ�� ��������
	RECT winRC;
	GetClientRect(_hWnd, &winRC);
	//DC����
	pDCRT->BindDC(hdc, &winRC);

	//�׸��� ����
	pDCRT->BeginDraw();
	pDCRT->SetTransform(Matrix3x2F::Rotation(angle, rotationCP));
	pDCRT->DrawBitmap(pD2DBitmap, rcF, alpha);
	pDCRT->EndDraw();

	//����
	pDCRT->Release();
}

void d2dImage::rotationRender(HDC hdc, float destX, float destY, float rotationX, float rotationY, float angle, ROTATION_CP RCP, float alpha)
{

	//DC�� ���� Ÿ�� ����
	ID2D1DCRenderTarget* pDCRT = NULL;
	pD2DBitmap = NULL;
	//����Ÿ�� ����
	pD2DFactory->CreateDCRenderTarget(&propertiesDC, &pDCRT);
	//wic��Ʈ���� d2d��Ʈ������ ��ȯ
	pDCRT->CreateBitmapFromWicBitmap(pWicBitmap, NULL, &pD2DBitmap);

	//��ġ��ǥ ����
	D2D1_RECT_F rcF = D2D1::RectF(destX, destY, destX + pD2DBitmap->GetSize().width, destY + pD2DBitmap->GetSize().height);

	//ȸ����ǥ ����
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

	//������ ũ�� ��������
	RECT winRC;
	GetClientRect(_hWnd, &winRC);
	//DC����
	pDCRT->BindDC(hdc, &winRC);

	//�׸��� ����
	pDCRT->BeginDraw();
	pDCRT->SetTransform(Matrix3x2F::Rotation(angle, rotationCP));
	pDCRT->DrawBitmap(pD2DBitmap, rcF, alpha);
	pDCRT->EndDraw();

	//���� Ȯ�� ����~
	pDCRT->Release();
}


//=================================================================================================
// ## [ ������ ���� ] ##
//=================================================================================================

void d2dImage::frameRender(HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float alpha)
{
	//DC�� ���� Ÿ�� ����
	ID2D1DCRenderTarget* pDCRT = NULL;
	pD2DBitmap = NULL;
	//����Ÿ�� ����
	pD2DFactory->CreateDCRenderTarget(&propertiesDC, &pDCRT);
	//wic��Ʈ���� d2d��Ʈ������ ��ȯ
	pDCRT->CreateBitmapFromWicBitmap(pWicBitmap, NULL, &pD2DBitmap);

	//������ ����ó��
	if (currentFrameX >= _d2dInfo->maxFrameX) currentFrameX = _d2dInfo->maxFrameX - 1;
	if (currentFrameY >= _d2dInfo->maxFrameY) currentFrameY = _d2dInfo->maxFrameY - 1;

	//��ġ��ǥ ����
	D2D1_RECT_F rcF = D2D1::RectF(destX, destY, destX + _d2dInfo->frameWidth, destY + _d2dInfo->frameHeight);

	D2D1_RECT_F frameRcF = D2D1::RectF(_d2dInfo->frameWidth *currentFrameX, _d2dInfo->frameHeight *currentFrameY,
		_d2dInfo->frameWidth *currentFrameX + _d2dInfo->frameWidth, _d2dInfo->frameHeight *currentFrameY + _d2dInfo->frameHeight);


	//������ ũ�� ��������
	RECT winRC;
	GetClientRect(_hWnd, &winRC);
	//DC����
	pDCRT->BindDC(hdc, &winRC);

	//�׸��� ����
	pDCRT->BeginDraw();
	pDCRT->DrawBitmap(pD2DBitmap, rcF, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, frameRcF);
	pDCRT->EndDraw();

	//����
	pDCRT->Release();
}

void d2dImage::rFrameRender(HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float angle, ROTATION_CP RCP, float alpha)
{
	//DC�� ���� Ÿ�� ����
	ID2D1DCRenderTarget* pDCRT = NULL;
	pD2DBitmap = NULL;
	//����Ÿ�� ����
	pD2DFactory->CreateDCRenderTarget(&propertiesDC, &pDCRT);
	//wic��Ʈ���� d2d��Ʈ������ ��ȯ
	pDCRT->CreateBitmapFromWicBitmap(pWicBitmap, NULL, &pD2DBitmap);

	//������ ����ó��
	if (currentFrameX >= _d2dInfo->maxFrameX) currentFrameX = _d2dInfo->maxFrameX - 1;
	if (currentFrameY >= _d2dInfo->maxFrameY) currentFrameY = _d2dInfo->maxFrameY - 1;

	//��ġ��ǥ ����
	D2D1_RECT_F rcF = D2D1::RectF(destX, destY, destX + _d2dInfo->frameWidth, destY + _d2dInfo->frameHeight);

	D2D1_RECT_F frameRcF = D2D1::RectF(_d2dInfo->frameWidth *currentFrameX, _d2dInfo->frameHeight *currentFrameY,
		_d2dInfo->frameWidth *currentFrameX + _d2dInfo->frameWidth, _d2dInfo->frameHeight *currentFrameY + _d2dInfo->frameHeight);


	//ȸ����ǥ ����
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

	//������ ũ�� ��������
	RECT winRC;
	GetClientRect(_hWnd, &winRC);
	//DC����
	pDCRT->BindDC(hdc, &winRC);

	//�׸��� ����
	pDCRT->BeginDraw();
	pDCRT->SetTransform(Matrix3x2F::Rotation(angle, rotationCP));
	pDCRT->DrawBitmap(pD2DBitmap, rcF, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, frameRcF);
	pDCRT->EndDraw();

	//����
	pDCRT->Release();
}

void d2dImage::rFrameRender(HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float rotationX, float rotationY, float angle, ROTATION_CP RCP, float alpha)
{
	//DC�� ���� Ÿ�� ����
	ID2D1DCRenderTarget* pDCRT = NULL;
	pD2DBitmap = NULL;
	//����Ÿ�� ����
	pD2DFactory->CreateDCRenderTarget(&propertiesDC, &pDCRT);
	//wic��Ʈ���� d2d��Ʈ������ ��ȯ
	pDCRT->CreateBitmapFromWicBitmap(pWicBitmap, NULL, &pD2DBitmap);

	//������ ����ó��
	if (currentFrameX >= _d2dInfo->maxFrameX) currentFrameX = _d2dInfo->maxFrameX - 1;
	if (currentFrameY >= _d2dInfo->maxFrameY) currentFrameY = _d2dInfo->maxFrameY - 1;

	//��ġ��ǥ ����
	D2D1_RECT_F rcF = D2D1::RectF(destX, destY, destX + _d2dInfo->frameWidth, destY + _d2dInfo->frameHeight);

	D2D1_RECT_F frameRcF = D2D1::RectF(_d2dInfo->frameWidth *currentFrameX, _d2dInfo->frameHeight *currentFrameY,
		_d2dInfo->frameWidth *currentFrameX + _d2dInfo->frameWidth, _d2dInfo->frameHeight *currentFrameY + _d2dInfo->frameHeight);


	//ȸ����ǥ ����
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

	//������ ũ�� ��������
	RECT winRC;
	GetClientRect(_hWnd, &winRC);
	//DC����
	pDCRT->BindDC(hdc, &winRC);

	//�׸��� ����
	pDCRT->BeginDraw();
	pDCRT->SetTransform(Matrix3x2F::Rotation(angle, rotationCP));
	pDCRT->DrawBitmap(pD2DBitmap, rcF, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, frameRcF);
	pDCRT->EndDraw();

	//����
	pDCRT->Release();
}


//=================================================================================================
// ## [ Ư�� ���� ] ##
//=================================================================================================

//
void d2dImage::xFrameRender(HDC hdc, float destX, float destY, float lengthY, int currentFrameX, float angle, TELESCOPIC_DIRECTION TD, ROTATION_CP RCP, float rotationX, float rotationY, float alpha)
{
	//DC�� ���� Ÿ�� ����
	ID2D1DCRenderTarget* pDCRT = NULL;
	pD2DBitmap = NULL;
	//����Ÿ�� ����
	pD2DFactory->CreateDCRenderTarget(&propertiesDC, &pDCRT);
	//wic��Ʈ���� d2d��Ʈ������ ��ȯ
	pDCRT->CreateBitmapFromWicBitmap(pWicBitmap, NULL, &pD2DBitmap);

	//������ ����ó��
	if (currentFrameX >= _d2dInfo->maxFrameX) currentFrameX = _d2dInfo->maxFrameX - 1;
	if (lengthY >= _d2dInfo->height) lengthY = _d2dInfo->height;


	//��ġ��ǥ ����
	D2D1_RECT_F rcF;
	if (TD == TD_CENTER) rcF = D2D1::RectF(destX - _d2dInfo->frameWidth / 2, destY - lengthY / 2, destX - _d2dInfo->frameWidth / 2 + _d2dInfo->frameWidth, destY + lengthY / 2);
	if (TD == TD_UP) rcF = D2D1::RectF(destX - _d2dInfo->frameWidth / 2, destY - lengthY, destX - _d2dInfo->frameWidth / 2 + _d2dInfo->frameWidth, destY);
	if (TD == TD_DOWN) rcF = D2D1::RectF(destX - _d2dInfo->frameWidth / 2, destY, destX - _d2dInfo->frameWidth / 2 + _d2dInfo->frameWidth, destY + lengthY);

	D2D1_RECT_F frameRcF = D2D1::RectF(_d2dInfo->frameWidth *currentFrameX, 0,
		_d2dInfo->frameWidth *currentFrameX + _d2dInfo->frameWidth, lengthY);

	//ȸ����ǥ ����
	D2D1_POINT_2F rotationCP;
	if (RCP != RCP_CENTER || RCP != RCP_LEFT || RCP != RCP_RIGHT) RCP = RCP_CENTER;
	if (RCP == RCP_CENTER)	rotationCP = Point2F(rotationX + destX, rotationY + destY);
	if (RCP == RCP_LEFT)	rotationCP = Point2F(rotationX + destX - _d2dInfo->frameWidth / 2, rotationY + destY);
	if (RCP == RCP_RIGHT)	rotationCP = Point2F(rotationX + destX + _d2dInfo->frameWidth / 2, rotationY + destY);


	//������ ũ�� ��������
	RECT winRC;
	GetClientRect(_hWnd, &winRC);
	//DC����
	pDCRT->BindDC(hdc, &winRC);

	//�׸��� ����
	pDCRT->BeginDraw();
	pDCRT->SetTransform(Matrix3x2F::Rotation(angle, rotationCP));
	pDCRT->DrawBitmap(pD2DBitmap, rcF, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, frameRcF);
	pDCRT->EndDraw();

	//����
	pDCRT->Release();
}






//d2d �����
void d2dImage::createD2D(const WCHAR* fileName)
{


	//���丮 ���� �ʱ�ȭ
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
	// D2D1_FACTORY_TYPE_SINGLE_THREADED (0) : �̱� ������ ����� Factory ��ü ����
	// D2D1_FACTORY_TYPE_MULTI_THREADED (1) : ��Ƽ ������ ����� Factory ��ü ����

	//������â Ŭ���̾�Ʈ ���� ũ�� ��������
	RECT winRC;
	GetClientRect(_hWnd, &winRC);

	//������â Ŭ���̾�Ʈ ���� ũ�� ����ϱ�
	D2D1_SIZE_U winSize = SizeU(winRC.right - winRC.left, winRC.bottom - winRC.top);


	//���� Ÿ�� ���� ���� ->�Ϲݿ�
	//pD2DFactory->CreateHwndRenderTarget(RenderTargetProperties(), HwndRenderTargetProperties(_hWnd, winSize), &pRenderTarget);

	//DC�� �׸���� ����
	propertiesDC = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
		0,
		0,
		D2D1_RENDER_TARGET_USAGE_NONE,
		D2D1_FEATURE_LEVEL_DEFAULT);


	//DC�� ���� Ÿ��
	//pD2DFactory->CreateDCRenderTarget(&propertiesDC, &pDCRT);

	//WIC���丮 ����
	pWicFactory = NULL;

	//COM���̺귯�� �ʱ�ȭ - �ٽ� �� �ϳ�
	CoInitialize(NULL);

	//���丮 �������̽� ��ü ����
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pWicFactory));

	//�̹��� �ؼ��� ���ڴ� ���� [ ��Ʈ�� ���ڴ� ] -> ���� �б����� ����
	pWicImageDecoder = NULL;

	//�̹��� �б�
	pWicFactory->CreateDecoderFromFilename(fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pWicImageDecoder);
	//CreateDecoderFromFilename(���� ���, ���ڴ� ����??(��), �б� or ���� or �а� ���� ����(���� �б��), ���ڴ� ĳ�� �ɼ�??(��), ���ڴ�(�Ƹ��� �ε��� �̹����� ���ڴ��� ��� ��))

	//�����Ӵ����� �ؼ��� ���ڴ� ���� [ ������ ���ڴ� ] -> ex) gif�� ���� �������� �̹����� �� ��
	pWicFrameDecoder = NULL;

	//���ڴ����� ������ ��� -> �Ƹ��� ������ ���ڴ��� �̹����� gif��� ������ ���ڴ��� �ִ� ��....
	pWicImageDecoder->GetFrame(0, &pWicFrameDecoder);
	//getFrame(������ ��������?,�������� �̹��� �ֱ�!)

	//���� ������ ����-> �ε��� �̹����� ��Ʈ������ ��ȯ�ϱ� ���� ��
	//IWICFormatConverter* pWicBitmap = NULL;

	//���� ������ ��ü ���� ->�Ƹ��� wic�� ��Ʈ���� �����ϴ� ��...
	pWicFactory->CreateFormatConverter(&pWicBitmap);

	//�ε��� �̹����� ù ��° �����ӿ� ������ �� �ִ� ������ ���ڴ��� �Ѱܼ� 
	//�ε��� �̹�����  WIC�� ��Ʈ������ ��ȭ(���� ������ �ʱ�ȭ)
	pWicBitmap->Initialize(pWicFrameDecoder, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);

	//��ȯ�� �̹��� ������ ����Ͽ� Direct2D�� ��Ʈ������ ��ȯ(���� Ÿ�ٿ��� ��ȯ)
	//��ȯ�� ���ؼ� ���� Ÿ�ٿ��� Wic��Ʈ�ʿ��� ������ d2d�� ��Ʈ���� �����ϴ� ���� �Լ� ���
	//pBitmapRT->CreateBitmapFromWicBitmap(pWicFormatConverter, NULL, &pD2DBitmap);
}