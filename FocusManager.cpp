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
	//현재 포커스의 위치 FOCUSX, FOCUSY, 단위시간당 이동할 포커스의 거리 FOCUSOFFSETX, Y, 찍은 원점 focus origin x, y, 그리고 마우스 포인터의 위치x y
	if (_isMoveFocus == true)
	{
		//단위 시간단 마우스포인터가 이동한 값을 포커스에서 빼주면 된다.
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
