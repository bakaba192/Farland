#pragma once
#include "gameNode.h"

// ===== ## [ 테스트씬 클래스 헤드 ] ## =====

//전처리기 이름변수 선언 - 땅과 하늘
#define ImgMaxSizeW		3000			//이미지 최대 가로크기


class testScene : public gameNode
{
private:
	
	//배경 이미지 관련
	image* _back_img;
	int _backMoveCount;
	image* _back_img01;

	//땅 이미지
	image* _ground_img;
	//땅 이미지 - 픽셀용
	image* _ground_pixel;

	//rgb
	int r, g, b;

public:
	//필수
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//생성자, 소멸자
	testScene()  {}
	~testScene() {}
};
