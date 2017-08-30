#pragma once
#include "gameNode.h"
#include "loading.h"
class F_loadingScene :	public gameNode
{
private:
	loading* _loading;

	RECT _startButton;

	bool _sceneChange;

	int _alpha;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void loadingImage(void);

	void loadingSound(void);

	F_loadingScene() {}
	~F_loadingScene() {}
};

