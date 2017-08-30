#include "stdafx.h"
#include "stageScene.h"

HRESULT stageScene::init()
{
	_backGround[0] = IMAGEMANAGER->findImage("���1");
	_backGround[1] = IMAGEMANAGER->findImage("���2");
	_backGround[2] = IMAGEMANAGER->findImage("���3");

	_saveSlot = 1;

	_charaStateLevel = 0;

	_turnCount = 1;

	_gameStart = true;

	_map = new stageMap;
	_map->init();

	stageInitialize();

	_selectedChara = nullptr;
	_selectedMonster = nullptr;
	_healTarget = nullptr;

	//=============================���� �ʱ�ȭ==============================//
	_tempCount = 0;//�׽�Ʈ������ �ӽ����� ī���Ϳ� ������
	_tempFrame = 0;

	_clipingRc = { 0,0,WINSIZEX,WINSIZEY };

	_charaStateRect = RectMake(0, WINSIZEY - 100, 300, 100);

	_isShowStateWindow = false;

	_hpBar = new stateBar;
	_mpBar = new stateBar;
	_ExpBar = new stateBar;

	_hpBar->init("ü�¹�_��", "ü�¹�_��", _charaStateRect.left + 130, _charaStateRect.top + 45);
	_mpBar->init("������_��", "������_��", _charaStateRect.left + 130, _charaStateRect.top + 65);
	_ExpBar->init("����ġ��_��", "����ġ��_��", 170, 250);

	_turnCount = 0;
	_turnSwitchCount = 0;

	_turnSwitch = false;

	for (int i = 0; i < _vCharacter.size(); i++)
	{
		if (_vCharacter[i]->getName() == "��")
		{
			FOCUSMANAGER->setFocus(WINSIZEX / 2 - _vCharacter[i]->getMoveRc().left, WINSIZEY / 2 - _vCharacter[i]->getMoveRc().top);
		}
	}

	_isSceneChange = false;

	_isVictory = false;

	_VictoryAlpha = 0;

	_isDefeat = false;

	_dark = false;

	_alpha = 255;

	_isLvUp = false;

	_deleyCount = 0;

	//test code
	if (MAPDATA->getStageNumber() == 2)
	{
		_vMonster[0]->getMStatus().moveLimit = 1000;
	}

	return S_OK;
}

void stageScene::release(void)
{

}

void stageScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		SCENEMANAGER->changeScene("����");
	}

	_hpBar->update();
	_mpBar->update();
	_ExpBar->update();

	WinLose();

	showCharaState();

	playerBehavior();
	_map->update();

	for (int i = 0; i < _vCharacter.size(); i++)
	{
		(*(_vCharacter.begin() + i))->update();
	}

	for (int i = 0; i < _vMonster.size(); i++)
	{
		(*(_vMonster.begin() + i))->update();
	}
	
	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		SCENEMANAGER->changeScene("����");
	}

}

void stageScene::render(void)
{

	_backGround[MAPDATA->getStageNumber() - 1]->render(getMemDC());

	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		Rectangle(getMemDC(), _clipingRc.left, _clipingRc.top, _clipingRc.right, _clipingRc.bottom);
	}

	_clipingRc = { 0 - FOCUSMANAGER->getFocusX() - 64,0 - FOCUSMANAGER->getFocusY() - 64,WINSIZEX - FOCUSMANAGER->getFocusX() + 64, WINSIZEY - FOCUSMANAGER->getFocusY() + 64 };

	RECT rc;

	for (int i = 0; i < TILEMAXI; i++)
	{
		for (int j = 0; j < TILEMAXJ; j++)
		{
			if (IntersectRect(&rc, &MAPDATA->getTileData(i, j)->rc, &_clipingRc))
			{
				_map->showBlock(i, j);
				_map->showTile(i, j);
				_map->showRange(i, j);
				_map->showObject(i, j);

				for (int x = 0; x < _vCharacter.size(); x++)
				{
					if ((*(_vCharacter.begin() + x))->getState() == C_MOVETEMPORARY)
					{
						if ((*(_vCharacter.begin() + x))->getTempPosX() == i && (*(_vCharacter.begin() + x))->getTempPosY() == j)
						{
							(*(_vCharacter.begin() + x))->render();
						}
					}
					else
					{
						if ((*(_vCharacter.begin() + x))->getPosX() == i && (*(_vCharacter.begin() + x))->getPosY() == j)
						{
							(*(_vCharacter.begin() + x))->render();
						}
					}
				}
				for (int x = 0; x < _vMonster.size(); x++)
				{
					if ((*(_vMonster.begin() + x))->getPosX() == i && (*(_vMonster.begin() + x))->getPosY() == j)
					{
						(*(_vMonster.begin() + x))->render();
					}
				}
			}
			else
			{

			}
		}
	}
	_map->showSelectedTile();


	for (int i = 0; i < _vMonster.size(); i++)
	{
		(*(_vMonster.begin() + i))->DemageRender();
	}

	for (int i = 0; i < _vCharacter.size(); i++)
	{
		(*(_vCharacter.begin() + i))->DemageRender();
	}

	for (int i = 0; i < _vCharacter.size(); i++)
	{
		if ((*(_vCharacter.begin() + i))->getSelectedSkill() != nullptr)
		{
			(*(_vCharacter.begin() + i))->getSelectedSkill()->showFireSkill();
		}
	}

	UIMANAGER->UIrender(getMemDC());

	if (_isShowStateWindow && STATEMANAGER->getState() == B_NONE)
	{
		IMAGEMANAGER->render("ĳ����_����â", getMemDC(), _charaStateRect.left, _charaStateRect.top);
		IMAGEMANAGER->frameRender(_charaStateName + "_�غ�", getMemDC(), _charaStateRect.left, _charaStateRect.top, 1, 0);
		SetBkMode(getMemDC(), TRANSPARENT);

		string str = "LV" + to_string(_charaStateLevel) + " " + _charaStateName;

		TextOut(getMemDC(), _charaStateRect.left + 96, _charaStateRect.top + 15, str.c_str(), strlen(str.c_str()));

		TextOut(getMemDC(), _charaStateRect.left + 96, _charaStateRect.top + 40, "HP", strlen("HP"));
		TextOut(getMemDC(), _charaStateRect.left + 96, _charaStateRect.top + 60, "MP", strlen("MP"));

		_hpBar->render();
		_mpBar->render();



	}

	static int tempCount = 0;

	if (_gameStart)
	{
		if (tempCount < 50)
		{
			tempCount++;

			SetBkMode(getMemDC(), TRANSPARENT);

			IMAGEMANAGER->render("�˸�_â", getMemDC(), WINSIZEX / 2 - 50, WINSIZEY / 2 - 50);
			TextOut(getMemDC(), WINSIZEX / 2 - 30, WINSIZEY / 2 - 30, " *��ǥ* ", strlen(" *��ǥ* "));
			TextOut(getMemDC(), WINSIZEX / 2 - 40, WINSIZEY / 2 - 10, "���� ����", strlen("���� ����"));
		}
		else
		{
			if (_turnSwitch)
			{
				if (_turnSwitchCount < 50)
				{
					_turnSwitchCount++;

					string printTurn = "�� " + to_string(_turnCount);

					IMAGEMANAGER->render("�˸�_â", getMemDC(), WINSIZEX / 2 - 50, WINSIZEY / 2 - 50);
					TextOut(getMemDC(), WINSIZEX / 2 - 30, WINSIZEY / 2 - 30, printTurn.c_str(), strlen(printTurn.c_str()));


				}
				else
				{
					_turnSwitch = false;
					_turnSwitchCount = 0;
				}
			}

		}
	}

	if (STATEMANAGER->getState() == B_GAINEXP)
	{
		IMAGEMANAGER->render("����ġâ", getMemDC(), 140, 200);

		string ExpStr = _selectedChara->getName() + "��(��)" + to_string(_gainExp) + "����Ʈ�� ����ġ�� �����!";
		TextOut(getMemDC(), 150, 220, ExpStr.c_str(), strlen(ExpStr.c_str()));
		if (_isLvUp)
		{
			TextOut(getMemDC(), 150, 270, (_selectedChara->getName() + "��(��) ������ �ö���!").c_str(), strlen((_selectedChara->getName() + "��(��) ������ �ö���!").c_str()));
		}

		_ExpBar->render();
	}

	if (_isVictory && STATEMANAGER->getState() == B_NONE)
	{
		IMAGEMANAGER->findImage("�¸�")->alphaRender(getMemDC(), 70, 150, _VictoryAlpha);
	}

	IMAGEMANAGER->findImage("����ȭ��")->alphaRender(getMemDC(), _alpha);
}

