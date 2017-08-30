#include "stdafx.h"
#include "SceneManager.h"
#include "gameNode.h"

//=================================================================================================
//	##	�� �Ŵ��� [ sceneManager ] (Ŭ����)	##
//=================================================================================================

//�ʱ�ȭ
HRESULT sceneManager::init(void)
{
	return S_OK;
}


//����
void sceneManager::release(void)
{

	//�������� �ݺ��ڸ� ���� ����
	miSceneList iter = _mSceneList.begin();
	for (; iter != _mSceneList.end();)
	{
		if (iter->second != NULL)
		{
			if (iter->second == _currentScene) iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mSceneList.erase(iter);
		}
		else
		{
			++iter;
		}
	}


	_mSceneList.clear();

	//stl ���� ���� ����Ѵ�
	//auto �ڵ����� �ڷ����� ��ȯ�Ѵ�.
	//in ��𲨸� �����ų�!!
	//for each(auto scene in _mSceneList)
	//{
	//	scene.second->release();
	//	SAFE_DELETE(scene.second);
	//}
}

//������Ʈ
void sceneManager::update(void)
{
	if (_currentScene) _currentScene->update();
}

//����
void sceneManager::render(void)
{
	if (_currentScene) _currentScene->render();
}



//�� �߰�
gameNode * sceneManager::addScene(string sceneName, gameNode * scene)
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

//�� ����
HRESULT sceneManager::changeScene(string sceneName)
{
	miSceneList find = _mSceneList.find(sceneName);

	//��ã�Ҵ�
	if (find == _mSceneList.end()) return E_FAIL;

	//�ٲٷ��� ���� ������� ����?
	if (find->second == _currentScene) return E_FAIL;

	_currentSceneName = sceneName;

	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		return S_OK;
	}

	return E_FAIL;
}
