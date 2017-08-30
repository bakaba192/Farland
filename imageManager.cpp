#include "stdafx.h"
#include "imageManager.h"

//=================================================================================================
//	##	�̹��� �Ŵ��� �Լ� [ imageManager ] (Ŭ����)	##
//=================================================================================================

HRESULT imageManager::init(void)
{
	return S_OK;
}

void imageManager::release(void)
{
	this->deleteAll();
}


//=================================================================================================
//	## [ �̹��� �ʱ�ȭ ] ##
//=================================================================================================


// !! [ �� ��Ʈ�� �ʱ�ȭ ] !! =================================================================================================
image * imageManager::addImage(string strKey, int width, int height)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	//������ �̹��� ���� ����
	img = new image;
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL ���� �ٽ�*/
	//Ű, �� �� ���� ������
	//ù��° first -> Ű
	//�ι�° second -> ��
	//�߰��ϴ� ����� insert�� ����ϵ� Ű�͹�� �ΰ��� ���ÿ� �߰��ؾ� �ϴ� 
	//pair, make_pair�� ����Ͽ� �߰��ϸ� �ȴ�

	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// !! [ �̹��� ���Ϸ� �ʱ�ȭ(�� ���) ] !! =================================================================================================
image * imageManager::addImage(string strKey, const CHAR * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	//������ �̹��� ���� ����
	img = new image;
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL �ʿ� ����*/
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// !! [ �̹��� ���Ϸ� �ʱ�ȭ(�ַ� ���) ] - ������������ �ʱ�ȭ ���� !! =================================================================================================
image * imageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	//������ �̹��� ���� ����
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL �ʿ� ����*/
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}


// !! [ ������ �̹��� �ʱ�ȭ(�ַ� ���) ] !! =================================================================================================
image * imageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	//������ �̹��� ���� ����
	img = new image;
	if (FAILED(img->init(fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL �ʿ� ����*/
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// !! [ ������ �̹��� �ʱ�ȭ(�ַ� ���) - ������������ �ʱ�ȭ ���� ] !! =================================================================================================
image * imageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	//������ �̹��� ���� ����
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL �ʿ� ����*/
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//������ �̹��� �ʱ�ȭ (!!Ư��!!)
image * imageManager::addScaleImage(string strKey, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	//������ �̹��� ���� ����
	img = new image;
	if (FAILED(img->scaleInit(width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL ���� �ٽ�*/

	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}



// !! [ Ű�� ã�� �� ���� ] !! =================================================================================================

//�̹��� Ű������ ã��
image * imageManager::findImage(string strKey)
{
	//�ش�Ű �˻�
	mapImageIter key = _mImageList.find(strKey);

	//�˻��� Ű�� ã��
	if (key != _mImageList.end())
	{
		//�� ��ȯ
		return key->second;
	}

	//�˻��� Ű�� �̹����� ��ã�Ҵٸ� NULL
	return NULL;
}

//�̹��� Ű������ ����
BOOL imageManager::deleteImage(string strKey)
{
	//�ش�Ű �˻�
	mapImageIter key = _mImageList.find(strKey);

	//�˻��� Ű�� ã�Ҵٸ�
	if (key != _mImageList.end())
	{
		//�̹��� ����
		key->second->release();
		//�޸� ����
		SAFE_DELETE(key->second);
		//���� �ݺ��� ����
		_mImageList.erase(key);

		return TRUE;
	}

	return FALSE;
}

//�̹��� ��ü ����
BOOL imageManager::deleteAll()
{
	//�� ��ü�� ���鼭 �����
	mapImageIter iter = _mImageList.begin();
	//for(;;)  == while(true)
	for (; iter != _mImageList.end();)
	{
		//�̹����� ������
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else //������
		{
			++iter;
		}
	}

	//�� ��ü�� ����
	_mImageList.clear();

	return TRUE;
}


//=================================================================================================
//	## [ �Ϲ� ���� ] ##
//=================================================================================================

//����(��ǥ�� �̹��� ���)
void imageManager::render(string strKey, HDC hdc)
{
	//�̹����� ã�Ƽ� ����
	image* img = findImage(strKey);
	if (img) img->render(hdc);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	//�̹����� ã�Ƽ� ����
	image* img = findImage(strKey);

	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//�̹����� ã�Ƽ� ����
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::focusRender(string strKey, HDC hdc, int destX, int destY)
{
	//�̹����� ã�Ƽ� ����
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX + FOCUSMANAGER->getFocusX(), destY + FOCUSMANAGER->getFocusY());
}



//=================================================================================================
//	## [ ���� ���� ] ##
//=================================================================================================

//���� ����
void imageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	//�̹����� ã�Ƽ� ����
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	//�̹����� ã�Ƽ� ����
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//�̹����� ã�Ƽ� ����
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

void imageManager::focusAlphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	//�̹����� ã�Ƽ� ����
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX + FOCUSMANAGER->getFocusX(), destY + FOCUSMANAGER->getFocusY(), alpha);
}


//=================================================================================================
//	## [ ������ ���� ] ##
//=================================================================================================

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	//�̹����� ã�Ƽ� ����
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//�̹����� ã�Ƽ� ����
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void imageManager::focusFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//�̹����� ã�Ƽ� ����
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX + FOCUSMANAGER->getFocusX(), destY + FOCUSMANAGER->getFocusY(), currentFrameX, currentFrameY);
}

//====================================================================
//			## �������� ##
//====================================================================
void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//�̹����� ã�Ƽ� �׳� ������Ű���
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void imageManager::focusLoopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//�̹����� ã�Ƽ� �׳� ������Ű���
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX + FOCUSMANAGER->getFocusX(), offsetY + FOCUSMANAGER->getFocusY());
}

void imageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
}



//=================================================================================================
//	## [ ������ ���� ] ##
//=================================================================================================

void imageManager::sizeRender(string strKey, HDC hdc, int sizeW, int sizeH)
{
	image* img = findImage(strKey);
	if (img) img->sizeRender(hdc, sizeW, sizeH);
}

//������ ����
void imageManager::sizeRender(string strKey, HDC hdc, int destX, int destY, int sizeW, int sizeH)
{
	image* img = findImage(strKey);
	if (img) img->sizeRender(hdc, destX, destY, sizeW, sizeH);
}


//=================================================================================================
//	## [  Ʈ���� ���� ] ##
//=================================================================================================

void imageManager::transRender(string strKey, HDC hdc, bool isTrans, COLORREF color)
{
	image* img = findImage(strKey);
	if (img) img->transRender(hdc, isTrans, color);
}

void imageManager::transRender(string strKey, HDC hdc, int destX, int destY, bool isTrans, COLORREF color)
{
	image* img = findImage(strKey);
	if (img) img->transRender(hdc, destX, destY, isTrans, color);
}


//=================================================================================================
//	## [ Ư�� ] ##
//=================================================================================================




void imageManager::setImageDC(string strKey, HDC hdc, int sizeW, int sizeH)
{
	image* img = findImage(strKey);
	if (img) img->setImageDC(hdc, sizeW, sizeH);
}

//====================================================================
//			## �����Ӿ��ķ��� ##
//====================================================================	
void imageManager::frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	image* img = findImage(strKey);
	if(img) img->frameAlphaRender(hdc, destX, destY, currentFrameX, currentFrameY, alpha);
}

void imageManager::focusFrameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->frameAlphaRender(hdc, destX + FOCUSMANAGER->getFocusX(), destY + FOCUSMANAGER->getFocusY(), currentFrameX, currentFrameY, alpha);
}
