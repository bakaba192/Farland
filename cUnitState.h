#pragma once
class cUnit;
//������ Ư���� ������ ������ �� �ִ�.
//ī���� �÷��ӹ���Ʈ ��ų��� �̶�� ���¸� �����ٰ� �����ϸ�
//�Ƹ����� ġ����ų ����̶�� ���¸� �����Եȴ�.

//�� ��� �ൿ�� init, update, render���̿��� �Ͼ�� �ɰ���.

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

