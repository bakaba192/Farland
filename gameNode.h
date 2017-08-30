#pragma once
#include "image.h"	 //�̹��� ������� ����
//=================================================================================================
//	##	���ӳ�� [ gameNode ] (���)	##
//=================================================================================================

//����� �̹����� ���������� ����� �α�
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);


class gameNode
{
private:
	//HDC
	HDC _hdc;
	//�Ŵ��� �ʱ�ȭ ����
	bool _managerInit;


public:
	//���� ��� �⺻�Լ�!
	virtual HRESULT init(void);	//HRESULT->�� ����Ǿ����� Ȯ�ο�
	virtual HRESULT init(bool managerInit);
	//virtual HRESULT init(int i);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//����� �̹��� ���
	image* getBackBuffer(void) { return _backBuffer; }

	//�޸� DC ���
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	//HDC ���(ȭ��� DC)
	HDC getHDC() { return _hdc; }

	//���� ���ν���
	LRESULT MainProc(HWND hWnd, UINT iMes, WPARAM wP, LPARAM lP);


	gameNode() {}
	virtual ~gameNode() {}	//�θ� Ŭ������ �Ҹ��� ȣ���� ����
};

