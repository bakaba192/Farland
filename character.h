#pragma once
#include "gameNode.h"
#include "CharacterAttribute.h"
#include "F_Skill.h"

class character : public gameNode
{
private:
	F_Skill* _Fskill;
	
	vector<F_Skill*> _vSkill;

	F_Skill* _selectedSkill;

	tagCharaStatus _status;

	charaState _state;
	charaState _preState;

	CharaName _cName;				//����Ÿ�� �̸�.

	string _charaName;				//��Ʈ�� ����

	int _indexX;					//Ÿ�ϻ��� ��ġ. i, j
	int _indexY;

	int _tempX;						//ĳ���Ͱ� �Ͻ������� ǥ�õ� ��ġ�� x y��
	int _tempY;

	int _tempForward;				//�ӽ������� ĳ���Ͱ� ���� ����

	int _moveForward;

	bool _moveOn;

	int _moveCount;					//�̵��� ���������� ã�� ī����
	int _jumpCount;					//�����̵��� ����� ī����

	


	vector<POINT> _way;				//������ ��� a��Ÿ�˰����� ��ȯ�� ������. ������ ��� �� WAY�� �����ϴ�	

	RECT _MoveRc;

	POINT _MovePoint;

	POINT _targetPoint;

	int _repeatCount;				//��� �ݺ��� ���ΰ�?

	int _numberFrame;
	int _numberCount;
	int _numberUpUp;

	int hund;
	int ten;
	int one;

	bool isOnPrintDemage;
	bool _isHeal;



public:
	HRESULT init(int x, int y, CharaName name, int lv);
	void release(void);
	void update(void);
	void render(void);

	void setPos(int i, int j) { _indexX = i, _indexY = j; }

	int& getPosX() { return _indexX; }
	int& getPosY() { return _indexY; }

	void setForward(int i) { _status.forward = i; }

	void setTempPos(int i, int j) { _tempX = i, _tempY = j; }

	int getTempPosX() { return _tempX; }
	int getTempPosY() { return _tempY; }

	void setTempForward(int i) { _tempForward = i; }
	int getTempForward() { return _tempForward; }

	void setState(int state) { _state = (charaState)state; }
	charaState& getState() { return _state; }

	void behaviorByState();//���°��� ���� �ൿ

	//���� ���� ���º�ȭ
	void showCharaByState();

	inline tagCharaStatus& getStatus() { return _status; }

	void moveToWay();
	void jumpUp();
	void jumpDown();

	bool printDemage(int Demage, bool isHeal = false);

	void DemageRender();

	vector<POINT> getWayStack() { return _way; }// 1 -1 ��  0 1 �� 0 0 

	void setWayStack(vector<POINT>& way){ _way = way; }
	
	vector<F_Skill*>& getVSkill() { return _vSkill; }

	F_Skill* getSelectedSkill() { return _selectedSkill; }

	void setSelectedSkill(F_Skill* FS) { _selectedSkill = FS; }

	CharaName& getCName() { return _cName; }

	string& getName() { return _charaName; }

	RECT getMoveRc() { return _MoveRc; }

	character() {};
	~character() {};
};