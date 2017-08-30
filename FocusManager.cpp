#include "stdafx.h"
#include "FocusManager.h"

HRESULT FocusManager::init(void)
{
	_FocusX = 0;
	_FocusY = 0;

	_isMoveFocus = false;

	_FocusMinBoundX = -500;
	_FocusMinBoundY = 400;
	_FocusMaxBoundX = 500;
	_FocusMaxBoundY = -100;

	return S_OK;
}

void FocusManager::release(void)
{

}

void FocusManager::FocusByMouse()
{
	if (KEYMANAGER->isOnceKeyDown(VK_MBUTTON))
	{
		_ptOriginX = _ptMouse.x;
		_ptOriginY = _ptMouse.y;
		_isMoveFocus = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_MBUTTON))
	{
		_isMoveFocus = false;
	}
	//���� ��Ŀ���� ��ġ FOCUSX, FOCUSY, �����ð��� �̵��� ��Ŀ���� �Ÿ� FOCUSOFFSETX, Y, ���� ���� focus origin x, y, �׸��� ���콺 �������� ��ġx y
	if (_isMoveFocus == true)
	{
		//���� �ð��� ���콺�����Ͱ� �̵��� ���� ��Ŀ������ ���ָ� �ȴ�.
		_FocusOffSetX = _ptMouse.x - _ptOriginX;
		_FocusOffSetY = _ptMouse.y - _ptOriginY;

		_FocusX += _FocusOffSetX;
		if (_FocusX > _FocusMaxBoundX)
		{
			_FocusX = _FocusMaxBoundX;
		}
		else if (_FocusX < _FocusMinBoundX)
		{
			_FocusX = _FocusMinBoundX;
		}

		_FocusY += _FocusOffSetY;
		if (_FocusY < _FocusMinBoundY)
		{
			_FocusY = _FocusMinBoundY;
		}
		else if (_FocusY > _FocusMaxBoundY)
		{
			_FocusY = _FocusMaxBoundY;
		}

		_ptOriginX = _ptMouse.x;
		_ptOriginY = _ptMouse.y;
	}
}
