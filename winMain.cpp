//=================================================================================================
//	##	��� ����	##
//=================================================================================================

#include "stdafx.h"
#include "mainGame.h"

//=================================================================================================
//	##	��������	##
//=================================================================================================

HINSTANCE	_hInstance;
HWND		_hWnd;
POINT		_ptMouse = { 0, 0 };	//���콺 ��ǥ��

//���� Ŭ��
BOOL		_doubleClick = false;

//�׷��ȿ�
ULONG_PTR	gdiplusToken;
GdiplusStartupInput	gdiplusStartupInput;

//���ΰ��� Ŭ���� ����
mainGame* _mg;

//=================================================================================================
//	##	�Լ� ���� ����	##
//=================================================================================================

//�ݺ� ���� ����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//������ ��Ȯ�� ũ�� ���� �Լ�
void setWindowSize(int x, int y, int width, int height);	//Ŭ���̾�Ʈ ������ ����� ��Ȯ�� ����ش�


//=================================================================================================
//	##	������ ���� �Լ�	##
//=================================================================================================
int APIENTRY WinMain(HINSTANCE hIns, HINSTANCE prevI, LPSTR lpszCmdParam, int cmdShow)
{
	//���ΰ��� Ŭ���� �����Ҵ�
	_mg = new mainGame;

	//���������� ���
	_hInstance = hIns;

	//������ ����ü ���� �� �ʱ�ȭ
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hIns;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.lpszClassName = WINNAME;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;;

	//�����쿡 ���
	RegisterClass(&wc);

#ifdef FULLSCREEN
	DEVMODE dm;

	ZeroMemory(&dm, sizeof(DEVMODE));
	dm.dmSize = sizeof(DEVMODE);
	dm.dmBitsPerPel = 32;
	dm.dmPelsWidth = 960;//�� �κ��� �����ϸ� �ػ󵵰� ����ȴ�. Ǯ��ũ����. 4:3 16:9 �̷��� ������~
	dm.dmPelsHeight = 540;
	dm.dmDisplayFrequency = 60; //����� 60Hz
	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		ChangeDisplaySettings(&dm, 0);
	}

	//������ ���� ����
	_hWnd = CreateWindow(
		WINNAME, WINNAME,
		WINSTYLE,
		WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY,
		NULL, (HMENU)NULL, hIns, NULL);


	//������ ũ�⸦ ��Ȯ�� ����
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

#else


	//������ ���� ����
	_hWnd = CreateWindow(
		WINNAME, WINNAME,
		WINSTYLE,
		WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY,
		NULL, (HMENU)NULL, hIns, NULL);


	//������ ũ�⸦ ��Ȯ�� ����
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

#endif // FULLSCREEN

	//������ ���̱�
	ShowWindow(_hWnd, cmdShow);
	//GDI+ �׷��� ����
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	//���ΰ��� �ʱ�ȭ ���н� �ٷ� ����
	if (FAILED(_mg->init()))
	{
		return 0;
	}

	//�޼��� ���� ����
	MSG mes;
	//�޼��� ����
	//GetMessage : �޼����� ������ �� ���������� �����ִ� �Լ�
	//PeekMessage : �޼����� ������ ���ϵǴ� �Լ�

	while (true) //���ӿ�
	{
		if (PeekMessage(&mes, NULL, 0, 0, PM_REMOVE))
		{
			if (mes.message == WM_QUIT) break;
			TranslateMessage(&mes);
			DispatchMessage(&mes);
		}
		else
		{
			TIMEMANAGER->update(60.0f);
			_mg->update();
			_mg->render();
		}
	}



	/*
	//TranslateMessage : Ű���� �Է¸޼��� ó���� ���
	//�Էµ� Ű�� ����Ű���� Ȯ���� �빮�� Ȥ�� �ҹ���, �ѱ�, ���������� ����
	//WM_CHAR �޼��� �߻���Ų��
	//DispatchMessage : ������ ���ν������� ���޵� �޼����� ���� ������� �������ش�
	while (GetMessage(&mes, 0, 0, 0)) //�Ϲ� ���α׷��ֿ�
	{
		TranslateMessage(&mes);
		DispatchMessage(&mes);
	}
	*/

	//���ΰ��� Ŭ���� ����
	_mg->release();
	//GDI+ �׷��� ����
	GdiplusShutdown(gdiplusToken);

	//������ Ŭ���� ��� ����
	UnregisterClass(WINNAME, hIns);

	//�޽��� �Ű����� ����
	return mes.wParam;

}


//������ ���ν���: �ü���� �ż��� ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMes, WPARAM wP, LPARAM lP)
{
	return _mg->MainProc(hWnd, iMes, wP, lP);
}


//=================================================================================================
//	##	������ ũ�� ����	##	(Ŭ���̾�Ʈ ������ ����� ��Ȯ�� ����ش�)
//=================================================================================================
void setWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0, 0, width, height };

	//���� ������ ũ�� ����
	AdjustWindowRect(&rc, WINSTYLE, false);
	//(RECT����ü, ������ ��Ÿ��, �޴�����)


	//�� ��Ʈ ������ ������ Ŭ���̾�Ʈ ������ ����
	SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);

	//(�ڵ�, �ڵ麯��� ����?, ����������� x, ����������� y, ������ ����, ������ ����,  SWP_NOZORDER | SWP_NOMOVE)
	//SWP_NOZORDER : z���� �������� ����.(ȭ�� ��ĥ �� z���� ����)
	//SWP_NOMOVE : ��ġ�������� ����.
	//SWP_NOSIZE : ũ�⺯������ ����.
}