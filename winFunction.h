#pragma once
#include "stdafx.h"
#include "gameNode.h"

//=================================================================================================
//	##	윈도우창 관련 함수 [ winFunction ]	##
//=================================================================================================

//윈도우창 크기 조정
inline void setWinResize(int width, int height)
{
	RECT prc;
	//윈도우 현재좌표
	GetWindowRect(_hWnd, &prc);

	RECT rc = { 0, 0, width, height };
	//실제 윈도우 크기 조정
	AdjustWindowRect(&rc, WINSTYLE, FALSE);
	
	//윈사이즈 재세팅
	MoveWindow(_hWnd, prc.left, prc.top, rc.right - rc.left, rc.bottom - rc.top, TRUE);
}
//윈도우창 위치 조정
inline void setWinMove(int startX, int startY)
{
	RECT rc = { 0,0,0,0 };
	GetClientRect(_hWnd, &rc);
	//실제 윈도우 크기 조정
	AdjustWindowRect(&rc, WINSTYLE, FALSE);
	//윈사이즈 재세팅
	MoveWindow(_hWnd, startX, startY, rc.right - rc.left, rc.bottom - rc.top, TRUE);
}
//윈도우창 위치, 크기 조정
inline void setWinMoveAndSize(int startX, int startY, int width, int height)
{
	RECT rc = { 0, 0, width, height };
	//실제 윈도우 크기 조정
	AdjustWindowRect(&rc, WINSTYLE, FALSE);
	//윈사이즈 재세팅
	MoveWindow(_hWnd, startX, startY, rc.right - rc.left, rc.bottom - rc.top, TRUE);
}

//윈도우 사이즈 크기 가져오기
inline int getWinSizeX(void)
{
	//-GetWindowRect(HWND hWnd, LPRECT lpRect), : 윈도우의 위치와 좌표를 구하는 함수
	//- GetClientRect(HWND hWnd, LPRECT lpRect) : 작업영역의 크기를 구하는 함

	RECT rc = { 0,0,0,0 };
	GetClientRect(_hWnd, &rc);

	return rc.right;
}

inline int getWinSizeY(void)
{
	//-GetWindowRect(HWND hWnd, LPRECT lpRect), : 윈도우의 위치와 좌표를 구하는 함수
	//- GetClientRect(HWND hWnd, LPRECT lpRect) : 작업영역의 크기를 구하는 함

	RECT rc = { 0,0,0,0 };
	GetClientRect(_hWnd, &rc);

	return rc.bottom;
}