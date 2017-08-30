#include "stdafx.h"
#include "soundManager.h"

HRESULT soundManager::init(void)
{
	//���� �ý����� �����Ѵ�
	System_Create(&_system);

	//���� ä�μ� ����
	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//����, ä�� Ŭ���� �����Ҵ�
	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	//�޸� �ʱ�ȭ
	memset(_sound, 0, sizeof(Sound*) * TOTALSOUNDBUFFER);
	memset(_channel, 0, sizeof(Channel*) * TOTALSOUNDBUFFER);


	return S_OK;
}

void soundManager::release(void)
{
	//���� �� ä�� ����
	if (_channel != NULL || _sound != NULL)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (_channel != NULL)
			{
				if (_channel[i]) _channel[i]->stop();
			}
			if (_sound != NULL)
			{
				if (_sound[i]) _sound[i]->release();
			}
		}
	}

	//�޸� �����
	SAFE_DELETE(_sound);
	SAFE_DELETE(_channel);
	
	//�ý��� �ݱ�
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}
}

void soundManager::update(void)
{
	//���ΰ��ӿ��� ���� �Ŵ����� ������Ʈ ����� ��
	//���� �ý����� ������ �����ϰų�, ����� ������ ���带 �����ϰų����
	//���� ���� �Ѱ������ �Ѵ�
	_system->update();
}

void soundManager::render(void)
{
}

void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (loop)//bgm, ȿ����
	{
		if (bgm)//bgm������?
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
		else//ȿ����������
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
	}
	else//ȿ����
	{
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
	}

	//�ʿ� ���带 Ű���� �Բ� ����ش�
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

//�÷���
void soundManager::play(string keyName, float volume)
{
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �÷���
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);
			//��������
			_channel[count]->setVolume(volume);
		}
	}
}

//����
void soundManager::stop(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� ����
			_channel[count]->stop();
			break;
		}
	}
}

//�Ͻ� ����
void soundManager::pause(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� ����
			_channel[count]->setPaused(true);
			break;
		}
	}
}

//�ٽ� ���
void soundManager::resume(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� ����
			_channel[count]->setPaused(false);
			break;
		}
	}
}

//�÷��� ���̳�?
bool soundManager::isPlaySound(string keyName)
{
	bool isPlay;
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �÷������̳�?
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

//�÷��� ���� ���̳�?
bool soundManager::isPauseSound(string keyName)
{
	bool isPause;
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �÷������̳�?
			_channel[count]->isPlaying(&isPause);
			break;
		}
	}

	return isPause;
}
