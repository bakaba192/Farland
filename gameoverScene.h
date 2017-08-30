#pragma once
#include "gameNode.h"
class gameoverScene : public gameNode
{
private:
	image* img;

	image* gameover;

	int _alpha, _Count;

	bool _brighttening , _dark, _changeScene;
	
public:
	gameoverScene() {};
	~gameoverScene() {};


	//ÇÊ¼ö
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

