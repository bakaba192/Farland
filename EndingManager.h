#pragma once
#include "singletonBase.h"
class EndingManager :	public singletonBase<EndingManager>
{
private:
	bool stageClear[3];

public:
	EndingManager() {};
	~EndingManager() {};

	HRESULT init(void);

	bool* getStageClear() { return stageClear; }
};

