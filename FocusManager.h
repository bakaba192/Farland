#pragma once
#include "singletonBase.h"

class FocusManager : public singletonBase<FocusManager>
{
private:
	int _FocusX;
	int _FocusY;

	int _ptOriginX;
	int _ptOriginY;

	int _FocusOffSetX;
	int _FocusOffSetY;

	bool _isMoveFocus;

	int _FocusMaxBoundX;
	int _FocusMaxBoundY;
	int _FocusMinBoundX;
	int _FocusMinBoundY;

public:
	FocusManager() {}
	~FocusManager() {}

	HRESULT init(void);
	void release(void);
/*
	inline void FocusUpdate(int *x , int *y)
	{
		*x = _FocusX;
		*y = _FocusY;
	}*/

	void FocusByMouse();

	inline void setFocus(int x, int y)
	{
		_FocusX = x;
		_FocusY = y;
	}

	inline int getFocusX()
	{
		return _FocusX;
	}

	inline int getFocusY()
	{
		return _FocusY;
	}



	inline void setBound(int MinX, int MaxX, int MinY, int MaxY)
	{
		_FocusMinBoundX = MinX;	//좌측 한계점
		_FocusMaxBoundX = MaxX;	//우측 한계점
		_FocusMinBoundY = MinY; //상단 한계점
		_FocusMaxBoundY = MaxY; //하단 한계점
	}
};