void stageScene::playerBehavior()//�÷��̾��� �ൿ�� ���°������� �����ϴ� �Լ�
{
	if (STATEMANAGER->getMyTurnStart() == true)
	{
		_turnSwitch = true;
		_turnCount++;

		for (int i = 0; i < _vCharacter.size(); i++)
		{
			_vCharacter[i]->getStatus().isReadyToBehavior = true;
			(*(_vCharacter.begin() + i))->getStatus().isReadyToMove = true;
		}
		STATEMANAGER->getMyTurnStart() = false;
	}

	if (STATEMANAGER->getEnemyTurnStart() == true)
	{
		for (int i = 0; i < _vMonster.size(); i++)
		{
			(*(_vMonster.begin() + i))->getMStatus().isReadyToBehavior = true;
			(*(_vMonster.begin() + i))->getMStatus().isReadyToMove = true;
		}
		STATEMANAGER->getEnemyTurnStart() = false;
	}


	//������!


	if (STATEMANAGER->getMyTurn() == true)
	{
		switch (STATEMANAGER->getState())
		{
		case B_NONE:
		{
			for (int i = 0; i < _vCharacter.size(); i++)
			{
				if (MAPDATA->getPickI() == (*(_vCharacter.begin() + i))->getPosX() && MAPDATA->getPickJ() == (*(_vCharacter.begin() + i))->getPosY())
				{
					//ĳ���� ���� ����â�� ���δ�

					//Ŭ���� ����� ����.
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_selectedChara = (*(_vCharacter.begin() + i));
						if (_selectedChara != nullptr)
						{
							if (_selectedChara->getStatus().isReadyToMove)
							{
								MAPDATA->showMoveRange(_selectedChara->getPosX(), _selectedChara->getPosY(), _selectedChara->getStatus().moveLimit);
								STATEMANAGER->setState(B_SHOWMOVERANGE);
							}
						}
					}
					else if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
					{
						_selectedChara = (*(_vCharacter.begin() + i));
						//�˾�â ���.
						UIMANAGER->popUpUI(_ptMouse.x, _ptMouse.y);
						STATEMANAGER->setState(B_SHOWPOPUPMENU);
					}
					break;
				}
			}
			break;
		}
		case B_SHOWPOPUPMENU:
		{

			if (PtInRect(&UIMANAGER->getUIrect()[1], _ptMouse))
			{
				if (_selectedChara->getStatus().isReadyToMove)
				{
					UIMANAGER->getUiState() = U_MOVE;
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						UIMANAGER->getUiState() = U_NONE;
						if (_selectedChara != nullptr)
						{
							MAPDATA->showMoveRange(_selectedChara->getPosX(), _selectedChara->getPosY(), _selectedChara->getStatus().moveLimit);
							STATEMANAGER->setState(B_SHOWMOVERANGE);
						}
					}
				}
			}
			else if (PtInRect(&UIMANAGER->getUIrect()[2], _ptMouse))
			{
				if (_selectedChara->getStatus().isReadyToBehavior)
				{
					UIMANAGER->getUiState() = U_SKILL;
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						//�ӽ������� ��ų �������� Ŭ���ϸ� ���� �÷��� ����Ʈ�� �̾�������.
						//_selectedChara->getSelectedSkill()->skillSetting()//�ӽ������� selected��ų�� �÷��ӹ���Ʈ�� �����Ѵ�.���߿� �ٽ� �����ؾ���.

						if (_selectedChara->getName() == "ī��")
						{
							MAPDATA->showSkillrange(_selectedChara->getPosX(), _selectedChara->getPosY(), _selectedChara->getSelectedSkill()->getRange());

						}
						else if (_selectedChara->getName() == "�Ƹ���")
						{
							MAPDATA->showSkillrange(_selectedChara->getPosX(), _selectedChara->getPosY(), _selectedChara->getSelectedSkill()->getRange(), true);
						}


						UIMANAGER->getUiState() = U_NONE;

						STATEMANAGER->setState(B_SHOWSKILLRANGE);
					}
				}
			}
			else if (PtInRect(&UIMANAGER->getUIrect()[3], _ptMouse))
			{
				if (_selectedChara->getStatus().isReadyToBehavior)
				{
					UIMANAGER->getUiState() = U_ITEM;

					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						UIMANAGER->getUiState() = U_NONE;
						STATEMANAGER->setState(B_NONE);
					}
				}
			}
			else if (PtInRect(&UIMANAGER->getUIrect()[4], _ptMouse))
			{
				UIMANAGER->getUiState() = U_TURNEND;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					UIMANAGER->getUiState() = U_NONE;
					STATEMANAGER->getMyTurn() = false;
					STATEMANAGER->getEnemyTurnStart() = true;
					STATEMANAGER->setState(B_NONE);
				}
			}
			else if (PtInRect(&UIMANAGER->getUIrect()[5], _ptMouse))
			{
				UIMANAGER->getUiState() = U_SAVE;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					UIMANAGER->getUiState() = U_SAVE2;
					STATEMANAGER->setState(B_SHOWSAVEMENU);
					stageSave();
				}
			}
			else if (PtInRect(&UIMANAGER->getUIrect()[6], _ptMouse))
			{
				UIMANAGER->getUiState() = U_LOAD;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					UIMANAGER->getUiState() = U_LOAD2;
					STATEMANAGER->setState(B_SHOWLOADMENU);
					//stageLoad();
				}
			}
			else
			{
				UIMANAGER->getUiState() = U_NORMAL;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					UIMANAGER->getUiState() = U_NONE;
					STATEMANAGER->setState(B_NONE);
				}
			}


			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{

				UIMANAGER->getUiState() = U_NONE;

				STATEMANAGER->setState(B_NONE);
			}

			break;
		}
		case B_SHOWSAVEMENU:
		{

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				for (int i = 1; i < 6; i++)
				{
					if (PtInRect(&UIMANAGER->getUIrect()[i], _ptMouse))
					{
						UIMANAGER->getSaveSlot() = i;
						stageSave();
						STATEMANAGER->setState(B_NONE);
						UIMANAGER->getUiState() = U_NONE;
					}
				}

				if (PtInRect(&UIMANAGER->getUIrect()[6], _ptMouse))
				{
					STATEMANAGER->setState(B_SHOWPOPUPMENU);
					UIMANAGER->getUiState() = U_NORMAL;
				}
			}


			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{

				UIMANAGER->getUiState() = U_NONE;

				STATEMANAGER->setState(B_NONE);
			}

			break;
		}
		case B_SHOWLOADMENU:
		{
			for (int i = 1; i < 6; i++)
			{
				if (PtInRect(&UIMANAGER->getUIrect()[i], _ptMouse))
				{
					UIMANAGER->getSaveSlot() = i;
					IMAGEMANAGER->render("�ε� ����2", getMemDC(), UIMANAGER->getUIrect()[i].left, UIMANAGER->getUIrect()[i].top);
				}
			}

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				for (int i = 1; i < 6; i++)
				{
					if (PtInRect(&UIMANAGER->getUIrect()[i], _ptMouse))
					{
						UIMANAGER->getSaveSlot() = i;
						stageLoad();
						STATEMANAGER->setState(B_NONE);
						UIMANAGER->getUiState() = U_NONE;
					}
				}


				if (PtInRect(&UIMANAGER->getUIrect()[6], _ptMouse))
				{
					STATEMANAGER->setState(B_SHOWPOPUPMENU);
					UIMANAGER->getUiState() = U_NORMAL;
				}
			}


			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{

				UIMANAGER->getUiState() = U_NONE;

				STATEMANAGER->setState(B_NONE);
			}

			break;
		}
		case B_SHOWMOVERANGE:
		{
			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				MAPDATA->unShowRange();
				_selectedChara = nullptr;
				STATEMANAGER->setState(B_NONE);
			}

			for (int i = 0; i < TILEMAXI; i++)
			{
				for (int j = 0; j < TILEMAXJ; j++)
				{
					if (MAPDATA->getTileData(i, j)->tSELECT == S_TRUE2&& //�ش�Ÿ���� �̵������ϰ�
						MAPDATA->getPickI() == i && MAPDATA->getPickJ() == j)//���� �ش�Ÿ���� ����������
					{
						if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
						{
							if (_selectedChara != nullptr)
							{
								MAPDATA->initAstar(_selectedChara->getPosX(), _selectedChara->getPosY(), i, j);

								_selectedChara->setTempPos(i, j);
								_selectedChara->setState(C_MOVETEMPORARY);
								STATEMANAGER->setState(B_SHOWMELEEATTACK);//�и��������� �Ѿ�� �ֺ��� �˻��ϰ� ������ ���� ����Ʈ ������� �Ѿ.
							}
						}
					}
				}
			}
			break;
		}
		case B_SELECTFORWARD:
		{
			//������ȯ
			if (MAPDATA->getTileData(_selectedChara->getTempPosX(), _selectedChara->getTempPosY())->rc.left + FOCUSMANAGER->getFocusX() + 32 < _ptMouse.x &&
				MAPDATA->getTileData(_selectedChara->getTempPosX(), _selectedChara->getTempPosY())->rc.top + FOCUSMANAGER->getFocusY() - 32 < _ptMouse.y)
			{
				_selectedChara->setTempForward(3);
			}
			else if (MAPDATA->getTileData(_selectedChara->getTempPosX(), _selectedChara->getTempPosY())->rc.left + FOCUSMANAGER->getFocusX() + 32 > _ptMouse.x &&
				MAPDATA->getTileData(_selectedChara->getTempPosX(), _selectedChara->getTempPosY())->rc.top + FOCUSMANAGER->getFocusY() - 32 > _ptMouse.y)
			{
				_selectedChara->setTempForward(2);
			}
			else if (MAPDATA->getTileData(_selectedChara->getTempPosX(), _selectedChara->getTempPosY())->rc.left + FOCUSMANAGER->getFocusX() + 32 > _ptMouse.x &&
				MAPDATA->getTileData(_selectedChara->getTempPosX(), _selectedChara->getTempPosY())->rc.top + FOCUSMANAGER->getFocusY() - 32 < _ptMouse.y)
			{
				_selectedChara->setTempForward(1);
			}
			else if (MAPDATA->getTileData(_selectedChara->getTempPosX(), _selectedChara->getTempPosY())->rc.left + FOCUSMANAGER->getFocusX() + 32 < _ptMouse.x &&
				MAPDATA->getTileData(_selectedChara->getTempPosX(), _selectedChara->getTempPosY())->rc.top + FOCUSMANAGER->getFocusY() - 32 > _ptMouse.y)
			{
				_selectedChara->setTempForward(0);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				MAPDATA->unShowRange();

				_selectedChara->setWayStack(MAPDATA->Astar());
				_selectedChara->setForward(_selectedChara->getTempForward());

				_selectedChara->setState(C_MOVE);
				//_selectedChara = nullptr;
				STATEMANAGER->setState(B_ONMOVING);
			}
			//�ൿ ���
			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				MAPDATA->unShowRange();
				_selectedChara->setState(C_READY);
				_selectedChara = nullptr;
				STATEMANAGER->setState(B_NONE);
			}
			break;
		}
		case B_SHOWMELEEATTACK:
		{
			//�ֺ�����
			//�ֺ��� �ƹ��͵� ���ų� ���ִº��� Ŭ���ϸ� ������ȯ���� �Ѿ
			//if()
			MAPDATA->unShowRange();

			if (showMeleeAttackRange(_selectedChara->getTempPosX(), _selectedChara->getTempPosY()) && _selectedChara->getStatus().isReadyToBehavior)//���� ������ true�� ��ȯ����.
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					if (MAPDATA->getPickI() == _selectedChara->getTempPosX() && MAPDATA->getPickJ() == _selectedChara->getTempPosY())
					{
						STATEMANAGER->setState(B_SELECTFORWARD);//�ڱ� �ڽ��� �ڸ��� �����ߴٸ� �����带 �����Ѵ�.
					}
					else if (MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->tSELECT == S_FALSE2)
					{
						//���Ŭ��

						//���ݴ���� ����
						for (int g = 0; g < _vMonster.size(); g++)
						{
							if ((*(_vMonster.begin() + g))->getPosX() == MAPDATA->getPickI() && (*(_vMonster.begin() + g))->getPosY() == MAPDATA->getPickJ())
							{
								_selectedMonster = (*(_vMonster.begin() + g));
							}
						}

						MAPDATA->unShowRange();

						_selectedChara->setWayStack(MAPDATA->Astar());
						_selectedChara->setForward(_selectedChara->getTempForward());

						_selectedChara->setState(C_MOVE);
						//_selectedChara = nullptr;
						STATEMANAGER->setState(B_ONMOVING);
					}
				}
				else if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
				{
					MAPDATA->unShowRange();
					_selectedChara->setState(C_READY);
					_selectedChara = nullptr;
					STATEMANAGER->setState(B_NONE);
				}
			}
			else
			{
				STATEMANAGER->setState(B_SELECTFORWARD);//�и��������� �Ѿ�� �ֺ��� �˻��ϰ� ������ ���� ����Ʈ ������� �Ѿ.
			}
			break;
		}
		case B_ONATTACK://B_ONATTCK�� �ƴϰ� �Ǹ� �÷��̾ ���ݸ���� ������. �� �÷��̾ ���� B������Ʈ�� ������ �ʴ´�.
		{
			//MAPDATA->unShowRange();

			_selectedChara->setState(C_ATTACK);

			_selectedMonster->getMState() = M_DEMAGED;

			if (_selectedChara->getStatus().currentFrame > 10)
			{
				_selectedMonster->getMStatus().hp -= _selectedChara->getStatus().attack - _selectedMonster->getMStatus().def;
				STATEMANAGER->setState(B_PRINTDEMAGE);
			}
			break;
		}
		case B_ONMOVING:
		{
			FOCUSMANAGER->setFocus(WINSIZEX / 2 - _selectedChara->getMoveRc().left, WINSIZEY / 2 - _selectedChara->getMoveRc().top);
			if (_selectedChara->getWayStack().size() == 0 && _selectedChara->getState() == C_READY)
			{
				_selectedChara->getStatus().isReadyToMove = false;
				if (_selectedMonster != nullptr)
				{

					STATEMANAGER->setState(B_ONATTACK);
				}
				else
				{

					STATEMANAGER->setState(B_NONE);
				}
			}
			break;
		}
		case B_PRINTDEMAGE:
		{

			_selectedChara->getStatus().isReadyToBehavior = false;


			if (_selectedMonster->printDemage(_selectedChara->getStatus().attack - _selectedMonster->getMStatus().def))
			{
				//����ġ ó��...
				_gainExp += 10;

				if (_selectedMonster->getMStatus().hp <= 0)
				{
					_selectedMonster->getMState() = M_DEATH;
					STATEMANAGER->setState(B_ONDEATH);
				}
				else
				{
					_selectedChara->setState(C_READY);
					//_selectedMonster = nullptr;//�̰� ������ ����ϰ� ���� ó������.
					//_selectedChara = nullptr;//�ٽ� �÷��̾�� ���ʹ� ���� ����Ŵ.
					_totalExp = _gainExp + _selectedChara->getStatus().Exp;

					STATEMANAGER->setState(B_GAINEXP);
				}
			}
			break;
		}
		case B_ONDEATH:
		{
			//_selectedMonster->getMState() = M_DEATH;
			bool isNoDead = true;//��ü����!

			//if���� ���Ͱ� �������� ���͸� ���Ϳ��� �̾Ʒ��� �÷��̾�� ������Ʈ�� �ʱ�ȭ�Ѵ�.

			for (int i = 0; i < _vMonster.size(); i++)
			{
				if (((*(_vMonster.begin() + i))->getMState() == M_DEATH))
				{
					isNoDead = false; //��ü�� �ְ� ���� �Ⱦ�������.

					if ((*(_vMonster.begin() + i))->getAlpha() == 0)
					{
						_gainExp += 20;
						_vMonster.erase(_vMonster.begin() + i);
						break;
					}
				}
			}

			if (isNoDead)//��ü������ �������� ����!
			{

				_selectedChara->setState(C_READY);
				_selectedMonster = nullptr;//�̰� ������ ����ϰ� ���� ó������.
				//_selectedChara = nullptr;//�ٽ� �÷��̾�� ���ʹ� ���� ����Ŵ.
				_totalExp = _gainExp + _selectedChara->getStatus().Exp;

				STATEMANAGER->setState(B_GAINEXP);
			}
			break;
		}
		case B_SHOWSKILLRANGE:
		{
			//MAPDATA->showSkillrange(_selectedChara->getPosX(), _selectedChara->getPosY(), _selectedChara->getSelectedSkill()->getRange());

			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				MAPDATA->unShowRange();
				_selectedChara = nullptr;

				STATEMANAGER->setState(B_NONE);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_selectedChara->getName() == "ī��")
				{
					if (MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->tSELECT == S_FALSE2)
					{
						//���Ŭ��

						//���ݴ���� ����
						for (int g = 0; g < _vMonster.size(); g++)
						{
							if ((*(_vMonster.begin() + g))->getPosX() == MAPDATA->getPickI() && (*(_vMonster.begin() + g))->getPosY() == MAPDATA->getPickJ())
							{
								_selectedMonster = (*(_vMonster.begin() + g));
							}
						}

						if (_selectedMonster != nullptr)
						{
							MAPDATA->unShowRange();

							MAPDATA->showSkillrange(_selectedMonster->getPosX(), _selectedMonster->getPosY(), _selectedChara->getSelectedSkill()->getBound());

							_selectedChara->getSelectedSkill()->skillSetting(_selectedMonster->getPosX(), _selectedMonster->getPosY());

							STATEMANAGER->setState(B_SHOWSKILLBOUNDS);
						}
					}
				}
				else if (_selectedChara->getName() == "�Ƹ���")
				{
					if (MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->tSELECT == S_TRUE2)
					{
						//���Ŭ��

						//���ݴ���� ����
						for (int g = 0; g < _vCharacter.size(); g++)
						{
							if ((*(_vCharacter.begin() + g))->getPosX() == MAPDATA->getPickI() && (*(_vCharacter.begin() + g))->getPosY() == MAPDATA->getPickJ())
							{
								_healTarget = (*(_vCharacter.begin() + g));
							}
						}

						if (_healTarget != nullptr)
						{
							MAPDATA->unShowRange();

							MAPDATA->showSkillrange(_healTarget->getPosX(), _healTarget->getPosY(), _selectedChara->getSelectedSkill()->getBound(), true);

							_selectedChara->getSelectedSkill()->skillSetting(_healTarget->getPosX(), _healTarget->getPosY());

							STATEMANAGER->setState(B_SHOWSKILLBOUNDS);
						}
					}
				}
			}
			break;
		}
		case B_SHOWSKILLBOUNDS:
		{

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_selectedChara->getName() == "ī��")
				{
					if (MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->tSELECT == S_FALSE2)
					{
						MAPDATA->unShowRange();
						_selectedChara->setState(C_SKILL1);//��ų1�� ��ų 3���� �ڵ����� ���Ѵ�.

					}
				}
				else if (_selectedChara->getName() == "�Ƹ���")
				{
					if (MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->tSELECT == S_TRUE2)
					{
						MAPDATA->unShowRange();
						_selectedChara->setState(C_SKILL1);//��ų1�� ��ų 3���� �ڵ����� ���Ѵ�.

					}
				}
			}

			if (_selectedChara->getName() == "ī��")
			{
				if (_selectedChara->getState() == C_SKILL3)
				{
					_selectedChara->getSelectedSkill()->startFire();
					_selectedChara->getStatus().isReadyToBehavior = false;



					STATEMANAGER->setState(B_ONSKILLATTACK);
				}
			}
			else if (_selectedChara->getName() == "�Ƹ���")
			{
				if (_selectedChara->getState() == C_SKILL2)
				{
					_selectedChara->getSelectedSkill()->startFire();
					_selectedChara->getStatus().isReadyToBehavior = false;



					STATEMANAGER->setState(B_ONSKILLATTACK);
				}
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				MAPDATA->unShowRange();
				_selectedChara = nullptr;
				_selectedMonster = nullptr;
				_healTarget = nullptr;

				STATEMANAGER->setState(B_NONE);
			}

			break;
		}
		case B_ONSKILLATTACK:
		{
			int isEnd = false;

			for (int i = 0; i < _vMonster.size(); i++)
			{
				for (int j = 0; j < 13; j++)
				{
					if (_selectedChara->getSelectedSkill()->getSkillData(j).indexX == (*(_vMonster.begin() + i))->getPosX() &&
						_selectedChara->getSelectedSkill()->getSkillData(j).indexY == (*(_vMonster.begin() + i))->getPosY() &&
						_selectedChara->getSelectedSkill()->getSkillData(j).isShow == true)
					{
						if ((*(_vMonster.begin() + i))->getMState() != M_DEMAGED)
						{
							(*(_vMonster.begin() + i))->getMStatus().hp -= _selectedChara->getSelectedSkill()->getPower();

						}

						(*(_vMonster.begin() + i))->getMState() = M_DEMAGED;
					}
					//���õ� ��ų�� isShow���� true�̸� ������ ���¸� M_DEMAGED�� �����.
				}
			}

			for (int i = 0; i < 13; i++)
			{
				if (_selectedChara->getSelectedSkill()->getSkillData(i).isShow)
				{
					isEnd = true;
					break;
				}
			}

			if (isEnd == false)
			{
				STATEMANAGER->setState(B_PRINTSKILLDEMAGE);
			}


			break;
		}
		case B_PRINTSKILLDEMAGE:
		{

			bool isEnd = false;

			bool isDie = false;
			//�ٲ��� . �켱 ���͸� Ž���ؼ� ���Ͱ� DEMAGED�̸� ����Ʈ �������� ����, 
			if (_selectedChara->getName() == "ī��")
			{

				for (int i = 0; i < _vMonster.size(); i++)
				{
					if ((*(_vMonster.begin() + i))->getMState() == M_DEMAGED)
					{
						if ((*(_vMonster.begin() + i))->printDemage(_selectedChara->getSelectedSkill()->getPower()))
						{
							//������ �ѳ�� ����ġ;
							_gainExp += 7;
							isEnd = true;
							if ((*(_vMonster.begin() + i))->getMStatus().hp <= 0)
							{
								isDie |= true;//�� ������ �ִ���?
								(*(_vMonster.begin() + i))->getMState() = M_DEATH;

								//��ų�� óġ�� ����ġ ȹ��.
							}
						}
					}
				}
			}
			else if (_selectedChara->getName() == "�Ƹ���")
			{
				//������ ����Ʈ �Ϸ���?
				if (_healTarget->printDemage(_selectedChara->getSelectedSkill()->getPower(), true))
				{
					isEnd = true;

					_healTarget->getStatus().hp += _selectedChara->getSelectedSkill()->getPower();

					//ġ���� +5�� ����ġ;
					_gainExp += _selectedChara->getSelectedSkill()->getPower() + 5;
				}
			}

			if (isEnd == true)
			{
				//�װų� .. ���� �ʰų�..
				if (isDie == true)
				{
					STATEMANAGER->setState(B_ONDEATH);
				}
				else
				{
					_selectedChara->setState(C_READY);
					_selectedMonster = nullptr;//�̰� ������ ����ϰ� ���� ó������.
					//_selectedChara = nullptr;//�ٽ� �÷��̾�� ���ʹ� ���� ����Ŵ.
					_healTarget = nullptr;

					_totalExp = _gainExp + _selectedChara->getStatus().Exp;

					STATEMANAGER->setState(B_GAINEXP);
				}
			}
			break;
		}
		case B_GAINEXP:
		{
			if (!gainExp())//����ġ �� �����?
			{
				if (_isLvUp)
				{
					bool canMove = _selectedChara->getStatus().isReadyToMove;
					bool canBehavior = _selectedChara->getStatus().isReadyToBehavior;
					int tempForward = _selectedChara->getStatus().forward;
					_selectedChara->getStatus().lv++;
					_selectedChara->init(_selectedChara->getPosX(), _selectedChara->getPosY(), _selectedChara->getCName(), _selectedChara->getStatus().lv);
					_selectedChara->getStatus().isReadyToMove = canMove;
					_selectedChara->getStatus().isReadyToBehavior = canBehavior;
					_selectedChara->getStatus().forward = tempForward;
					_isLvUp = false;
				}

				_selectedChara = nullptr;
				_selectedMonster = nullptr;
				_healTarget = nullptr;
				_gainExp = 0;
				_totalExp = 0;

				STATEMANAGER->setState(B_NONE);
			}
			break;
		}
		default:
			break;
		}
	}
	else //���� ��
	{
		switch (STATEMANAGER->getState())
		{
		case B_NONE:
		{
			for (int i = 0; i < _vMonster.size(); i++)
			{
				if ((*(_vMonster.begin() + i))->getMStatus().isReadyToBehavior && (*(_vMonster.begin() + i))->getMStatus().isReadyToMove)
				{
					if (_selectedMonster == nullptr)
					{
						_selectedMonster = (*(_vMonster.begin() + i));
					}
				}
			}


			if (_selectedMonster != nullptr)//���Ͱ� ���õǾ��ٸ� Ÿ���� �����϶�.
			{
				//�Ÿ��񱳸� ���� ������
				int a1 = 0;
				int b1 = 0;
				int a2 = 0;
				int b2 = 0;

				//_selectedChara = *_vCharacter.begin();
				a1 = 1000;//abs(_selectedMonster->getPosX() - _selectedChara->getPosX());
				b1 = 1000;//abs(_selectedMonster->getPosY() - _selectedChara->getPosY());



				for (int i = 0; i < _vCharacter.size(); i++)
				{
					a2 = abs(_selectedMonster->getPosX() - (*(_vCharacter.begin() + i))->getPosX());
					b2 = abs(_selectedMonster->getPosY() - (*(_vCharacter.begin() + i))->getPosY());
					if ((a1 + b1 > a2 + b2) && (*(_vCharacter.begin() + i))->getState() != C_STUN)
					{
						a1 = a2;
						b1 = b2;
						_selectedChara = (*(_vCharacter.begin() + i));
					}
				}

				if (_selectedChara == nullptr)
				{
					//���̻� ����� ����.
					_selectedMonster->getMStatus().isReadyToBehavior = false;
					return;
				}

				POINT minXY;//���� ����� ���� ã�´�.
				minXY.x = 10000;
				minXY.y = 10000;

				if (_selectedChara->getPosX() < TILEMAXI - 1)
				{
					if (abs(_selectedMonster->getPosX() - (_selectedChara->getPosX() + 1)) + abs(_selectedMonster->getPosY() - _selectedChara->getPosY())
						< abs(_selectedMonster->getPosX() - minXY.x) + abs(_selectedMonster->getPosY() - minXY.y) &&
						MAPDATA->getTileData(_selectedChara->getPosX() + 1, _selectedChara->getPosY())->isOpen)
					{
						minXY.x = _selectedChara->getPosX() + 1;
						minXY.y = _selectedChara->getPosY();

					}
				}

				if (_selectedChara->getPosX() > 0)
				{
					if (abs(_selectedMonster->getPosX() - (_selectedChara->getPosX() - 1)) + abs(_selectedMonster->getPosY() - _selectedChara->getPosY())
						< abs(_selectedMonster->getPosX() - minXY.x) + abs(_selectedMonster->getPosY() - minXY.y) &&
						MAPDATA->getTileData(_selectedChara->getPosX() - 1, _selectedChara->getPosY())->isOpen)
					{
						minXY.x = _selectedChara->getPosX() - 1;
						minXY.y = _selectedChara->getPosY();

					}
				}

				if (_selectedChara->getPosY() < TILEMAXJ - 1)
				{
					if (abs(_selectedMonster->getPosX() - (_selectedChara->getPosX())) + abs(_selectedMonster->getPosY() - (_selectedChara->getPosY() + 1))
						< abs(_selectedMonster->getPosX() - minXY.x) + abs(_selectedMonster->getPosY() - minXY.y) &&
						MAPDATA->getTileData(_selectedChara->getPosX(), _selectedChara->getPosY() + 1)->isOpen)
					{
						minXY.x = _selectedChara->getPosX();
						minXY.y = _selectedChara->getPosY() + 1;

					}
				}

				if (_selectedChara->getPosX() > 0)
				{
					if (abs(_selectedMonster->getPosX() - (_selectedChara->getPosX())) + abs(_selectedMonster->getPosY() - (_selectedChara->getPosY() - 1))
						< abs(_selectedMonster->getPosX() - minXY.x) + abs(_selectedMonster->getPosY() - minXY.y) &&
						MAPDATA->getTileData(_selectedChara->getPosX(), _selectedChara->getPosY() - 1)->isOpen)
					{
						minXY.x = _selectedChara->getPosX();
						minXY.y = _selectedChara->getPosY() - 1;

					}
				}

				//Ÿ���� �����ߴ�.
				//���� �̵� �� ������ �ϰ� Ÿ�� ������ ���� �ؾ���.
				if ((abs(_selectedMonster->getPosX() - _selectedChara->getPosX()) + abs(_selectedMonster->getPosY() - _selectedChara->getPosY())) == 1)
				{

					int i = 0;
					int j = 0;

					i = _selectedMonster->getPosX() - _selectedChara->getPosX();
					j = _selectedMonster->getPosY() - _selectedChara->getPosY();

					if (i == 1)
					{
						_selectedMonster->getMStatus().forward = 2;
					}
					else if (i == -1)
					{
						_selectedMonster->getMStatus().forward = 3;
					}
					else if (j == 1)
					{
						_selectedMonster->getMStatus().forward = 0;
					}
					else if (j == -1)
					{
						_selectedMonster->getMStatus().forward = 1;
					}

					_selectedMonster->getMState() = M_ATTACK;
					_selectedMonster->getOnAttack() = true;
					STATEMANAGER->setState(B_ONATTACK);
				}
				else
				{
					//���� ���̽�Ÿ�� �غ��Ѵ�. 


					MAPDATA->initAstar(_selectedMonster->getPosX(), _selectedMonster->getPosY(), minXY.x, minXY.y);
					_selectedMonster->setWayStack(MAPDATA->Astar());
					_selectedMonster->getMState() = M_MOVE;
					STATEMANAGER->setState(B_ONMOVING);
				}


			}
			else
			{
				//���̻� ������ ���� ����.

				STATEMANAGER->getMyTurn() = true;
				STATEMANAGER->getMyTurnStart() = true;
			}

			break;
		}
		case B_ONMOVING:
		{
			FOCUSMANAGER->setFocus(WINSIZEX / 2 - _selectedMonster->getMoveRc().left, WINSIZEY / 2 - _selectedMonster->getMoveRc().top);

			if (_selectedMonster->getStack().size() == 0 && _selectedMonster->getMState() == M_READY)
			{
				_selectedMonster->getMStatus().isReadyToMove = false;

				if ((abs(_selectedMonster->getPosX() - (_selectedChara->getPosX())) + abs(_selectedMonster->getPosY() - _selectedChara->getPosY())) == 1)
				{
					int i = 0;
					int j = 0;

					i = _selectedMonster->getPosX() - _selectedChara->getPosX();
					j = _selectedMonster->getPosY() - _selectedChara->getPosY();

					if (i == 1)
					{
						_selectedMonster->getMStatus().forward = 2;
					}
					else if (i == -1)
					{
						_selectedMonster->getMStatus().forward = 3;
					}
					else if (j == 1)
					{
						_selectedMonster->getMStatus().forward = 0;
					}
					else if (j == -1)
					{
						_selectedMonster->getMStatus().forward = 1;
					}

					_selectedMonster->getMState() = M_ATTACK;
					_selectedMonster->getOnAttack() = true;
					STATEMANAGER->setState(B_ONATTACK);
				}
				else
				{
					_selectedMonster->getMState() = M_READY;
					_selectedChara = nullptr;
					_selectedMonster = nullptr;
					STATEMANAGER->setState(B_NONE);
				}
			}

			break;
		}
		case B_ONATTACK:
		{
			FOCUSMANAGER->setFocus(WINSIZEX / 2 - _selectedMonster->getMoveRc().left, WINSIZEY / 2 - _selectedMonster->getMoveRc().top);

			_selectedChara->setState(C_DEMAGED);

			if (_selectedMonster->getOnAttack() == false)
			{
				_selectedChara->getStatus().hp -= _selectedMonster->getMStatus().attack - _selectedChara->getStatus().def;


				STATEMANAGER->setState(B_PRINTDEMAGE);
			}
			break;
		}

		case B_PRINTDEMAGE:
		{
			_selectedMonster->getMStatus().isReadyToBehavior = false;
			if (_selectedChara->printDemage(_selectedMonster->getMStatus().attack - _selectedChara->getStatus().def))
			{
				_selectedMonster->getMState() = M_READY;
				if (_selectedChara->getStatus().hp <= 0)
				{
					//_selectedChara->setState(C_READY);
					_selectedChara->setState(C_READY);
					_selectedMonster = nullptr;//�̰� ������ ����ϰ� ���� ó������.
					_selectedChara = nullptr;//�ٽ� �÷��̾�� ���ʹ� ���� ����Ŵ.
					STATEMANAGER->setState(B_NONE);
				}
				else
				{
					_selectedChara->setState(C_READY);
					_selectedMonster = nullptr;//�̰� ������ ����ϰ� ���� ó������.
					_selectedChara = nullptr;//�ٽ� �÷��̾�� ���ʹ� ���� ����Ŵ.
					STATEMANAGER->setState(B_NONE);
				}
			}
			break;
		}
		case B_PRINTSKILLDEMAGE:

			break;

		case B_SHOWMOVERANGE:

			break;


		case B_SHOWMELEEATTACK:

			break;

		case B_SELECTFORWARD:

			break;

		case B_SHOWSKILLRANGE:

			break;
		case B_SHOWSKILLBOUNDS:

			break;
		case B_ONDEATH:

			break;
		default:
			break;
		}
	}
}

