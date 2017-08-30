#pragma once
#include "singletonBase.h"
#include "d2dImage.h"

//=================================================================================================
//	##	�̹��� �Ŵ��� �Լ� [ imageManager ] (���)	##
//=================================================================================================

class d2dManager : public singletonBase<d2dManager>
{
private:
	typedef map<string, d2dImage*> mapD2DImgList;				//������ ���� �̹������
	typedef map<string, d2dImage*>::iterator mapD2DImgIter;		//������ ���� �̹�������� �ݺ���

private:
	mapD2DImgList _mD2DImgList;		//���� �̹���Ŭ������ ���� ��

public:

	//=================================================================================================
	//	##	[ d2d�̹��� �ʱ�ȭ ]	##
	//=================================================================================================

	//�̹��� �Ŵ��� �ʱ�ȭ
	HRESULT init(void);
	//�̹��� �Ŵ��� ����
	void release(void);


	//d2d�̹����� �ʱ�ȭ �� �߰�
	d2dImage* addImage(string strKey, const WCHAR* fileName);
	d2dImage* addFrameImage(string strKey, const WCHAR * fileName, int maxFrameX, int maxFrameY);



	// ## << Ű�� ã�� �� ���� >> ##
	//�̹��� Ű������ ã��
	d2dImage* findImage(string strKey);
	//�̹��� Ű������ ����
	BOOL deleteImage(string strKey);
	////�̹��� ��ü ����
	//BOOL deleteAll();


	//=================================================================================================
	//	## [ �Ϲ� ���� ] ##
	//=================================================================================================

	//����(��ǥ�� �̹��� ���)
	void render(string strKey, HDC hdc, float alpha = 1.0);											//��ǥ �⺻����()
	void render(string strKey, HDC hdc, float destX, float destY, float alpha = 1.0);						//��ǥ ���� �Է�
	//void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);		//�߶� ���̱�

	//=================================================================================================
	//	## [ ȸ�� ���� ] ##
	//=================================================================================================

	void rotationRender(string strKey, HDC hdc, float destX, float destY, float angle, ROTATION_CP RCP = RCP_CENTER, float alpha = 1.0);
	void rotationRender(string strKey, HDC hdc, float destX, float destY, float rotationX, float rotationY, float angle, ROTATION_CP RCP = RCP_CENTER, float alpha = 1.0);

	////=================================================================================================
	////	## [ ������ ���� ] ##
	////=================================================================================================

	////������ ����
	//void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float alpha = 1.0);
	void rFrameRender(string strKey, HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float angle, ROTATION_CP RCP = RCP_CENTER, float alpha = 1.0);
	void rFrameRender(string strKey, HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float rotationX, float rotationY, float angle, ROTATION_CP RCP = RCP_CENTER, float alpha = 1.0);

	////====================================================================
	////			## �������� ##
	////====================================================================

	//void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	//void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	////=================================================================================================
	////	## [ ������ ���� ] ##
	////=================================================================================================

	////������ ����
	//void sizeRender(string strKey, HDC hdc, int sizeW, int sizeH);
	//void sizeRender(string strKey, HDC hdc, int destX, int destY, int sizeW, int sizeH);

	////=================================================================================================
	////	## [  Ʈ���� ���� ] ##
	////=================================================================================================

	//void transRender(string strKey, HDC hdc, bool isTrans, COLORREF color);
	//void transRender(string strKey, HDC hdc, int destX, int destY, bool isTrans, COLORREF color);


	////=================================================================================================
	////	## [ Ư�� ] ##
	////=================================================================================================

	void xFrameRender(string strKey, HDC hdc, float destX, float destY, float lengthY, int currentFrameX, float angle, TELESCOPIC_DIRECTION TD = TD_CENTER, ROTATION_CP RCP = RCP_CENTER, float rotationX = 0.0f, float rotationY = 0.0f, float alpha = 1.0);
	//void setImageDC(string strKey, HDC hdc, int sizeW, int sizeH);


	//������, �Ҹ���
	d2dManager() {}
	~d2dManager() {}
};

