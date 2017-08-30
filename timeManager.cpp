#include "stdafx.h"
#include "timeManager.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
//timeGetTime�Լ��� ����ϱ� ���� ���̺귯�� �߰�
//�����찡 ���۵ǰ� �� �� �ð��� ���Ͻ����ش�
//GetTickCount���� ������ �ɿ���~~ �� ����

//=================================================================================================
//	##	Ÿ�� �Ŵ��� [ timeManager ] (Ŭ����)	##
//=================================================================================================

HRESULT timeManager::init(void)
{
	//���� Ÿ�̸� �������� üũ
	//���� Ÿ�̸Ӹ� �����ϸ� �ʴ� ����ũ�μ�������� ī��Ʈ�� �Ѵ�
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		//���� Ÿ�̸Ӹ� �����ϴϱ� �ϵ���� true
		_isHardware = true;

		//�ʴ� �ð� ��� ���� (1ī��Ʈ�� �ʰ� �󸶳� �ǳ�?)
		_timeScale = 1.0f / _periodFrequency;

		//�ʱ�ȭ ������ �ð��� ������ �ð�����
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);
	}
	else
	{
		//���� Ÿ�̸Ӹ� �������� �����ϱ� �ϵ���� false
		_isHardware = false;
		_timeScale = 1.0f / 1000.0f;
		_lastTime = timeGetTime();
	}

	//������ �ʱ�ȭ
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
		//����ð� ��´�
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else
	{
		//���� Ÿ�̸Ӹ� �������� �ʱ⶧���� �׳� time�Լ� ����Ѵ�
		_curTime = timeGetTime();
	}

	//�������� ������ ���� �ʽð� ���
	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	//�����Ӷ��� �����Ѵٸ� �����ӽ�Ű���� �Ѵ�
	if (lockFPS > 0.0f)
	{
		while (_timeElapsed < (1.0f / lockFPS))
		{
			if (_isHardware)
			{
				//����ð� ��´�
				QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			}
			else
			{
				//���� Ÿ�̸Ӹ� �������� �ʱ⶧���� �׳� time�Լ� ����Ѵ�
				_curTime = timeGetTime();
			}

			//�������� ������ ���� �ʽð� ���
			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	//���� �ð� ����
	_lastTime = _curTime;

	//������ �� ����
	_FPSTimeElapsed += _timeElapsed;

	//������ �ð� ����
	_worldTime += _timeElapsed;

	//������ �ʱ�ȭ�� 1�ʸ��� �����ϱ�
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

	//���ڹ����
	SetBkMode(hdc, TRANSPARENT);
	//���ڻ���
	SetTextColor(hdc, RGB(255, 0, 0));

	//FPS
	wsprintf(str, "FPS : %d", _frameRate);
	TextOut(hdc, 0, 0, str, strlen(str));
	//��ü�ð�
	sprintf_s(str, "WorldTime : %f", _worldTime);
	TextOut(hdc, 0, 20, str, strlen(str));
	//�������Ӵ� ����ð�
	sprintf_s(str, "ElapsedTime : %f", _timeElapsed);
	TextOut(hdc, 0, 40, str, strlen(str));
	//��Ŀ�� X ,Y
	sprintf_s(str, "Focus : %d, %d", FOCUSMANAGER->getFocusX(), FOCUSMANAGER->getFocusY());
	TextOut(hdc, 0, 60, str, strlen(str));


}
