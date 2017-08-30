#pragma once
#include "singletonBase.h"

//=================================================================================================
//	##	씬 매니저 [ sceneManager ] (헤드)	##
//=================================================================================================

//게임노드 클래스 전방선언
class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
private:
	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

private:
	mSceneList _mSceneList;		//씬을 담아둘 맵으로 만든 목록
	gameNode* _currentScene;		//현재씬
	string _currentSceneName;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//씬 추가
	gameNode* addScene(string sceneName, gameNode* scene);
	//씬 변경
	HRESULT changeScene(string sceneName);

	string getCurrentSceneName() { return _currentSceneName; }

	sceneManager() : _currentScene(NULL) {}
	~sceneManager() {}
};
