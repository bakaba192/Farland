#pragma once

//=================================================================================================
//	##	GDI+ �̹��� [ gdiPlusImage ] (���)	##
//=================================================================================================

class gdipImage
{
public:
	typedef struct tagGDI
	{

		HDC			hMemDC;			//�޸� DC
		HBITMAP		hBit;			//��Ʈ��
		HBITMAP		hOBit;			//�õ��Ʈ��
		float		x;				//�̹��� x��ǥ(����Ʈ)
		float		y;				//�̹��� y��ǥ(ž)
		int			width;			//�̹��� ����ũ��
		int			height;			//�̹��� ����ũ��
		int			currentFrameX;	//���������� x��ǥ
		int			currentFrameY;	//���������� y��ǥ
		int			maxFrameX;		//�ִ������� x����
		int			maxFrameY;		//�ִ������� y����
		int			frameWidth;		//1������ ����ũ��
		int			frameHeight;	//1������ ����ũ��

		//�ʱ�ȭ
		tagGDI()
		{
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
		}

	}GDI_INFO, *LPGDI_INFO;

private:
	LPGDI_INFO		_gdiInfo;		//GDI����
	CHAR*			_fileName;		//�̹��� �̸�
	Graphics*		_gdi;
	Graphics*		_gdiRender;
	Image*			_gdiImg;

public:
	//�ʱ�ȭ
	HRESULT init(int maxFrameX, int maxFrameY);
	HRESULT init(const WCHAR* fileName, int maxFrameX, int maxFrameY);
	//����
	void release(void);

	//=================================================================================================
	//	## [ GDI+������ ���� ] ##
	//=================================================================================================

	//������ ����(������ ���� - ���ϴ� ������ ����)
	void gdiFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	gdipImage();
	~gdipImage();
};







