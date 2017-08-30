#pragma once
#include "image.h"	 //이미지 헤드파일 선언
//=================================================================================================
//	##	게임노드 [ gameNode ] (헤드)	##
//=================================================================================================

//백버퍼 이미지를 정적변수로 만들어 두기
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);


class gameNode
{
private:
	//HDC
	HDC _hdc;
	//매니저 초기화 여부
	bool _managerInit;


public:
	//게임 노드 기본함수!
	virtual HRESULT init(void);	//HRESULT->잘 실행되었는지 확인용
	virtual HRESULT init(bool managerInit);
	//virtual HRESULT init(int i);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//백버퍼 이미지 얻기
	image* getBackBuffer(void) { return _backBuffer; }

	//메모리 DC 얻기
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	//HDC 얻기(화면용 DC)
	HDC getHDC() { return _hdc; }

	//메인 프로시저
	LRESULT MainProc(HWND hWnd, UINT iMes, WPARAM wP, LPARAM lP);


	gameNode() {}
	virtual ~gameNode() {}	//부모 클래스로 소멸자 호출을 방지
};

