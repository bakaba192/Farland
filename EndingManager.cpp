#include "stdafx.h"
#include "EndingManager.h"

HRESULT EndingManager::init(void)
{

	stageClear[0] = false;
	stageClear[1] = false;
	stageClear[2] = false;

	return S_OK;
}
