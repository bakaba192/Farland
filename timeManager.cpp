#include "stdafx.h"
#include "timeManager.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
//timeGetTime함수를 사용하기 위해 라이브러리 추가
//윈도우가 시작되고 난 후 시간을 리턴시켜준다
//GetTickCount보다 성능이 쪼오끔~~ 더 좋다

//=================================================================================================
//	##	타임 매니저 [ timeManager ] (클래스)	##
//=================================================================================================

HRESULT timeManager::init(void)
{
	//고성능 타이머 지원여부 체크
	//고성능 타이머를 지원하면 초당 마이크로세컨드까지 카운트를 한다
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		//고성능 타이머를 지원하니까 하드웨어 true
		_isHardware = true;

		//초당 시간 계산 범위 (1카운트당 초가 얼마나 되냐?)
		_timeScale = 1.0f / _periodFrequency;

		//초기화 시점의 시간을 마지막 시간으로
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);
	}
	else
	{
		//고성능 타이머를 지원하지 않으니까 하드웨어 false
		_isHardware = false;
		_timeScale = 1.0f / 1000.0f;
		_lastTime = timeGetTime();
	}

	//변수들 초기화
	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0.0f;
	_worldTime = 0;

	return S_OK;
}

void timeManager::release(void)
{
}

void timeManager::update(float lockFPS)
{
	if (_isHardware)
	{
		//현재시간 얻는다
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else
	{
		//고성능 타이머를 지원하지 않기때문에 그냥 time함수 사용한다
		_curTime = timeGetTime();
	}

	//한프레임 간격의 지난 초시간 계산
	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	//프레임락이 존재한다면 프레임스키핑을 한다
	if (lockFPS > 0.0f)
	{
		while (_timeElapsed < (1.0f / lockFPS))
		{
			if (_isHardware)
			{
				//현재시간 얻는다
				QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			}
			else
			{
				//고성능 타이머를 지원하지 않기때문에 그냥 time함수 사용한다
				_curTime = timeGetTime();
			}

			//한프레임 간격의 지난 초시간 계산
			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	//지난 시간 갱신
	_lastTime = _curTime;

	//프레임 초 누적
	_FPSTimeElapsed += _timeElapsed;

	//총지난 시간 누적
	_worldTime += _timeElapsed;

	//프레임 초기화를 1초마다 진행하기
	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPSTimeElapsed = 0.0f;
	}
	_FPSFrameCount++;
}

void timeManager::render(HDC hdc)
{
	char str[256];

	//글자배경모드
	SetBkMode(hdc, TRANSPARENT);
	//글자색상
	SetTextColor(hdc, RGB(255, 0, 0));

	//FPS
	wsprintf(str, "FPS : %d", _frameRate);
	TextOut(hdc, 0, 0, str, strlen(str));
	//전체시간
	sprintf_s(str, "WorldTime : %f", _worldTime);
	TextOut(hdc, 0, 20, str, strlen(str));
	//한프레임당 경과시간
	sprintf_s(str, "ElapsedTime : %f", _timeElapsed);
	TextOut(hdc, 0, 40, str, strlen(str));
	//포커스 X ,Y
	sprintf_s(str, "Focus : %d, %d", FOCUSMANAGER->getFocusX(), FOCUSMANAGER->getFocusY());
	TextOut(hdc, 0, 60, str, strlen(str));


}
