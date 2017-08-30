#include "stdafx.h"
#include "soundManager.h"

HRESULT soundManager::init(void)
{
	//사운드 시스템을 생성한다
	System_Create(&_system);

	//사운드 채널수 설정
	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//사운드, 채널 클래스 동적할당
	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	//메모리 초기화
	memset(_sound, 0, sizeof(Sound*) * TOTALSOUNDBUFFER);
	memset(_channel, 0, sizeof(Channel*) * TOTALSOUNDBUFFER);


	return S_OK;
}

void soundManager::release(void)
{
	//사운드 및 채널 삭제
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

	//메모리 지우기
	SAFE_DELETE(_sound);
	SAFE_DELETE(_channel);
	
	//시스템 닫기
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}
}

void soundManager::update(void)
{
	//메인게임에서 사운드 매니져를 업데이트 해줘야 함
	//사운드 시스템은 볼륨을 변경하거나, 재생이 끝난후 사운드를 변경하거나등등
	//사운드 관련 총괄담당을 한다
	_system->update();
}

void soundManager::render(void)
{
}

void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (loop)//bgm, 효과음
	{
		if (bgm)//bgm루프냐?
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
		else//효과음루프냐
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
	}
	else//효과음
	{
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
	}

	//맵에 사운드를 키값과 함께 담아준다
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

//플레이
void soundManager::play(string keyName, float volume)
{
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 플레이
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);
			//볼륨세팅
			_channel[count]->setVolume(volume);
		}
	}
}

//정지
void soundManager::stop(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 정지
			_channel[count]->stop();
			break;
		}
	}
}

//일시 정지
void soundManager::pause(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 정지
			_channel[count]->setPaused(true);
			break;
		}
	}
}

//다시 재생
void soundManager::resume(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 정지
			_channel[count]->setPaused(false);
			break;
		}
	}
}

//플레이 중이냐?
bool soundManager::isPlaySound(string keyName)
{
	bool isPlay;
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 플레이중이냐?
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

//플레이 정지 중이냐?
bool soundManager::isPauseSound(string keyName)
{
	bool isPause;
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 플레이중이냐?
			_channel[count]->isPlaying(&isPause);
			break;
		}
	}

	return isPause;
}
