#pragma once
#include "gameNode.h"
class EndingScene :	public gameNode
{
private:
	int _alpha;
	bool _dark;

public:
	EndingScene() {};
	~EndingScene() {};

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

