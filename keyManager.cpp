#include "stdafx.h"
#include "keyManager.h"

//=================================================================================================
//	##	키 매니저 함수 [ keyManager ] (클래스)	##
//=================================================================================================

//키 매니저 초기화
HRESULT keyManager::init()
{
	for (int i = 0; i < KEYMAX; i++)
	{
		_keyUp[i] = false;
		_keyDown[i] = false;
	}

	return S_OK;
}

//키 한번만 누름
bool keyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!_keyDown[key])
		{
			_keyDown[key] = true;
			return true;
		}
	}
	else
	{
		_keyDown[key] = false;
	}

	return false;
}

//키 한번 눌렀다 띄움
bool keyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		_keyUp[key] = true;
	}
	else
	{
		if (_keyUp[key])
		{
			_keyUp[key] = false;
			return true;
		}
	}
	return false;
}

//키 계속 누름
bool keyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}
//토글키
bool keyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}

//더블클릭
bool keyManager::doubleClick()
{
	if (_doubleClick)
	{
		_doubleClick = false;
		return true;
	}

	return false;
}
