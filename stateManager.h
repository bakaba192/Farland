#pragma once
#include "singletonBase.h"

enum BState //전투 상태
{
	B_NONE = 0,				//선택되지 않음. ()
	B_SHOWPOPUPMENU,		//팝업메뉴 보여지는 중.
	B_SHOWSAVEMENU,
	B_SHOWLOADMENU,
	B_SHOWMOVERANGE,		//이동 거리 표시. (적이 근처에 있다면 공격 표시.)
	B_SHOWMELEEATTACK,		//이동 후 적이있다면 근접공격 (적이 근처에 있다면 공격 표시./ 제자리 선택시 셀렉트 포워드로 전환.)
	B_SHOWSKILLRANGE,		//스킬 사용시 타겟팅 범위 표시.
	B_SHOWSKILLBOUNDS,		//스킬 공격 적용 범위가 표시됨.
	B_SELECTFORWARD,		//이동 후 적이 없다면 방향 설정 
	B_ONMOVING,				//캐릭터가 이동중
	B_ONATTACK,				//캐릭터가 공격중
	B_ONSKILLATTACK,		//캐릭터가 스킬공격중
	B_PRINTDEMAGE,			//데미지 표시 중
	B_PRINTSKILLDEMAGE,		//스킬 데미지 표시 중//여러마리가 한번에 데미지 표시
	B_ONDEATH,				//적 사망 중
	B_GAINEXP,				//경험치 오르는 중
	B_WIN
};

class stateManager : public singletonBase<stateManager>
{
private:
	BState _state;
	string _selectedChara;//선택한(마우스커서가 올라간) 캐릭터의 이름을 저장.
	bool _myTurn;			//true 일때 플레이어의 턴

	bool _myTurnStart;	//이 값이 트루이면 모든 플레이어의 이동및 액션 상태를 true로 초기화한다.
	bool _enemyTurnStart; //이 값이 트루이면 모든 플레이어의 이동및 액션 상태를 true로 초기화한다.

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