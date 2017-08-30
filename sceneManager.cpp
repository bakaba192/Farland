#include "stdafx.h"
#include "SceneManager.h"
#include "gameNode.h"

//=================================================================================================
//	##	씬 매니저 [ sceneManager ] (클래스)	##
//=================================================================================================

//초기화
HRESULT sceneManager::init(void)
{
	return S_OK;
}


//해제
void sceneManager::release(void)
{

	//정석으로 반복자를 통한 삭제
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

	//stl 같은 곳에 사용한다
	//auto 자동으로 자료형을 반환한다.
	//in 어디꺼를 돌릴거냐!!
	//for each(auto scene in _mSceneList)
	//{
	//	scene.second->release();
	//	SAFE_DELETE(scene.second);
	//}
}

//업데이트
void sceneManager::update(void)
{
	if (_currentScene) _currentScene->update();
}

//렌더
void sceneManager::render(void)
{
	if (_currentScene) _currentScene->render();
}



//씬 추가
gameNode * sceneManager::addScene(string sceneName, gameNode * scene)
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

//씬 변경
HRESULT sceneManager::changeScene(string sceneName)
{
	miSceneList find = _mSceneList.find(sceneName);

	//못찾았다
	if (find == _mSceneList.end()) return E_FAIL;

	//바꾸려는 씬과 현재씬이 같냐?
	if (find->second == _currentScene) return E_FAIL;

	_currentSceneName = sceneName;

	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		return S_OK;
	}

	return E_FAIL;
}
