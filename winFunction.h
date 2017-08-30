#pragma once
#include "stdafx.h"
#include "gameNode.h"

//=================================================================================================
//	##	������â ���� �Լ� [ winFunction ]	##
//=================================================================================================

//������â ũ�� ����
inline void setWinResize(int width, int height)
{
	RECT prc;
	//������ ������ǥ
	GetWindowRect(_hWnd, &prc);

	RECT rc = { 0, 0, width, height };
	//���� ������ ũ�� ����
	AdjustWindowRect(&rc, WINSTYLE, FALSE);
	
	//�������� �缼��
	MoveWindow(_hWnd, prc.left, prc.top, rc.right - rc.left, rc.bottom - rc.top, TRUE);
}
//������â ��ġ ����
inline void setWinMove(int startX, int startY)
{
	RECT rc = { 0,0,0,0 };
	GetClientRect(_hWnd, &rc);
	//���� ������ ũ�� ����
	AdjustWindowRect(&rc, WINSTYLE, FALSE);
	//�������� �缼��
	MoveWindow(_hWnd, startX, startY, rc.right - rc.left, rc.bottom - rc.top, TRUE);
}
//������â ��ġ, ũ�� ����
inline void setWinMoveAndSize(int startX, int startY, int width, int height)
{
	RECT rc = { 0, 0, width, height };
	//���� ������ ũ�� ����
	AdjustWindowRect(&rc, WINSTYLE, FALSE);
	//�������� �缼��
	MoveWindow(_hWnd, startX, startY, rc.right - rc.left, rc.bottom - rc.top, TRUE);
}

//������ ������ ũ�� ��������
inline int getWinSizeX(void)
{
	//-GetWindowRect(HWND hWnd, LPRECT lpRect), : �������� ��ġ�� ��ǥ�� ���ϴ� �Լ�
	//- GetClientRect(HWND hWnd, LPRECT lpRect) : �۾������� ũ�⸦ ���ϴ� ��

	RECT rc = { 0,0,0,0 };
	GetClientRect(_hWnd, &rc);

	return rc.right;
}

inline int getWinSizeY(void)
{
	//-GetWindowRect(HWND hWnd, LPRECT lpRect), : �������� ��ġ�� ��ǥ�� ���ϴ� �Լ�
	//- GetClientRect(HWND hWnd, LPRECT lpRect) : �۾������� ũ�⸦ ���ϴ� ��

	RECT rc = { 0,0,0,0 };
	GetClientRect(_hWnd, &rc);

	return rc.bottom;
}