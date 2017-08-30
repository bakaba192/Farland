#pragma once
#include "gameNode.h"

//==================================================================
//		## stateBar ## (���¹� = ü�¹�)
//==================================================================

enum enumBarState
{
	BAR_RIGHT = 0,
	BAR_LEFT,
	BAR_UP,
};

#define BAR_RIGHT BAR_RIGHT
#define BAR_LEFT BAR_LEFT
#define BAR_UP BAR_UP


class stateBar : public gameNode
{
private:
	RECT _rcProgress;			//ü�¹� ��Ʈ
	int _x, _y;					//ü�¹� ��ġ ��ǥ
	float _width;				//ü�¹� ���α���
	float _height;				//ü�¹� ���α��� (���߿� �ʿ��ϸ� �����ϱ�)

	float _maxWidth;

	float _cutStartX;			//�ڸ��� ������ġX
	float _cutStartY;			//�ڸ��� ������ġY

	image* _progressBarFront;	//ü�¹� �տ� �ִ� �̹���
	image* _progressBarBack;	//ü�¹� �ڿ� �ִ� �̹���

public:
	//ü�¹� �ʱ�ȭ(ü�¹� ���̹���Ű, ü�¹� ���̹���Ű, x, y)
	HRESULT init(char * frontImageKey, char * backImageKey, int x, int y);
	void release(void);
	void update(void);
	void render(void);

	//ü�¹� ������ �����ϱ�
	void setGauge(float currentNumS, float maxNum, enumBarState barState = BAR_RIGHT);

	//ü�¹� ��ġ��ǥ �����ϱ�(����)
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
	//ü�¹� ���� ����
	RECT getRect(void) { return _rcProgress; }



	stateBar() {};
	~stateBar() {};
};

