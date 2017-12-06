#pragma once
class cUnit;
//유닛의 특정한 동작을 설정할 수 있다.
//카린은 플레임버스트 스킬사용 이라는 상태를 가진다고 가정하면
//아리스는 치유스킬 사용이라는 상태를 가지게된다.

//이 모든 행동은 init, update, render사이에서 일어나게 될것임.

class cUnitState
{
private:
	cUnit* unit;

public:
	cUnitState(cUnit* unit);
	virtual ~cUnitState();

	virtual void init();
	virtual void update();
	virtual void render();
	virtual void release();
};

