#pragma once
#include "singletonBase.h"
#include "gdipImage.h"

//=================================================================================================
//	##	GDI �̹��� �Ŵ��� [ gdiPlusManager ] (���)	##
//=================================================================================================

class gdiPlusManager :	public singletonBase<gdiPlusManager>
{
private:
	typedef map<string, gdipImage*> mapGdipImgList;				//������ ���� �̹������
	typedef map<string, gdipImage*>::iterator mapGdipImgIter;		//������ ���� �̹�������� �ݺ���

private:
	mapGdipImgList _mGdipImgList;		//���� �̹���Ŭ������ ���� ��

private:


public:
	//�ʱ�ȭ
	HRESULT init(void);
	//����
	void release(void);


	//�̹��� �ʱ�ȭ
	gdipImage * addImage(string strKey, const WCHAR * fileName, int maxFrameX, int maxFrameY);
	//�̹��� Ű������ ã��
	gdipImage * findImage(string strKey);

	BOOL deleteAll();

	//����
	void gdiFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	gdiPlusManager() {}
	~gdiPlusManager() {}
};

