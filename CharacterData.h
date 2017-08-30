#pragma once
#include "singletonBase.h"


//스테이지 전환에서 사용되기 위한 캐릭터들의 레벨을 저장하는 싱글톤 함수이다.
//캐릭터들이 각자 데이터를 저장하는 형식인 편인 더 효율적일 듯 하나,
//현재 상황에서 다소 변경에 어려움이 있으므로 이런 형식을 취한다.
//원래는 이곳에 장비, 스텟 등이 모두 저장되어 있을 것이다.

class CharacterData : public singletonBase<CharacterData>
{
private:
	int _alLv;
	int _karinLv;
	int _arisLv;

	int _alExp;
	int _karinExp;
	int _arisExp;

public:
	CharacterData() {};
	~CharacterData() {};
	
	HRESULT init();

	int& getAlLv() { return _alLv; }
	int& getKarinLv() { return _karinLv; }
	int& getArisLv() { return _arisLv; }

	int& getAlExp() { return _alExp; }
	int& getKarinExp() { return _karinExp; }
	int& getArisExp() { return _arisExp; }

};

