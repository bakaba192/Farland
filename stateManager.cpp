#include "stdafx.h"
#include "stateManager.h"



HRESULT stateManager::init(void)
{
	_state = B_NONE;
	_myTurn = true;

	_myTurnStart = true;	//이 값이 트루이면 모든 플레이어의 이동및 액션 상태를 true로 초기화한다.
	_enemyTurnStart = false; //이 값이 트루이면 모든 플레이어의 이동및 액션 상태를 true로 초기화한다.

	return S_OK;
}

void stateManager::release(void)
{
}

