#include "stdafx.h"
#include "stateManager.h"



HRESULT stateManager::init(void)
{
	_state = B_NONE;
	_myTurn = true;

	_myTurnStart = true;	//�� ���� Ʈ���̸� ��� �÷��̾��� �̵��� �׼� ���¸� true�� �ʱ�ȭ�Ѵ�.
	_enemyTurnStart = false; //�� ���� Ʈ���̸� ��� �÷��̾��� �̵��� �׼� ���¸� true�� �ʱ�ȭ�Ѵ�.

	return S_OK;
}

void stateManager::release(void)
{
}

