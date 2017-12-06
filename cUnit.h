#pragma once
#include "gameNode.h"

class cUnitState;
class cUnit : public gameNode
{
private:
	SYNTHESIZE(int, m_PosX, PosX);
	SYNTHESIZE(int, m_PosY, PosY);

	SYNTHESIZE(int, m_CurHp, CurHp);
	SYNTHESIZE(int, m_MaxHp, MaxHp);

	SYNTHESIZE(int, m_CurMp, CurMp);
	SYNTHESIZE(int, m_MaxMp, MaxMp);



private:
	SYNTHESIZE(cUnitState*, m_State, State);

public:
	cUnit();
	~cUnit();

	HRESULT init();
	void update();
	void render();
	void release();
};