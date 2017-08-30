#pragma once
#include "singletonBase.h"
/*FMOD를 사용하기 위해 라이브러리 추가*/
#include "inc/fmod.hpp"
#pragma comment(lib, "lib/fmodex64_vc.lib")
using namespace FMOD;

//=============================================================
//	## soundManager ## (사운드 매니져)
//=============================================================

//채널, 사운드버퍼
#define EXTRACHANELBUFFER 5
//사운드 갯수만큼 설정해주기
#define SOUNDBUFFER 20
//총 사운드 버퍼설정
//#define TOTALSOUNDBUFFER (EXTRACHANELBUFFER + SOUNDBUFFER)
const int TOTALSOUNDBUFFER = EXTRACHANELBUFFER + SOUNDBUFFER;

class soundManager : public singletonBase <soundManager>
{
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundIter;

private:
	System* _system;		//시스템 클래스
	Sound** _sound;			//사운드 클래스
	Channel** _channel;		//채녈 클래스

	arrSounds _mTotalSounds;	//맵에 담아둘 사운드들

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//사운드 추가(키값, 파일이름, BGM?, 루프?)
	void addSound(string keyName, string soundName, bool bgm = FALSE, bool loop = FALSE);

	//사운드 플레이(볼륨0.0f ~ 1.0f)
	void play(string keyName, float volume = 1.0f);
	//사운드 정지
	void stop(string keyName);
	//사운드 일시정지
	void pause(string keyName);
	//사운드 다시재생
	void resume(string keyName);

	//플레이 중이냐?
	bool isPlaySound(string keyName);
	//일시정지 중이냐?
	bool isPauseSound(string keyName);

	soundManager() : _system(NULL), _sound(NULL), _channel(NULL) {}
	~soundManager() {}
};

