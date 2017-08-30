// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

//=================================================================================================
//	##	������ ��� ����	##
//=================================================================================================

#include <SDKDDKVer.h>

//C4996 ��� ���ֱ� - sprintf��� ���ؼ�(�� �� �ϳ� ���)
#define _CRT_SECURE_NO_DEPRECATE
//#pragma warning(disable:4996)

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

//������ (�ּ�ġ�� �ܼ�â�� �������)
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
//#include <string.h>


// C++ ��Ÿ�� ��� �����Դϴ�.
#include <iostream>
#include <math.h>
#include <string>
#include<fstream>

//���ֻ���ϴ� STL
#include <string>
#include <vector>
#include <map>

using namespace std;

//=================================================================================================
//	##	�׷��� ��� ���� 	##
//=================================================================================================

//�׷���GDI+ ����ϱ� ���� ��
#include <ole2.h>			//�ʼ� GDI+ ���õ� �ͺ��� ���ʿ�!!!!
#include <GdiPlus.h>
#pragma comment(lib, "gdiplus")
using namespace Gdiplus;

//��Ƽ����Ʈ ���ڿ� �����ڵ� ���� ��ȣ ��ȯ�� ���� ��� ���� ���� - �׷��� ��� ����
#include <atlconv.h>
//USES_CONVERSION;
//WCHAR* w = A2W("dd")


//D2D�� ����ϱ� ���� ��
#include <d2d1.h>			//���̷�Ʈ2d�� ����ϱ� ���� ���
#include <d2d1helper.h>		//C++ ���� ������ �Լ���, Ŭ������ �׸��� ����ü���� ���ǵǾ� �ֽ��ϴ�.
#include <d2dbasetypes.h>	//��, �� �Ǵ� �簢���� ���� �⺻���� �׸��⿡ ���� ������ ���ǵǾ� �ֽ��ϴ�.
#include <D2DErr.h>			//  Direct2D API���� ����ϴ� �����ڵ忡 ���Ͽ� ���ǵǾ� �ֽ��ϴ�.

//d2d ���̺귯�� �߰�
#pragma comment(lib, "D2D1.lib")

//Direct2D ���丮�� �����Ѵ�.
//���丮���� ����Ÿ���� �����Ѵ�.
//����Ÿ�ٿ��� ���ҽ����� �����Ѵ�.
//���� �Ǿ��� ���ҽ����� �̿��ؼ� �׸��� �۾��� �����Ѵ�.


//WIC(Windows Imaging Component)
//WIC�� ��� �̹����� ���� ó���� �� �ֵ��� ���� COM ����� �����ӿ�ũ!!
#include <wincodec.h>
#pragma comment(lib, "WindowsCodecs.lib")
using namespace D2D1;


//=================================================================================================
//	##	���� ��� ����	##
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
//	##	�̱���	##
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
//	##	������â �ʱ�ȭ	��ó����	##
//=================================================================================================

#define WINNAME				(LPTSTR)(TEXT("�ķ��� ��ƽ��"))

//Ǯ��ũ�� ȭ���� ����Ϸ��� �ּ� ����
//#define FULLSCREEN

#ifdef FULLSCREEN
	#define WINSTARTX		0
	#define WINSTARTY		0
	#define WINSIZEX			GetSystemMetrics(SM_CXSCREEN)
	#define WINSIZEY			GetSystemMetrics(SM_CYSCREEN)
	#define WINSTYLE			WS_POPUPWINDOW | WS_MAXIMIZE
							//������ȿ��� �ػ󵵺���?
#else
	#define WINSTARTX		100
	#define WINSTARTY		100
	#define WINSIZEX			640
	#define WINSIZEY			480
	#define WINSTYLE			WS_CAPTION | WS_SYSMENU
#endif



//=================================================================================================
//	##	��ũ�� �Լ�	##	(Ŭ���� ������ �����Ҵ� ����)
//=================================================================================================

#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}


//=================================================================================================
//	##	��������	##
//=================================================================================================

//extern ->	�������� ����
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;		//���콺 ��ǥ��
extern ULONG_PTR	gdiplusToken;	//�׷��ȿ�
extern BOOL			_doubleClick;	//����Ŭ����

//=================================================================================================
//	##	��Ÿ �߰��� ��??	##
//=================================================================================================