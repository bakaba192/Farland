// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

//=================================================================================================
//	##	윈도우 헤드 파일	##
//=================================================================================================

#include <SDKDDKVer.h>

//C4996 경고 없애기 - sprintf사용 위해서(둘 중 하나 사용)
#define _CRT_SECURE_NO_DEPRECATE
//#pragma warning(disable:4996)

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

//디버깅용 (주석치면 콘솔창이 사라진다)
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
//#include <string.h>


// C++ 런타임 헤더 파일입니다.
#include <iostream>
#include <math.h>
#include <string>
#include<fstream>

//자주사용하는 STL
#include <string>
#include <vector>
#include <map>

using namespace std;

//=================================================================================================
//	##	그래픽 헤더 파일 	##
//=================================================================================================

//그래픽GDI+ 사용하기 위한 것
#include <ole2.h>			//필수 GDI+ 관련된 것보다 위쪽에!!!!
#include <GdiPlus.h>
#pragma comment(lib, "gdiplus")
using namespace Gdiplus;

//멀티바이트 문자와 유니코드 문자 상호 변환를 위한 헤더 파일 선언 - 그래픽 경로 문제
#include <atlconv.h>
//USES_CONVERSION;
//WCHAR* w = A2W("dd")


//D2D를 사용하기 위한 것
#include <d2d1.h>			//다이렉트2d를 사용하기 위한 헤더
#include <d2d1helper.h>		//C++ 에서 유용한 함수들, 클래스들 그리고 구조체들이 정의되어 있습니다.
#include <d2dbasetypes.h>	//점, 선 또는 사각형과 같은 기본적인 그리기에 대한 정보가 정의되어 있습니다.
#include <D2DErr.h>			//  Direct2D API에서 사용하는 에러코드에 대하여 정의되어 있습니다.

//d2d 라이브러리 추가
#pragma comment(lib, "D2D1.lib")

//Direct2D 팩토리를 생성한다.
//팩토리에서 렌더타겟을 생성한다.
//렌더타겟에서 리소스들을 생성한다.
//생성 되어진 리소스들을 이용해서 그리기 작업을 수행한다.


//WIC(Windows Imaging Component)
//WIC는 모든 이미지를 쉽게 처리할 수 있도록 만들어낸 COM 기반의 프레임워크!!
#include <wincodec.h>
#pragma comment(lib, "WindowsCodecs.lib")
using namespace D2D1;


//=================================================================================================
//	##	개인 헤드 파일	##
//=================================================================================================

#include "commonMacroFunction.h"
#include "keyManager.h"
#include "randomFunction.h"
#include "TrigonometricFunction.h"
#include "imageManager.h"
#include "gdiPlusManager.h"
#include "sceneManager.h"
#include "timeManager.h"
#include "iniData.h"
#include "soundManager.h"
#include "d2dManager.h"
#include "FocusManager.h"
#include "stateManager.h"
#include "F_MAPDATA.h"
#include "dataBase.h"
#include "uiManager.h"
#include "CharacterData.h"
#include "EndingManager.h"


//=================================================================================================
//	##	싱글톤	##
//=================================================================================================

#define KEYMANAGER			keyManager::getSingleton()
#define RND					randomFunction::getSingleton()
#define IMAGEMANAGER			imageManager::getSingleton()
#define GDI					gdiPlusManager::getSingleton()
#define SCENEMANAGER			sceneManager::getSingleton()
#define TIMEMANAGER			timeManager::getSingleton()
#define INIDATA				iniData::getSingleton()
#define SOUNDMANAGER			soundManager::getSingleton()
#define D2D					d2dManager::getSingleton()
#define FOCUSMANAGER			FocusManager::getSingleton()
#define STATEMANAGER	stateManager::getSingleton()
#define MAPDATA			F_MAPDATA::getSingleton()
#define DATABASE		dataBase::getSingleton()
#define UIMANAGER		uiManager::getSingleton()
#define CHARADATA		CharacterData::getSingleton()
#define ENDINGMANAGER	EndingManager::getSingleton()

//=================================================================================================
//	##	윈도우창 초기화	전처리기	##
//=================================================================================================

#define WINNAME				(LPTSTR)(TEXT("파랜드 택틱스"))

//풀스크린 화면을 사용하려면 주석 해제
//#define FULLSCREEN

#ifdef FULLSCREEN
	#define WINSTARTX		0
	#define WINSTARTY		0
	#define WINSIZEX			GetSystemMetrics(SM_CXSCREEN)
	#define WINSIZEY			GetSystemMetrics(SM_CYSCREEN)
	#define WINSTYLE			WS_POPUPWINDOW | WS_MAXIMIZE
							//윈도우안에서 해상도변경?
#else
	#define WINSTARTX		100
	#define WINSTARTY		100
	#define WINSIZEX			640
	#define WINSIZEY			480
	#define WINSTYLE			WS_CAPTION | WS_SYSMENU
#endif



//=================================================================================================
//	##	매크로 함수	##	(클래스 생성시 동적할당 제거)
//=================================================================================================

#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}


//=================================================================================================
//	##	전역변수	##
//=================================================================================================

//extern ->	전역변수 선언
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;		//마우스 좌표용
extern ULONG_PTR	gdiplusToken;	//그래픽용
extern BOOL			_doubleClick;	//더블클릭용

//=================================================================================================
//	##	기타 추가할 것??	##
//=================================================================================================