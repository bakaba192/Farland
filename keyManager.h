#pragma once
#include "singletonBase.h"
//=================================================================================================
//	##	키 매니저 [ keyManager ] (헤드)	##
//=================================================================================================

//키 최대숫자?
#define KEYMAX 256

class keyManager : public singletonBase<keyManager>
{
private:
	//키 변수
	BOOL _keyUp[KEYMAX];
	BOOL _keyDown[KEYMAX];
public:
	//키 매니저 초기화
	HRESULT init();

	//키 한번만 누름
	bool isOnceKeyDown(int key);
	//키 한번 눌렀다 띄움
	bool isOnceKeyUp(int key);
	//키 계속 누름
	bool isStayKeyDown(int key);
	//토글키
	bool isToggleKey(int key);

	//더블클릭
	bool doubleClick();

	keyManager() {}
	~keyManager() {}
};

