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

	CharaName _cName;				//에넘타입 이름.

	string _charaName;				//스트링 네임

	int _indexX;					//타일상의 위치. i, j
	int _indexY;

	int _tempX;						//캐릭터가 일시적으로 표시될 위치의 x y값
	int _tempY;

	int _tempForward;				//임시적으로 캐릭터가 가질 방향

	int _moveForward;

	bool _moveOn;

	int _moveCount;					//이동의 절반지점을 찾는 카운터
	int _jumpCount;					//점프이동에 사용할 카운터

	


	vector<POINT> _way;				//진행할 경로 a스타알고리즘의 반환을 저장함. 몬스터의 경우 이 WAY를 저장하는	

	RECT _MoveRc;

	POINT _MovePoint;

	POINT _targetPoint;

	int _repeatCount;				//몇번 반복할 것인가?

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

	void behaviorByState();//상태값에 따른 행동

	//값에 따른 상태변화
	void showCharaByState();

	inline tagCharaStatus& getStatus() { return _status; }

	void moveToWay();
	void jumpUp();
	void jumpDown();

	bool printDemage(int Demage, bool isHeal = false);

	void DemageRender();

	vector<POINT> getWayStack() { return _way; }// 1 -1 앞  0 1 뒤 0 0 

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