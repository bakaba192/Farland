#include "stdafx.h"
#include "uiManager.h"

HRESULT uiManager::init(void)
{
	_uState = U_NONE;

	_numberFrame = 0;
	_numberCount = 0;
	_numberUpUp = 0;

	hund = 0;
	ten = 0;
	one = 0;

	_x = 0;
	_y = 0;

	isOnPrintDemage = false;

	return S_OK;
}

void uiManager::release(void)
{

}

void uiManager::popUpUI(int x, int y)
{
	_uState = U_NORMAL;
	_UIrect[0] = RectMake(x, y, 452, 102);

	if (_UIrect[0].right > WINSIZEX)
	{
		_UIrect[0].right = WINSIZEX;
		_UIrect[0].left = WINSIZEX - 452;
	}

	if (_UIrect[0].bottom > WINSIZEY)
	{
		_UIrect[0].bottom = WINSIZEY;
		_UIrect[0].top = WINSIZEY - 102;
	}

	_saveSlot = 0; //0~4


	_UIrect[1] = RectMake(_UIrect[0].left + 16, _UIrect[0].top + 16, 70, 70);
	_UIrect[2] = RectMake(_UIrect[0].left + 86, _UIrect[0].top + 16, 70, 70);
	_UIrect[3] = RectMake(_UIrect[0].left + 156, _UIrect[0].top + 16, 70, 70);
	_UIrect[4] = RectMake(_UIrect[0].left + 226, _UIrect[0].top + 16, 70, 70);
	_UIrect[5] = RectMake(_UIrect[0].left + 296, _UIrect[0].top + 16, 70, 70);
	_UIrect[6] = RectMake(_UIrect[0].left + 366, _UIrect[0].top + 16, 70, 70);
}

void uiManager::UIrender(HDC hdc)
{
	switch (_uState)
	{
	case U_NONE:

		break;
	case U_NORMAL:
		IMAGEMANAGER->render("����â", hdc, _UIrect[0].left, _UIrect[0].top);
		break;
	case U_MOVE:
		IMAGEMANAGER->render("����â_�̵�", hdc, _UIrect[0].left, _UIrect[0].top);
		break;
	case U_SKILL:
		IMAGEMANAGER->render("����â_��ų", hdc, _UIrect[0].left, _UIrect[0].top);
		break;
	case U_SKILL2:

		break;
	case U_ITEM:
		IMAGEMANAGER->render("����â_����", hdc, _UIrect[0].left, _UIrect[0].top);
		break;
	case U_TURNEND:
		IMAGEMANAGER->render("����â_��", hdc, _UIrect[0].left, _UIrect[0].top);
		break;
	case U_SAVE:
		IMAGEMANAGER->render("����â_����", hdc, _UIrect[0].left, _UIrect[0].top);
		SetTextColor(hdc, RGB(0, 0, 0));
		TextOut(hdc, _UIrect[5].left + 20, _UIrect[5].top + 20, "����", strlen("����"));
		break;
	case U_SAVE2:
		IMAGEMANAGER->render("���̺�â", hdc, _UIrect[0].left, _UIrect[0].top);

		for (int i = 1; i < 6; i++)
		{
			if (PtInRect(&UIMANAGER->getUIrect()[i], _ptMouse))
			{

				IMAGEMANAGER->render("���̺� ����2", hdc, UIMANAGER->getUIrect()[i].left, UIMANAGER->getUIrect()[i].top);
			}
		}

		break;
	case U_LOAD:
		IMAGEMANAGER->render("����â_�ε�", hdc, _UIrect[0].left, _UIrect[0].top);
		SetTextAlign(hdc, 0);
		SetTextColor(hdc, RGB(0, 0, 0));
		TextOut(hdc, _UIrect[6].left + 20, _UIrect[6].top + 20, "�ε�", strlen("�ε�"));
		break;
	case U_LOAD2:
		IMAGEMANAGER->render("�ε�â", hdc, _UIrect[0].left, _UIrect[0].top);


		for (int i = 1; i < 6; i++)
		{
			if (PtInRect(&UIMANAGER->getUIrect()[i], _ptMouse))
			{

				IMAGEMANAGER->render("�ε� ����2", hdc, UIMANAGER->getUIrect()[i].left, UIMANAGER->getUIrect()[i].top);
			}
		}
		break;
	default:
		
		break;
	}
}


bool uiManager::printDemage(int x, int y, int Demage)
{
	_x = x;
	_y = y;

	isOnPrintDemage = true;

	hund = Demage / 100;
	ten = (Demage % 100) / 10;
	one = Demage % 10;


	_numberCount++;

	if (_numberCount > 4)
	{
		_numberCount = 0;
		_numberFrame++;
	}

	if (_numberFrame < 9)
	{
		_numberUpUp = 32 * sinf(22.5 * M_RAD * _numberFrame);//�̺κ��� �� �Ҿ�
	}

	

	if (_numberFrame > 17)
	{
		_numberFrame = 0;
		_numberCount = 0;
		_numberUpUp = 0;

		isOnPrintDemage = false;

		return true;
	}
	return false;
}

void  uiManager::DemageRender(HDC hdc)
{
	if (isOnPrintDemage)
	{
		if (hund == 0)//100�� �ڸ� ����
		{
			if (ten == 0)//1�� �ڸ� ���
			{
				IMAGEMANAGER->focusFrameRender("������Ʈ2", hdc, MAPDATA->getTileData(_x, _y)->rc.left + 24, MAPDATA->getTileData(_x, _y)->rc.top - 64 - _numberUpUp, _numberFrame, one);
				//Rectangle(hdc, MAPDATA->getTileData(_x, _y)->rc.left, MAPDATA->getTileData(_x, _y)->rc.top, MAPDATA->getTileData(_x, _y)->rc.right, MAPDATA->getTileData(_x, _y)->rc.bottom);
			}
			else//10�� �ڸ� ���
			{
				IMAGEMANAGER->focusFrameRender("������Ʈ2", hdc, MAPDATA->getTileData(_x, _y)->rc.left + 16, MAPDATA->getTileData(_x, _y)->rc.top - 64 - _numberUpUp, _numberFrame, ten);
				IMAGEMANAGER->focusFrameRender("������Ʈ2", hdc, MAPDATA->getTileData(_x, _y)->rc.left + 32, MAPDATA->getTileData(_x, _y)->rc.top - 64 - _numberUpUp, _numberFrame, one);
			}
		}
		else//100�� �ڸ� ���� ���
		{
			IMAGEMANAGER->focusFrameRender("������Ʈ2", hdc, MAPDATA->getTileData(_x, _y)->rc.left + 8, MAPDATA->getTileData(_x, _y)->rc.top - 64 - _numberUpUp, _numberFrame, hund);
			IMAGEMANAGER->focusFrameRender("������Ʈ2", hdc, MAPDATA->getTileData(_x, _y)->rc.left + 24, MAPDATA->getTileData(_x, _y)->rc.top - 64 - _numberUpUp, _numberFrame, ten);
			IMAGEMANAGER->focusFrameRender("������Ʈ2", hdc, MAPDATA->getTileData(_x, _y)->rc.left + 40, MAPDATA->getTileData(_x, _y)->rc.top - 64 - _numberUpUp, _numberFrame, one);
		}
	}
}

