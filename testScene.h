#pragma once
#include "gameNode.h"

// ===== ## [ �׽�Ʈ�� Ŭ���� ��� ] ## =====

//��ó���� �̸����� ���� - ���� �ϴ�
#define ImgMaxSizeW		3000			//�̹��� �ִ� ����ũ��


class testScene : public gameNode
{
private:
	
	//��� �̹��� ����
	image* _back_img;
	int _backMoveCount;
	image* _back_img01;

	//�� �̹���
	image* _ground_img;
	//�� �̹��� - �ȼ���
	image* _ground_pixel;

	//rgb
	int r, g, b;

public:
	//�ʼ�
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//������, �Ҹ���
	testScene()  {}
	~testScene() {}
};
