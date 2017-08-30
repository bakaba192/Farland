//=================================================================================================
//	##	헤드 파일	##
//=================================================================================================

#include "stdafx.h"
#include "mainGame.h"

//=================================================================================================
//	##	전역변수	##
//=================================================================================================

HINSTANCE	_hInstance;
HWND		_hWnd;
POINT		_ptMouse = { 0, 0 };	//마우스 좌표용

//더블 클릭
BOOL		_doubleClick = false;

//그래픽용
ULONG_PTR	gdiplusToken;
GdiplusStartupInput	gdiplusStartupInput;

//메인게임 클래스 선언
mainGame* _mg;

//=================================================================================================
//	##	함수 전방 선언	##
//=================================================================================================

//콜벡 전방 선언
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//윈도우 정확한 크기 설정 함수
void setWindowSize(int x, int y, int width, int height);	//클라이언트 영역의 사이즈를 정확히 잡아준다


//=================================================================================================
//	##	윈도우 메인 함수	##
//=================================================================================================
int APIENTRY WinMain(HINSTANCE hIns, HINSTANCE prevI, LPSTR lpszCmdParam, int cmdShow)
{
	//메인게임 클래스 동적할당
	_mg = new mainGame;

	//전역변수에 담기
	_hInstance = hIns;

	//윈도우 구조체 선언 및 초기화
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

	//윈도우에 등록
	RegisterClass(&wc);

#ifdef FULLSCREEN
	DEVMODE dm;

	ZeroMemory(&dm, sizeof(DEVMODE));
	dm.dmSize = sizeof(DEVMODE);
	dm.dmBitsPerPel = 32;
	dm.dmPelsWidth = 960;//이 부분을 조절하면 해상도가 변경된다. 풀스크린시. 4:3 16:9 이런거 생각해~
	dm.dmPelsHeight = 540;
	dm.dmDisplayFrequency = 60; //재생빈도 60Hz
	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		ChangeDisplaySettings(&dm, 0);
	}

	//윈도우 생성 정보
	_hWnd = CreateWindow(
		WINNAME, WINNAME,
		WINSTYLE,
		WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY,
		NULL, (HMENU)NULL, hIns, NULL);


	//윈도우 크기를 정확히 설정
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

#else


	//윈도우 생성 정보
	_hWnd = CreateWindow(
		WINNAME, WINNAME,
		WINSTYLE,
		WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY,
		NULL, (HMENU)NULL, hIns, NULL);


	//윈도우 크기를 정확히 설정
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

#endif // FULLSCREEN

	//윈도우 보이기
	ShowWindow(_hWnd, cmdShow);
	//GDI+ 그래픽 선언
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	//메인게임 초기화 실패시 바로 종료
	if (FAILED(_mg->init()))
	{
		return 0;
	}

	//메세지 루프 시작
	MSG mes;
	//메세지 루프
	//GetMessage : 메세지를 꺼내올 수 있을때까지 멈춰있는 함수
	//PeekMessage : 메세지가 없더라도 리턴되는 함수

	while (true) //게임용
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
	//TranslateMessage : 키보드 입력메세지 처리를 담당
	//입력된 키가 문자키인지 확인후 대문자 혹은 소문자, 한글, 영문인지에 대한
	//WM_CHAR 메세지 발생시킨다
	//DispatchMessage : 윈도우 프로시져에서 전달된 메세지를 실제 윈도우로 전달해준다
	while (GetMessage(&mes, 0, 0, 0)) //일반 프로그래밍용
	{
		TranslateMessage(&mes);
		DispatchMessage(&mes);
	}
	*/

	//메인게임 클래스 해제
	_mg->release();
	//GDI+ 그래픽 해제
	GdiplusShutdown(gdiplusToken);

	//윈도우 클래스 등록 해제
	UnregisterClass(WINNAME, hIns);

	//메시지 매개변수 리턴
	return mes.wParam;

}


//윈도우 프로시저: 운영체제에 매세지 전달
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMes, WPARAM wP, LPARAM lP)
{
	return _mg->MainProc(hWnd, iMes, wP, lP);
}


//=================================================================================================
//	##	윈도우 크기 조정	##	(클라이언트 영역의 사이즈를 정확히 잡아준다)
//=================================================================================================
void setWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0, 0, width, height };

	//실제 윈도우 크기 조정
	AdjustWindowRect(&rc, WINSTYLE, false);
	//(RECT구조체, 윈도우 스타일, 메뉴여부)


	//위 렉트 정보로 윈도우 클라이언트 사이즈 세팅
	SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);

	//(핸들, 핸들변경시 설정?, 윈도우시작점 x, 윈도우시작점 y, 윈도우 가로, 윈도우 세로,  SWP_NOZORDER | SWP_NOMOVE)
	//SWP_NOZORDER : z순서 변경하지 않음.(화면 겹칠 때 z순서 무시)
	//SWP_NOMOVE : 위치변경하지 않음.
	//SWP_NOSIZE : 크기변경하지 않음.
}