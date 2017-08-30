#pragma once
#include "gameNode.h"
class mainScene : public gameNode
{
private:
	int _alpha;

	bool _isSceneChange;

	image* _black;

	image* _town;

	RECT _stage[4];

	RECT _mouse;

	string _nextScene;

public:
	mainScene() {};
	~mainScene() {};

	HRESULT init();
	void release(void);
	void update(void);
	void render(void);
};