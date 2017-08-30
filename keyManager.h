#pragma once
#include "singletonBase.h"
//=================================================================================================
//	##	Ű �Ŵ��� [ keyManager ] (���)	##
//=================================================================================================

//Ű �ִ����?
#define KEYMAX 256

class keyManager : public singletonBase<keyManager>
{
private:
	//Ű ����
	BOOL _keyUp[KEYMAX];
	BOOL _keyDown[KEYMAX];
public:
	//Ű �Ŵ��� �ʱ�ȭ
	HRESULT init();

	//Ű �ѹ��� ����
	bool isOnceKeyDown(int key);
	//Ű �ѹ� ������ ���
	bool isOnceKeyUp(int key);
	//Ű ��� ����
	bool isStayKeyDown(int key);
	//���Ű
	bool isToggleKey(int key);

	//����Ŭ��
	bool doubleClick();

	keyManager() {}
	~keyManager() {}
};