bool stageScene::showMeleeAttackRange(int i, int j)
{
	bool isThereEnemy = false;

	for (int x = 0; x < _vMonster.size(); x++)
	{
		if ((*(_vMonster.begin() + x))->getPosX() == i &&
			(*(_vMonster.begin() + x))->getPosY() == j - 1
			&& abs(MAPDATA->getTileData(i, j - 1)->z - MAPDATA->getTileData(i, j)->z) < 3)
		{
			MAPDATA->getTileData(i, j - 1)->tSELECT = S_FALSE2;
			_selectedChara->setTempForward(0);
			isThereEnemy = true;
		}
		else if ((*(_vMonster.begin() + x))->getPosX() == i &&
			(*(_vMonster.begin() + x))->getPosY() == j + 1
			&& abs(MAPDATA->getTileData(i, j - 1)->z - MAPDATA->getTileData(i, j)->z) < 3)
		{

			MAPDATA->getTileData(i, j + 1)->tSELECT = S_FALSE2;
			_selectedChara->setTempForward(1);
			isThereEnemy = true;
		}
		else if ((*(_vMonster.begin() + x))->getPosX() == i - 1 &&
			(*(_vMonster.begin() + x))->getPosY() == j
			&& abs(MAPDATA->getTileData(i, j - 1)->z - MAPDATA->getTileData(i, j)->z) < 3)
		{

			_selectedChara->setTempForward(2);
			MAPDATA->getTileData(i - 1, j)->tSELECT = S_FALSE2;
			isThereEnemy = true;
		}
		else if ((*(_vMonster.begin() + x))->getPosX() == i + 1 &&
			(*(_vMonster.begin() + x))->getPosY() == j
			&& abs(MAPDATA->getTileData(i, j - 1)->z - MAPDATA->getTileData(i, j)->z) < 3)
		{
			MAPDATA->getTileData(i + 1, j)->tSELECT = S_FALSE2;

			_selectedChara->setTempForward(3);

			isThereEnemy = true;
		}
	}

	if (isThereEnemy)
	{
		//�ڱ��ڸ� �Ķ��� ĥ�ϱ�
		MAPDATA->getTileData(i, j)->tSELECT = S_TRUE2;
	}

	return isThereEnemy;
}

