#include "stdafx.h"
#include "F_loadingScene.h"


HRESULT F_loadingScene::init(void)
{
	//�ε�Ŭ���� ���� �� �ʱ�ȭ
	_loading = new loading;
	_loading->init();

	//�̹��� �� ���� �ε�
	this->loadingImage();
	this->loadingSound();

	_sceneChange = false;
	_alpha = 0;

	return S_OK;
}

void F_loadingScene::release(void)
{
	//�ε�ȭ�� ����
	SAFE_DELETE(_loading);
}

void F_loadingScene::update(void)
{
	//cout << "�ε� ���� ���?" << endl;
	//�ε�Ŭ���� ������Ʈ
	_loading->update();

	if (_loading->loadingDone())
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			//�ε��� �Ϸ� ������ ����������
			_sceneChange = true;
		}
	}

	if (_sceneChange)
	{
		_alpha += 5;
	}

	if (_alpha == 255)
	{
		SCENEMANAGER->changeScene("����");
	}
}

void F_loadingScene::render(void)
{
	_loading->render();

}

//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
void F_loadingScene::loadingImage(void)
{
	//��׶���
	//========================================================================================================
	_loading->loadImage("���1", "image/�ý���/���1.bmp", 640, 480);
	_loading->loadImage("���2", "image/�ý���/���2.bmp", 640, 480);
	_loading->loadImage("���3", "image/�ý���/���3.bmp", 640, 480);

	_loading->loadImage("����", "image/�ý���/town00.bmp", WINSIZEX, WINSIZEY);

	_loading->loadImage("���ӿ���", "image/�ý���/���ӿ���.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("����", "image/�ý���/����.bmp", WINSIZEX, 345);

	_loading->loadImage("����ȭ��", WINSIZEX, WINSIZEY);

	//�ý��� UI
	//========================================================================================================
	_loading->loadImage("����â", "image/�ý���/����â.bmp", 452, 102, true, RGB(255, 0, 255));
	_loading->loadImage("����â_�̵�", "image/�ý���/�̵�����.bmp", 452, 102, true, RGB(255, 0, 255));
	_loading->loadImage("����â_��ų", "image/�ý���/��ų����.bmp", 452, 102, true, RGB(255, 0, 255));
	_loading->loadImage("����â_����", "image/�ý���/������ ����.bmp", 452, 102, true, RGB(255, 0, 255));
	_loading->loadImage("����â_��", "image/�ý���/������ ����.bmp", 452, 102, true, RGB(255, 0, 255));
	_loading->loadImage("����â_����", "image/�ý���/���̺� ����.bmp", 452, 102, true, RGB(255, 0, 255));
	_loading->loadImage("����â_�ε�", "image/�ý���/�ε� ����.bmp", 452, 102, true, RGB(255, 0, 255));

	_loading->loadImage("���̺�â", "image/�ý���/���̺�â.bmp", 452, 102, true, RGB(255, 0, 255));
	_loading->loadImage("�ε�â", "image/�ý���/�ε�â.bmp", 452, 102, true, RGB(255, 0, 255));

	_loading->loadImage("���̺� ����2", "image/�ý���/���̺� ����2.bmp", 70, 70, true, RGB(255, 0, 255));
	_loading->loadImage("�ε� ����2", "image/�ý���/�ε� ����2.bmp", 70, 70, true, RGB(255, 0, 255));

	_loading->loadImage("����ġâ", "image/�ý���/����ġâ.bmp", 360, 100, true, RGB(255, 0, 255));

	_loading->loadImage("UI���", "image/�ý���/UI��׶���.bmp", 200, 480);
	_loading->loadImage("���̺�", "image/�ý���/���̺�.bmp", 64, 64, true, RGB(255, 0, 255));
	_loading->loadImage("�ε�", "image/�ý���/�ε�.bmp", 64, 64, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ȭ��ǥ", "image/�ý���/ȭ��ǥ.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ȭ��ǥ2", "image/�ý���/ȭ��ǥ2.bmp", 64, 128, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ǥ����", "image/�ý���/ǥ����.bmp", 128, 256, 1, 4, true, RGB(255, 0, 255));
	_loading->loadImage("�׵θ�", "image/�ý���/�׵θ�2.bmp", 240, 480, true, RGB(255, 0, 255));
	_loading->loadImage("�¸�", "image/�ý���/�¸�.bmp", 500, 148, true, RGB(255, 0, 255));

	//�ý���
	//========================================================================================================
	_loading->loadFrameImage("����", "image/�ý���/����.bmp", 96, 384, 1, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����", "image/�ý���/����.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("������Ʈ1", "image/�ý���/������Ʈ1.bmp", 128, 320, 8, 10, true, RGB(255, 0, 255));
	_loading->loadFrameImage("������Ʈ2", "image/�ý���/������Ʈ2.bmp", 128, 320, 8, 10, true, RGB(255, 0, 255));
	_loading->loadFrameImage("������Ʈ3", "image/�ý���/������Ʈ3.bmp", 32, 640, 1, 10, true, RGB(255, 0, 255));
	_loading->loadImage("ü�¹�_��", "image/�ý���/ü�¹�_��1.bmp", 150, 12);
	_loading->loadImage("ü�¹�_��", "image/�ý���/ü�¹�_��1.bmp", 150, 12);
	_loading->loadImage("������_��", "image/�ý���/������_��.bmp", 150, 12);
	_loading->loadImage("������_��", "image/�ý���/������_��.bmp", 150, 12);
	_loading->loadImage("�����_��", "image/�ý���/�����_��.bmp", 800, 24);
	_loading->loadImage("�����_��", "image/�ý���/�����_��.bmp", 800, 24);
	_loading->loadImage("����ġ��_��", "image/�ý���/����ġ��_��.bmp", 300, 12);
	_loading->loadImage("����ġ��_��", "image/�ý���/����ġ��_��.bmp", 300, 12);
	_loading->loadImage("�׸���", "image/�ý���/�׸���.bmp", 96, 96, true, RGB(255, 0, 255));
	_loading->loadImage("ĳ����_����â", "image/�ý���/ĳ���� ����â.bmp", 300, 100, true, RGB(255, 0, 255));
	_loading->loadImage("�˸�_â", "image/�ý���/�˸� â.bmp", 100, 100, true, RGB(255, 0, 255));


	//��ų
	//========================================================================================================
	_loading->loadFrameImage("�÷��ӹ���Ʈ", "image/��ų/�÷��ӹ���Ʈ.bmp", 2380, 192, 17, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��1", "image/��ų/��_����.bmp", 192, 384, 2, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��2", "image/��ų/��_���.bmp", 192, 768, 2, 8, true, RGB(255, 0, 255));



	//���� �̹���
	//========================================================================================================
	//�θ�
	_loading->loadFrameImage("�θ�_���", "image/����/�θ�/�θ� ���.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("�θ�_�ǰ�", "image/����/�θ�/�θ� �ǰ�.bmp", 384, 192, 4, 2, true, RGB(255, 0, 255));

	_loading->loadFrameImage("�θ�_���", "image/����/�θ�/�θ� ���.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�θ�_�غ�", "image/����/�θ�/�θ� ���.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("�θ�_�̵�", "image/����/�θ�/�θ� �̵�.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("�θ�_����", "image/����/�θ�/�θ� ����.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("�θ�_����", "image/����/�θ�/�θ� ����.bmp", 384, 1152, 4, 12, true, RGB(255, 0, 255));
	//�����
	//========================================================================================================

	_loading->loadFrameImage("�����_���", "image/����/�����/����� ���.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("�����_�ǰ�", "image/����/�����/����� �ǰ�.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("�����_���", "image/����/�����/����� ���.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("�����_�غ�", "image/����/�����/����� ���.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("�����_�̵�", "image/����/�����/����� �̵�.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("�����_����", "image/����/�����/����� ����.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("�����_����", "image/����/�����/����� ����.bmp", 384, 960, 4, 10, true, RGB(255, 0, 255));


	//ĳ���� �̹���
	//=======================================================================================================
	//ī��
	_loading->loadFrameImage("ī��_�ǰ�", "image/ĳ����/ī��/ī�� �ǰ�.bmp", 384, 192, 4, 2, true, RGB(255, 0, 255));

	_loading->loadFrameImage("ī��_���", "image/ĳ����/ī��/ī�� ���.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ī��_����", "image/ĳ����/ī��/ī�� ����.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ī��_ȸ��", "image/ĳ����/ī��/ī�� ȸ��.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ī��_����", "image/ĳ����/ī��/ī�� ����.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ī��_����", "image/ĳ����/ī��/ī�� ����.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ī��_��ȭ", "image/ĳ����/ī��/ī�� ��ȭ.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("ī��_�̵�", "image/ĳ����/ī��/ī�� �̵�.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ī��_����", "image/ĳ����/ī��/ī�� ����.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ī��_�غ�", "image/ĳ����/ī��/ī�� �غ�.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ī��_��ų1", "image/ĳ����/ī��/ī�� ��ų1.bmp", 384, 288, 4, 3, true, RGB(255, 0, 255));

	_loading->loadFrameImage("ī��_��ų2", "image/ĳ����/ī��/ī�� ��ų2.bmp", 384, 288, 4, 3, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ī��_��ų3", "image/ĳ����/ī��/ī�� ��ų3.bmp", 384, 480, 4, 5, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ī��_����", "image/ĳ����/ī��/ī�� ����.bmp", 384, 576, 4, 6, true, RGB(255, 0, 255));

	//�Ƹ���				  
	_loading->loadFrameImage("�Ƹ���_���", "image/ĳ����/�Ƹ���/�Ƹ��� ���.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("�Ƹ���_����", "image/ĳ����/�Ƹ���/�Ƹ��� ����.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�Ƹ���_�ǰ�", "image/ĳ����/�Ƹ���/�Ƹ��� �ǰ�.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("�Ƹ���_�̵�", "image/ĳ����/�Ƹ���/�Ƹ��� �̵�.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�Ƹ���_����", "image/ĳ����/�Ƹ���/�Ƹ��� ����.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�Ƹ���_�غ�", "image/ĳ����/�Ƹ���/�Ƹ��� �غ�.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�Ƹ���_��ų1", "image/ĳ����/�Ƹ���/�Ƹ��� ��ų1.bmp", 384, 1056, 4, 11, true, RGB(255, 0, 255));

	_loading->loadFrameImage("�Ƹ���_����", "image/ĳ����/�Ƹ���/�Ƹ��� ����.bmp", 384, 576, 4, 6, true, RGB(255, 0, 255));

	//��
	_loading->loadFrameImage("��_���", "image/ĳ����/��/�� ���.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("��_����", "image/ĳ����/��/�� ����.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��_�ǰ�", "image/ĳ����/��/�� �ǰ�.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("��_����", "image/ĳ����/��/�� ����.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("��_�غ�", "image/ĳ����/��/�� �غ�.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��_�̵�", "image/ĳ����/��/�� �̵�.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��_����", "image/ĳ����/��/�� ����.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��_��ų1", "image/ĳ����/��/�� ��ų1.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("��_����", "image/ĳ����/��/�� ����.bmp", 384, 576, 4, 6, true, RGB(255, 0, 255));

	//���̹���
	//=======================================================================================================
	_loading->loadImage("���", "image/���.bmp", 64, 32, true, RGB(255, 0, 255));
	_loading->loadImage("���2", "image/���2.bmp", 64, 32, true, RGB(255, 0, 255));
	_loading->loadImage("���3", "image/���3.bmp", 64, 32, true, RGB(255, 0, 255));
	_loading->loadImage("���4", "image/���4.bmp", 64, 32, true, RGB(255, 0, 255));
	_loading->loadImage("����", "image/TileSelectTrue2.bmp", 64, 32, true, RGB(255, 0, 255));
	_loading->loadImage("����2", "image/TileSelectFalse2.bmp", 64, 32, true, RGB(255, 0, 255));
	_loading->loadImage("����3", "image/TileSelectTrue.bmp", 64, 32, true, RGB(255, 0, 255));
	_loading->loadImage("����4", "image/TileSelectFalse.bmp", 64, 32, true, RGB(255, 0, 255));

	_loading->loadFrameImage("Ÿ��1", "image/GrassTile.bmp", 320, 192, 5, 6, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��2", "image/SnowTile.bmp", 1120, 48, 16, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("������Ʈ", "image/������Ʈ.bmp", 640, 128, 10, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("������Ʈ2", "image/������Ʈ2.bmp", 448, 140, 7, 1, true, RGB(255, 0, 255));

}

void F_loadingScene::loadingSound(void)
{

}
