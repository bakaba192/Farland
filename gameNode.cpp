#include "stdafx.h"
#include "gameNode.h"

//===== ## [ ���� ��� Ŭ���� ] ## =====

//=================================================================================================
//	##	�ʱ�ȭ init(void)	##
//=================================================================================================

HRESULT gameNode::init(void)
{
	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		//SetTimer(_hWnd, 1, 10, NULL);	//Ÿ�̸� �ʱ�ȭ(�ڵ�, Ÿ�̸ӹ�ȣ, �ð�(��), NULL)
		KEYMANAGER->init();				//Ű�Ŵ��� �̱��� �ʱ�ȭ
		RND->init();					//�����Լ� �̱��� �ʱ�ȭ
		IMAGEMANAGER->init();			//�̹����Ŵ��� �̱��� �ʱ�ȭ
		GDI->init();					//GDI �̱��� �ʱ�ȭ
		SCENEMANAGER->init();			//���Ŵ��� �ʱ�ȭ
		TIMEMANAGER->init();			//Ÿ�ӸŴ��� �ʱ�ȭ
		INIDATA->init();				//INI������ �ʱ�ȭ
		SOUNDMANAGER->init();			//����Ŵ��� �ʱ�ȭ
		D2D->init();					//D2D�Ŵ��� �̹��� �ʱ�ȭ
		FOCUSMANAGER->init();			//��Ŀ���Ŵ��� �ʱ�ȭ
		STATEMANAGER->init();
		MAPDATA->init();
		UIMANAGER->init();
		CHARADATA->init();
		ENDINGMANAGER->init();
	}

	return S_OK;
}


//=================================================================================================
//	##	���� release(void)	##
//=================================================================================================

void gameNode::release(void)
{
	if (_managerInit)
	{
		//Ÿ�̸� ����
		//KillTimer(_hWnd, 1);
		//Ű����_�Ŵ��� �̱��� ����
		KEYMANAGER->releaseSingleton();	
		//���� �Լ� �̱��� ����
		RND->releaseSingleton();
		//�̹��� �Ŵ��� ���� �� ��Ŭ�� ����
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		//GDI �̹��� �Ŵ��� ���� �� �̱��� ����
		GDI->release();
		GDI->releaseSingleton();
		//���Ŵ��� ����, �̱��� ����
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		//Ÿ�ӸŴ��� �̱��� ����
		TIMEMANAGER->releaseSingleton();
		//INI������ �̱��� ����
		INIDATA->releaseSingleton();
		//����Ŵ��� ����, �̱��� ����
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
		D2D->release();
		D2D->releaseSingleton();

		//��Ŀ���Ŵ��� �̱��� ����
		FOCUSMANAGER->releaseSingleton();

		STATEMANAGER->releaseSingleton();

		//�ʵ����� �̱��� ����
		MAPDATA->releaseSingleton();

		//�����ͺ��̽� �̱��� ����
		DATABASE->releaseSingleton();

		//UI�Ŵ��� �̱�������
		UIMANAGER->releaseSingleton();

		CHARADATA->releaseSingleton();

		ENDINGMANAGER->releaseSingleton();
	}
}

//=================================================================================================
//	##	������Ʈ update(void)	##
//=================================================================================================

void gameNode::update(void)
{
	//���ΰ�ħ (���߿� ���� Ÿ�̸Ӹ� ���� �Ŀ��� ������� �ʴ´�)
	//������۸� ���� ������� �ʴ´� (true => false)
	//���߿� �׽�Ʈ �ϱ� (true / false or �������)
	//InvalidateRect(_hWnd, NULL, FALSE);	//�ٽ� �׸���
}


//=================================================================================================
//	##	���� render(HDC hdc)	##
//=================================================================================================

void gameNode::render(void)
{
}



//=================================================================================================
//	##	���� ���ν��� [ mainProc() ]	##
//=================================================================================================

LRESULT gameNode::MainProc(HWND hWnd, UINT iMes, WPARAM wP, LPARAM lP)
{
	//HDC hdc;			//�׸��� ����
	//PAINTSTRUCT ps;		//������ ����ü ����

	switch (iMes)
	{
	//case WM_TIMER:	//Ÿ�̸�
	//	this->update();
	//	break;
	//case WM_PAINT:	//������ �κ�
	//	hdc = BeginPaint(hWnd, &ps);
	//	this->render();
	//	EndPaint(hWnd, &ps);
	//	break;

	//���콺 ��ǥ
	case WM_MOUSEMOVE:	
		_ptMouse.x = LOWORD(lP);
		_ptMouse.y = HIWORD(lP);
		break;
	//Ű���� ���� Ŭ��
	case WM_LBUTTONDBLCLK:
		_doubleClick = true;
		break;
	//���콺 ��
	case WM_MOUSEWHEEL:
		if ((SHORT)HIWORD(wP) > 0)
		{
			// �ϰ� ���� ���� -��
		}
		
		else
		{
			// �ϰ� ���� ���� - �ٿ�
		}
	case WM_KEYDOWN:	//Ű����
		switch (wP)
		{
		case VK_ESCAPE:	//ESCŰ ������ ��������
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);	//�޽��� ������ ����
		break;
	}


	return (DefWindowProc(hWnd, iMes, wP, lP));
}
