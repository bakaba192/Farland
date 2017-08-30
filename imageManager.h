#pragma once
#include "singletonBase.h"
#include "image.h"

//=================================================================================================
//	##	�̹��� �Ŵ��� �Լ� [ imageManager ] (���)	##
//=================================================================================================

class imageManager : public singletonBase<imageManager>
{
private:
	typedef map<string, image*> mapImageList;				//������ ���� �̹������
	typedef map<string, image*>::iterator mapImageIter;		//������ ���� �̹�������� �ݺ���

private:
	mapImageList _mImageList;		//���� �̹���Ŭ������ ���� ��

public:

//=================================================================================================
//	##	[ �̹��� �ʱ�ȭ ]	##
//=================================================================================================

	//�̹��� �Ŵ��� �ʱ�ȭ
	HRESULT init(void);
	//�̹��� �Ŵ��� ����
	void release(void);

	//�� ��Ʈ������ �ʱ�ȭ �� �߰�
	image* addImage(string strKey, int width, int height);

	//�̹��� ���Ϸ� �ʱ�ȭ �� �߰�(�ַ� ���)
	image* addImage(string strKey, const CHAR* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//�̹��� ���Ϸ� �ʱ�ȭ �� �߰�(�ַ� ���) - ������������ �ʱ�ȭ ����
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//������ �̹��� �ʱ�ȭ �� �߰�(�ַ� ���)
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//������ �̹��� �ʱ�ȭ �� �߰�(�ַ� ���) - ������������ �ʱ�ȭ ����
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//������ �̹��� �ʱ�ȭ (!!Ư��!!)
	image* addScaleImage(string strKey, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));


	// ## << Ű�� ã�� �� ���� >> ##
	//�̹��� Ű������ ã��
	image* findImage(string strKey);
	//�̹��� Ű������ ����
	BOOL deleteImage(string strKey);
	//�̹��� ��ü ����
	BOOL deleteAll();


//=================================================================================================
//	## [ �Ϲ� ���� ] ##
//=================================================================================================

	//����(��ǥ�� �̹��� ���)
	void render(string strKey, HDC hdc);											//��ǥ �⺻����()
	void render(string strKey, HDC hdc, int destX, int destY);						//��ǥ ���� �Է�
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);		//�߶� ���̱�

	void focusRender(string strKey, HDC hdc, int destX, int destY);						//��ǥ ���� �Է�

//=================================================================================================
//	## [ ���� ���� ] ##
//=================================================================================================

	//���� ����
	void alphaRender(string strKey, HDC hdc, BYTE alpha);							//��ǥ �⺻����()
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);	//��ǥ ���� �Է�
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);		//�߶� ���̱�
	
	void focusAlphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);	//��ǥ ���� �Է�


//=================================================================================================
//	## [ ������ ���� ] ##
//=================================================================================================

	//������ ����
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void focusFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

//====================================================================
//			## �������� ##
//====================================================================

void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
void focusLoopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

//=================================================================================================
//	## [ ������ ���� ] ##
//=================================================================================================

	//������ ����
	void sizeRender(string strKey, HDC hdc, int sizeW, int sizeH);
	void sizeRender(string strKey, HDC hdc, int destX, int destY, int sizeW, int sizeH);

//=================================================================================================
//	## [  Ʈ���� ���� ] ##
//=================================================================================================

	void transRender(string strKey, HDC hdc, bool isTrans, COLORREF color);
	void transRender(string strKey, HDC hdc, int destX, int destY, bool isTrans, COLORREF color);


//=================================================================================================
//	## [ Ư�� ] ##
//=================================================================================================

	void setImageDC(string strKey,HDC hdc, int sizeW, int sizeH);

	void frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	void focusFrameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);
	



	//������, �Ҹ���
	imageManager() {}
	~imageManager() {}
};

