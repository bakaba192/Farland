#pragma once
#include "gameNode.h"

struct tagSkill { //스킬은 오로지 보여주기만 한다.
	
	bool isShow;

	int indexX;//폭발위치
	int indexY;//폭발위치

	int skillCount;
	int frameX;
	int frameY;

};

class F_Skill : public gameNode
{
private:
	string _name;

	int _skillRange;//사거리
	int _skillBounds;//효력범위(0~3)정도?

	tagSkill _data[13]; //0~2범위
	//힐은 동시에 떨어지고 폭발은 하나씩 연쇄적으로 터진다 즉 다르다.

	

	int _power;

	int _drop;
	int _dropCount;

public:
	F_Skill() {};
	~F_Skill() {};

	HRESULT init(string name, int mAtk, int Bounds);//bound = chara.lv / 10;
	void release(void);
	void update(void);
	void render(void);



	tagSkill& getSkillData(int i) { return _data[i]; }

	void skillSetting(int x, int y );

	void showFireSkill();

	void startFire();

	int& getBound() { return _skillBounds; }
	int& getRange() { return _skillRange; }

	int getPower() { return _power; }
	//스킬 매커니즘 정리

	//1. 스킬이 선택된다. 캐릭터-셀렉티드스킬 = 요 스킬
	//2. 선택된 스킬의 범위가 표시된다 스킬 범위는 스킬에 따라서 고정되어 있다..
	//3. 표시된 범위안의 적 캐릭터를 선택한다.
	//4. 적 캐릭터주변에 타격 범위 표시.
	//5. 
};

