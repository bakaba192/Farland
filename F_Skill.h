#pragma once
#include "gameNode.h"

struct tagSkill { //��ų�� ������ �����ֱ⸸ �Ѵ�.
	
	bool isShow;

	int indexX;//������ġ
	int indexY;//������ġ

	int skillCount;
	int frameX;
	int frameY;

};

class F_Skill : public gameNode
{
private:
	string _name;

	int _skillRange;//��Ÿ�
	int _skillBounds;//ȿ�¹���(0~3)����?

	tagSkill _data[13]; //0~2����
	//���� ���ÿ� �������� ������ �ϳ��� ���������� ������ �� �ٸ���.

	

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
	//��ų ��Ŀ���� ����

	//1. ��ų�� ���õȴ�. ĳ����-����Ƽ�彺ų = �� ��ų
	//2. ���õ� ��ų�� ������ ǥ�õȴ� ��ų ������ ��ų�� ���� �����Ǿ� �ִ�..
	//3. ǥ�õ� �������� �� ĳ���͸� �����Ѵ�.
	//4. �� ĳ�����ֺ��� Ÿ�� ���� ǥ��.
	//5. 
};