void stageScene::showCharaState()
{
	if (MAPDATA->getTileData(MAPDATA->getPickI(), MAPDATA->getPickJ())->isOpen == false)
	{
		//��ֹ�, Ȥ�� ������ ����.
		for (int i = 0; i < _vCharacter.size(); i++)
		{
			if (_vCharacter[i]->getPosX() == MAPDATA->getPickI() && _vCharacter[i]->getPosY() == MAPDATA->getPickJ())
			{
				//_selectedChara = _vCharacter[i];
				_charaStateName = _vCharacter[i]->getName();
				_charaStateLevel = _vCharacter[i]->getStatus().lv;

				_hpBar->setGauge(_vCharacter[i]->getStatus().hp, _vCharacter[i]->getStatus().maxHp);
				_mpBar->setGauge(_vCharacter[i]->getStatus().mp, _vCharacter[i]->getStatus().maxMp);

				_isShowStateWindow = true;
				return;
			}
		}

		for (int i = 0; i < _vMonster.size(); i++)
		{
			if (_vMonster[i]->getPosX() == MAPDATA->getPickI() && _vMonster[i]->getPosY() == MAPDATA->getPickJ())
			{
				//_selectedMonster = _vMonster[i];
				_charaStateName = _vMonster[i]->getName();
				_charaStateLevel = _vMonster[i]->getMStatus().lv;

				_hpBar->setGauge(_vMonster[i]->getMStatus().hp, _vMonster[i]->getMStatus().maxHp);
				_mpBar->setGauge(_vMonster[i]->getMStatus().mp, _vMonster[i]->getMStatus().maxMp);

				_isShowStateWindow = true;
				return;
			}
		}
	}
	else
	{
		_isShowStateWindow = false;
	}
}

