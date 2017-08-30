#include "stdafx.h"
#include "gdiPlusManager.h"

//=================================================================================================
//	##	GDI �̹��� �Ŵ��� [ gdiPlusManager ] (Ŭ����)	##
//=================================================================================================

HRESULT gdiPlusManager::init(void)
{
	return S_OK;
}

void gdiPlusManager::release(void)
{
	this->deleteAll();
}


//=================================================================================================
//	## [ �̹��� �ʱ�ȭ ] ##
//=================================================================================================

gdipImage * gdiPlusManager::addImage(string strKey, const WCHAR* fileName, int maxFrameX, int maxFrameY)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	gdipImage* gdiImg = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (gdiImg) return gdiImg;

	//������ �̹��� ���� ����
	gdiImg = new gdipImage;
	if (FAILED(gdiImg->init(fileName, maxFrameX, maxFrameY)))
	{
		SAFE_DELETE(gdiImg);
		return NULL;
	}

	/*STL �ʿ� ����*/
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mGdipImgList.insert(make_pair(strKey, gdiImg));

	return gdiImg;
}



// !! [ Ű�� ã�� �� ���� ] !! =================================================================================================

//�̹��� Ű������ ã��
gdipImage * gdiPlusManager::findImage(string strKey)
{
	//�ش�Ű �˻�
	mapGdipImgIter key = _mGdipImgList.find(strKey);

	//�˻��� Ű�� ã��
	if (key != _mGdipImgList.end())
	{
		//�� ��ȯ
		return key->second;
	}

	//�˻��� Ű�� �̹����� ��ã�Ҵٸ� NULL
	return NULL;
}

//����
BOOL gdiPlusManager::deleteAll()
{
	//�� ��ü�� ���鼭 �����
	mapGdipImgIter iter = _mGdipImgList.begin();
	//for(;;)  == while(true)
	for (; iter != _mGdipImgList.end();)
	{
		//�̹����� ������
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mGdipImgList.erase(iter);
		}
		else //������
		{
			++iter;
		}
	}

	//�� ��ü�� ����
	_mGdipImgList.clear();

	return TRUE;
}




//����
void gdiPlusManager::gdiFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiFrameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

