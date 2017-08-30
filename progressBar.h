#pragma once
#include "gameNode.h"



class progressBar : public gameNode
{
private:
	RECT _rcProgress;			//체력바 렉트
	int _x, _y;					//체력바 위치 좌표
	float _width;				//체력바 가로길이
	float _height;				//체력바 세로길이 (나중에 필요하면 수정하기)

	image* _progressBarFront;	//체력바 앞에 있는 이미지
	image* _progressBarBack;	//체력바 뒤에 있는 이미지

public:
	//체력바 초기화(체력바 앞이미지키, 체력바 뒤이미지키, x, y, 가로길이, 세로길이)
	HRESULT init(char* frontImageKey, char* backImageKey, int x, int y, int width, int height);
	void release(void);
	void update(void);
	void render(void);

	//체력바 게이지 세팅하기
	void setGauge(float currentHp, float maxHp);

	//체력바 위치좌표 세팅하기(셋터)
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
	//체력바 렉터 겟터
	RECT getRect(void) { return _rcProgress; }


	progressBar() {}
	~progressBar() {}
};

