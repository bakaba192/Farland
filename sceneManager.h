#pragma once
#include "singletonBase.h"

//=================================================================================================
//	##	�� �Ŵ��� [ sceneManager ] (���)	##
//=================================================================================================

//���ӳ�� Ŭ���� ���漱��
class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
private:
	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

private:
	mSceneList _mSceneList;		//���� ��Ƶ� ������ ���� ���
	gameNode* _currentScene;		//�����
	string _currentSceneName;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�� �߰�
	gameNode* addScene(string sceneName, gameNode* scene);
	//�� ����
	HRESULT changeScene(string sceneName);

	string getCurrentSceneName() { return _currentSceneName; }

	sceneManager() : _currentScene(NULL) {}
	~sceneManager() {}
};
