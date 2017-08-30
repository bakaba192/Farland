#include "stdafx.h"
#include "d2dManager.h"


//=================================================================================================
//	##	d2d �Ŵ��� �Լ� [ d2dManager ] (Ŭ����)	##
//=================================================================================================

HRESULT d2dManager::init(void)
{
	return S_OK;
}
void d2dManager::release(void)
{
	//this->deleteAll();
}


//=================================================================================================
//	## [ �̹��� �ʱ�ȭ ] ##
//=================================================================================================

d2dImage* d2dManager::addImage(string strKey, const WCHAR* fileName)
{
	d2dImage* d2dImg = findImage(strKey);

	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (d2dImg) return d2dImg;

	//������ �̹��� ���� ����
	d2dImg = new d2dImage;
	if (FAILED(d2dImg->init(fileName)))
	{
		SAFE_DELETE(d2dImg);
		return NULL;
	}

	/*STL �ʿ� ����*/
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mD2DImgList.insert(make_pair(strKey, d2dImg));


	return d2dImg;
}

d2dImage * d2dManager::addFrameImage(string strKey, const WCHAR * fileName, int maxFrameX, int maxFrameY)
{
	d2dImage* d2dImg = findImage(strKey);

	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (d2dImg) return d2dImg;

	//������ �̹��� ���� ����
	d2dImg = new d2dImage;
	if (FAILED(d2dImg->frameInit(fileName, maxFrameX, maxFrameY)))
	{
		SAFE_DELETE(d2dImg);
		return NULL;
	}

	/*STL �ʿ� ����*/
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mD2DImgList.insert(make_pair(strKey, d2dImg));


	return d2dImg;
}




// !! [ Ű�� ã�� �� ���� ] !! =================================================================================================

//�̹��� Ű������ ã��
d2dImage* d2dManager::findImage(string strKey)
{
	//�ش�Ű �˻�
	mapD2DImgIter key = _mD2DImgList.find(strKey);

	//�˻��� Ű�� ã��
	if (key != _mD2DImgList.end())
	{
		//�� ��ȯ
		return key->second;
	}

	//�˻��� Ű�� �̹����� ��ã�Ҵٸ� NULL
	return NULL;
}

//�̹��� Ű������ ����
BOOL d2dManager::deleteImage(string strKey)
{
	//�ش�Ű �˻�
	mapD2DImgIter key = _mD2DImgList.find(strKey);

	//�˻��� Ű�� ã�Ҵٸ�
	if (key != _mD2DImgList.end())
	{
		//�̹��� ����
		key->second->release();
		//�޸� ����
		SAFE_DELETE(key->second);
		//���� �ݺ��� ����
		_mD2DImgList.erase(key);

		return TRUE;
	}

	return FALSE;
}


//=================================================================================================
//	## [ �Ϲ� ���� ] ##
//=================================================================================================

void d2dManager::render(string strKey, HDC hdc, float alpha)
{
	//�̹����� ã�Ƽ� ����
	d2dImage* d2dImg = findImage(strKey);
	if (d2dImg) d2dImg->render(hdc, alpha);
}

void d2dManager::render(string strKey, HDC hdc, float destX, float destY, float alpha)
{
	//�̹����� ã�Ƽ� ����
	d2dImage* d2dImg = findImage(strKey);
	if (d2dImg) d2dImg->render(hdc, alpha);
}

//=================================================================================================
//	## [ ȸ�� ���� ] ##
//=================================================================================================

void d2dManager::rotationRender(string strKey, HDC hdc, float destX, float destY, float angle, ROTATION_CP RCP, float alpha)
{
	//�̹����� ã�Ƽ� ����
	d2dImage* d2dImg = findImage(strKey);
	if (d2dImg) d2dImg->rotationRender(hdc, destX, destY, angle, RCP, alpha);
}

void d2dManager::rotationRender(string strKey, HDC hdc, float destX, float destY, float rotationX, float rotationY, float angle, ROTATION_CP RCP, float alpha)
{
	//�̹����� ã�Ƽ� ����
	d2dImage* d2dImg = findImage(strKey);
	if (d2dImg) d2dImg->rotationRender(hdc, destX, destY, angle, rotationX, rotationY, RCP, alpha);
}

////=================================================================================================
////	## [ ������ ���� ] ##
////=================================================================================================

void d2dManager::frameRender(string strKey, HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float alpha)
{
	//�̹����� ã�Ƽ� ����
	d2dImage* d2dImg = findImage(strKey);
	if (d2dImg) d2dImg->frameRender(hdc, destX, destY, currentFrameX, currentFrameY, alpha);
}

void d2dManager::rFrameRender(string strKey, HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float angle, ROTATION_CP RCP, float alpha)
{
	//�̹����� ã�Ƽ� ����
	d2dImage* d2dImg = findImage(strKey);
	if (d2dImg) d2dImg->rFrameRender(hdc, destX, destY, currentFrameX, currentFrameY, angle, RCP, alpha);
}

void d2dManager::rFrameRender(string strKey, HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float rotationX, float rotationY, float angle, ROTATION_CP RCP, float alpha)
{
	//�̹����� ã�Ƽ� ����
	d2dImage* d2dImg = findImage(strKey);
	if (d2dImg) d2dImg->rFrameRender(hdc, destX, destY, currentFrameX, currentFrameY, rotationX, rotationY, angle, RCP, alpha);
}


////=================================================================================================
////	## [ Ư�� ] ##
////=================================================================================================

void d2dManager::xFrameRender(string strKey, HDC hdc, float destX, float destY, float lengthY, int currentFrameX, float angle, TELESCOPIC_DIRECTION TD, ROTATION_CP RCP, float rotationX, float rotationY, float alpha)
{
	//�̹����� ã�Ƽ� ����
	d2dImage* d2dImg = findImage(strKey);
	if (d2dImg) d2dImg->xFrameRender(hdc, destX, destY, lengthY, currentFrameX, angle, TD ,RCP, rotationX, rotationY, alpha);
}
