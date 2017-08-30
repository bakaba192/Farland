#pragma once
#include "singletonBase.h"

//=================================================================================================
//	##	Ÿ�� �Ŵ��� [ timeManager ] (���)	##
//=================================================================================================


class timeManager : public singletonBase <timeManager>
{
private:
	bool _isHardware;				//���� Ÿ�̸Ӹ� �����ϳ�?
	float _timeScale;				//�ð� �����
	float _timeElapsed;				//�������Ӵ� ����ð�
	__int64 _curTime;				//����ð�
	__int64 _lastTime;				//�������ð�
	__int64 _periodFrequency;		//�ð��ֱ� (1�ʿ� ����̳� ī��Ʈ�� �Ǵ���)

	unsigned long _frameRate;		//FPS
	unsigned long _FPSFrameCount;	//FPS ī��Ʈ
	float _FPSTimeElapsed;			//FPS �������ð��� ����ð� �����
	float _worldTime;				//��ü ����ð�


public:
	HRESULT init(void);
	void release(void);
	void update(float lockFPS);
	void render(HDC hdc);

	//�������Ӵ� ����ð� ��������
	float getElapsedTime(void) { return _timeElapsed; }

	//��ü ����ð� ��������
	float getWorldTime(void) { return _worldTime; }

	timeManager() {}
	~timeManager() {}
};

