#include "stdafx.h"
#include "gameNode.h"

//===== ## [ 게임 노드 클래스 ] ## =====

//=================================================================================================
//	##	초기화 init(void)	##
//=================================================================================================

HRESULT gameNode::init(void)
{
	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		//SetTimer(_hWnd, 1, 10, NULL);	//타이머 초기화(핸들, 타이머번호, 시간(초), NULL)
		KEYMANAGER->init();				//키매니저 싱글톤 초기화
		RND->init();					//랜덤함수 싱글톤 초기화
		IMAGEMANAGER->init();			//이미지매니저 싱글톤 초기화
		GDI->init();					//GDI 싱글톤 초기화
		SCENEMANAGER->init();			//씬매니저 초기화
		TIMEMANAGER->init();			//타임매니저 초기화
		INIDATA->init();				//INI데이터 초기화
		SOUNDMANAGER->init();			//사운드매니저 초기화
		D2D->init();					//D2D매니저 이미지 초기화
		FOCUSMANAGER->init();			//포커스매니저 초기화
		STATEMANAGER->init();
		MAPDATA->init();
		UIMANAGER->init();
		CHARADATA->init();
		ENDINGMANAGER->init();
	}

	return S_OK;
}


//=================================================================================================
//	##	해제 release(void)	##
//=================================================================================================

void gameNode::release(void)
{
	if (_managerInit)
	{
		//타이머 해제
		//KillTimer(_hWnd, 1);
		//키보드_매니저 싱글톤 해제
		KEYMANAGER->releaseSingleton();	
		//랜덤 함수 싱글톤 해제
		RND->releaseSingleton();
		//이미지 매니저 해제 및 싱클톤 해제
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		//GDI 이미지 매니저 해제 및 싱글톤 해제
		GDI->release();
		GDI->releaseSingleton();
		//씬매니저 해제, 싱글톤 해제
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		//타임매니저 싱글톤 해제
		TIMEMANAGER->releaseSingleton();
		//INI데이터 싱글톤 해제
		INIDATA->releaseSingleton();
		//사운드매니져 해제, 싱글톤 해제
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
		D2D->release();
		D2D->releaseSingleton();

		//포커스매니져 싱글톤 해제
		FOCUSMANAGER->releaseSingleton();

		STATEMANAGER->releaseSingleton();

		//맵데이터 싱글톤 해제
		MAPDATA->releaseSingleton();

		//데이터베이스 싱글톤 해제
		DATABASE->releaseSingleton();

		//UI매니져 싱글톤해제
		UIMANAGER->releaseSingleton();

		CHARADATA->releaseSingleton();

		ENDINGMANAGER->releaseSingleton();
	}
}

//=================================================================================================
//	##	업데이트 update(void)	##
//=================================================================================================

void gameNode::update(void)
{
	//새로고침 (나중에 고성능 타이머를 만든 후에는 사용하지 않는다)
	//더블버퍼링 이후 사용하지 않는다 (true => false)
	//나중에 테스트 하기 (true / false or 걍지우기)
	//InvalidateRect(_hWnd, NULL, FALSE);	//다시 그리기
}


//=================================================================================================
//	##	랜더 render(HDC hdc)	##
//=================================================================================================

void gameNode::render(void)
{
}



//=================================================================================================
//	##	메인 프로시저 [ mainProc() ]	##
//=================================================================================================

LRESULT gameNode::MainProc(HWND hWnd, UINT iMes, WPARAM wP, LPARAM lP)
{
	//HDC hdc;			//그리기 선언
	//PAINTSTRUCT ps;		//페인터 구조체 선언

	switch (iMes)
	{
	//case WM_TIMER:	//타이머
	//	this->update();
	//	break;
	//case WM_PAINT:	//페인터 부분
	//	hdc = BeginPaint(hWnd, &ps);
	//	this->render();
	//	EndPaint(hWnd, &ps);
	//	break;

	//마우스 좌표
	case WM_MOUSEMOVE:	
		_ptMouse.x = LOWORD(lP);
		_ptMouse.y = HIWORD(lP);
		break;
	//키보드 더블 클릭
	case WM_LBUTTONDBLCLK:
		_doubleClick = true;
		break;
	//마우스 휠
	case WM_MOUSEWHEEL:
		if ((SHORT)HIWORD(wP) > 0)
		{
			// 하고 싶은 동작 -업
		}
		
		else
		{
			// 하고 싶은 동작 - 다운
		}
	case WM_KEYDOWN:	//키보드
		switch (wP)
		{
		case VK_ESCAPE:	//ESC키 누를시 빠져나가
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);	//메시지 종료명령 전달
		break;
	}


	return (DefWindowProc(hWnd, iMes, wP, lP));
}