void stageScene::stageSave()
{
	DATABASE->saveSlot(UIMANAGER->getSaveSlot());//�������� ��ȣ ����

	string charaFileName = "ini/����" + to_string(UIMANAGER->getSaveSlot()) + "ĳ����";
	DATABASE->clearData(charaFileName.c_str());
	DATABASE->saveCharaData(charaFileName.c_str(), _vCharacter);

	string monsterFileName = "ini/����" + to_string(UIMANAGER->getSaveSlot()) + "����";
	DATABASE->clearData(monsterFileName.c_str());
	DATABASE->saveMonsterData(monsterFileName.c_str(), _vMonster);
}

void stageScene::stageLoad()
{
	_vCharacter.clear();
	_vMonster.clear();

	DATABASE->loadSlot(UIMANAGER->getSaveSlot());
	MAPDATA->loadMap(MAPDATA->getStageNumber());

	string charaFileName = "ini/����" + to_string(UIMANAGER->getSaveSlot()) + "ĳ����";
	_vCharacter = DATABASE->loadCharaData(charaFileName.c_str(), false);

	string monsterFileName = "ini/����" + to_string(UIMANAGER->getSaveSlot()) + "����";
	_vMonster = DATABASE->loadMonsterData(monsterFileName.c_str());

	_selectedChara = nullptr;
	_selectedMonster = nullptr;
}

