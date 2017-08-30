#pragma once
#include "singletonBase.h"

enum BState //���� ����
{
	B_NONE = 0,				//���õ��� ����. ()
	B_SHOWPOPUPMENU,		//�˾��޴� �������� ��.
	B_SHOWSAVEMENU,
	B_SHOWLOADMENU,
	B_SHOWMOVERANGE,		//�̵� �Ÿ� ǥ��. (���� ��ó�� �ִٸ� ���� ǥ��.)
	B_SHOWMELEEATTACK,		//�̵� �� �����ִٸ� �������� (���� ��ó�� �ִٸ� ���� ǥ��./ ���ڸ� ���ý� ����Ʈ ������� ��ȯ.)
	B_SHOWSKILLRANGE,		//��ų ���� Ÿ���� ���� ǥ��.
	B_SHOWSKILLBOUNDS,		//��ų ���� ���� ������ ǥ�õ�.
	B_SELECTFORWARD,		//�̵� �� ���� ���ٸ� ���� ���� 
	B_ONMOVING,				//ĳ���Ͱ� �̵���
	B_ONATTACK,				//ĳ���Ͱ� ������
	B_ONSKILLATTACK,		//ĳ���Ͱ� ��ų������
	B_PRINTDEMAGE,			//������ ǥ�� ��
	B_PRINTSKILLDEMAGE,		//��ų ������ ǥ�� ��//���������� �ѹ��� ������ ǥ��
	B_ONDEATH,				//�� ��� ��
	B_GAINEXP,				//����ġ ������ ��
	B_WIN
};

class stateManager : public singletonBase<stateManager>
{
private:
	BState _state;
	string _selectedChara;//������(���콺Ŀ���� �ö�) ĳ������ �̸��� ����.
	bool _myTurn;			//true �϶� �÷��̾��� ��

	bool _myTurnStart;	//�� ���� Ʈ���̸� ��� �÷��̾��� �̵��� �׼� ���¸� true�� �ʱ�ȭ�Ѵ�.
	bool _enemyTurnStart; //�� ���� Ʈ���̸� ��� �÷��̾��� �̵��� �׼� ���¸� true�� �ʱ�ȭ�Ѵ�.

public:
	stateManager() {};
	~stateManager() {};

	HRESULT init(void);
	void release(void);

	void setState(BState state) { _state = state; }
	BState getState() { return _state; }

	void selectChara() { _selectedChara; }
	string getSelectedChara() { return _selectedChara; }

	bool& getMyTurn() { return _myTurn; }
	bool& getMyTurnStart() { return _myTurnStart; }
	bool& getEnemyTurnStart() { return _enemyTurnStart; }
};