void stageScene::stageInitialize()
{
	_vCharacter.clear();
	_vMonster.clear();

	MAPDATA->loadMap(MAPDATA->getStageNumber());

	string charaFileName = "ini/��������" + to_string(MAPDATA->getStageNumber()) + "ĳ����";
	_vCharacter = DATABASE->loadCharaData(charaFileName.c_str(), true);

	string monsterFileName = "ini/��������" + to_string(MAPDATA->getStageNumber()) + "����";
	_vMonster = DATABASE->loadMonsterData(monsterFileName.c_str(), true);

	_selectedChara = nullptr;
	_selectedMonster = nullptr;
}

void stageScene::WinLose()
{
	//���� �����Ŵ. �¸�!
	if (_vMonster.size() == 0 && STATEMANAGER->getState() == B_NONE)
	{
		_isVictory = true;
	}

	for (int i = 0; i < _vCharacter.size(); i++)
	{
		if (_vCharacter[i]->getState() == C_STUN)
		{
			_isDefeat = true;

		}
		else
		{
			_isDefeat = false;

			break;
		}
	}

	if (_dark == false)
	{
		_alpha -= 5;
		if (_alpha < 0)
		{
			_alpha = 0;
		}
	}
	else
	{
		_alpha += 1;
		if (_alpha > 255)
		{
			_alpha = 255;
			_isSceneChange = true;
		}
	}

	if (_isVictory)
	{
		_VictoryAlpha += 5;
		if (_VictoryAlpha > 255)
		{
			_VictoryAlpha = 255;

			_deleyCount++;
			if (_deleyCount > 100)
			{
				_dark = true;
			}
		}
	}

	if (_isDefeat)
	{
		_dark = true;
	}

	if (_isSceneChange)
	{
		if (_isVictory)
		{
			for (int i = 0; i < _vCharacter.size(); i++)
			{
				switch (_vCharacter[i]->getCName())
				{
				case N_KARIN:
					CHARADATA->getKarinLv() = _vCharacter[i]->getStatus().lv;
					CHARADATA->getKarinExp() = _vCharacter[i]->getStatus().Exp;
					break;

				case N_ARIS:
					CHARADATA->getArisLv() = _vCharacter[i]->getStatus().lv;
					CHARADATA->getArisExp() = _vCharacter[i]->getStatus().Exp;
					break;

				case N_AL:
					CHARADATA->getAlLv() = _vCharacter[i]->getStatus().lv;
					CHARADATA->getAlExp() = _vCharacter[i]->getStatus().Exp;
					break;

				default:
					break;
				}
			}


			ENDINGMANAGER->getStageClear()[MAPDATA->getStageNumber() - 1] = true;
			SCENEMANAGER->changeScene("����");
		}
		else if (_isDefeat)
		{
			SCENEMANAGER->changeScene("���ӿ���");
		}
	}

}

bool stageScene::gainExp()
{
	bool isGainExp = true;
	if (_selectedChara->getStatus().Exp < _totalExp)
	{
		_selectedChara->getStatus().Exp++;
		if (_selectedChara->getStatus().Exp >= 100)
		{
			_isLvUp = true;
			_totalExp -= 100;
			_selectedChara->getStatus().Exp -= 100;
		}
		isGainExp = true;
	}
	else
	{
		_deleyCount++;
		if (_deleyCount > 100)
		{
			_deleyCount = 0;
			_selectedChara->getStatus().Exp = _totalExp;
			isGainExp = false;
		}
	}

	_ExpBar->setGauge(_selectedChara->getStatus().Exp * 3, 300);

	return isGainExp;
}
