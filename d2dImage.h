#pragma once

//=================================================================================================
//	##	�̹��� [ Image ] (���)	##
//=================================================================================================

//�����̼� ��ǥ��
enum ROTATION_CP
{
	RCP_CENTER,
	RCP_LEFT,
	RCP_RIGHT,
	RCP_TOP,
	RCP_BOTTOM,
	RCP_LT,
	RCP_RT,
	RCP_LB,
	RCP_RB,
	RCP_NONE

};

//�����ӿ�
enum TELESCOPIC_DIRECTION
{
	TD_CENTER,
	TD_UP,
	TD_DOWN,

};


//�����̼� ��ǥ��
#define RCP_CENTER		RCP_CENTER
#define RCP_LEFT		RCP_LEFT
#define RCP_RIGHT		RCP_RIGHT
#define RCP_TOP			RCP_TOP
#define RCP_BOTTOM		RCP_BOTTOM
#define RCP_LT			RCP_LT
#define RCP_RT			RCP_RT
#define RCP_LB			RCP_LB
#define RCP_RB			RCP_RB
#define RCP_NONE		RCP_NONE

#define TD_CENTER		TD_CENTER
#define TD_UP			TD_UP
#define TD_DOWN			TD_DOWN

class d2dImage
{
public:
	typedef struct tagD2D
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

		D2D1_RECT_F RectF;			//��Ʈ, �⺻
		D2D1_RECT_F FrameRectF;		//�����ӿ� ��Ʈ

		ID2D1DCRenderTarget* pDCRT;			//����Ÿ��
		ID2D1Bitmap* pD2DBitmap = NULL;		//��Ʈ��

		//�ʱ�ȭ
		tagD2D()
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

			ID2D1DCRenderTarget* pDCRT = NULL;
			ID2D1Bitmap* pD2DBitmap = NULL;
		}

	}D2D_INFO, *LPD2D_INFO;

private:
	LPD2D_INFO		_d2dInfo;		//GDI����
	//CHAR*			_fileName;		//�̹��� �̸�

	//DC�� �׸���� ����
	D2D1_RENDER_TARGET_PROPERTIES propertiesDC;

	//D2D ���丮 ����
	ID2D1Factory* pD2DFactory;

	//���� Ÿ�� ���� ->���� Ÿ���� GPU�� �޸� �Ҵ��ϴ� ��[ d2d����(GDI�� ���� ����) ]
	//ID2D1HwndRenderTarget* pRenderTarget = NULL;	//���� �ϰ� �Ⱦ�����!!

	//DC�� ���� Ÿ�� ���� ->GDI�� DC�� ���� ����ϱ� ����(�ٽ�)
	//ID2D1DCRenderTarget* pDCRT = NULL;

	//��Ʈ�� ���� Ÿ�� ����->��Ʈ�� �����
	//ID2D1BitmapRenderTarget* pBitmapRT;

	//d2d�� ��Ʈ�� ����
	ID2D1Bitmap* pD2DBitmap;

	//���� ������ ����-> �ε��� �̹����� ��Ʈ������ ��ȯ�ϱ� ���� ��
	IWICFormatConverter* pWicBitmap;


private:
	//wic���丮 ����
	IWICImagingFactory* pWicFactory;
	//������ ���ڴ� ����
	IWICBitmapFrameDecode *pWicFrameDecoder;
	//�̹��� ���ڴ� ����
	IWICBitmapDecoder* pWicImageDecoder;



public:

	//=================================================================================================
	//	##	[ �ʱ�ȭ ]	##
	//=================================================================================================


	//�Ϲ� �ʱ�ȭ
	HRESULT init(const WCHAR* fileName);
	//�Ϲ� �ʱ�ȭ - ��ġ��ǥ
	HRESULT init(const WCHAR * fileName, float x, float y);

	//������ �ʱ�ȭ
	HRESULT frameInit(const WCHAR * fileName, int maxFrameX, int maxFrameY);

	//����
	void release(void);




	//=================================================================================================
	//	## [ �Ϲ� ���� ] ##
	//=================================================================================================

	//����
	void render(HDC hdc, float alpha = 1.0);
	void render(HDC hdc, float destX, float destY, float alpha = 1.0);



	//=================================================================================================
	// ## [ ȸ�� ���� ] ##
	//=================================================================================================

	//�⺻��
	void rotationRender(HDC hdc, float destX, float destY, float angle, ROTATION_CP RCP = RCP_CENTER, float alpha = 1.0);
	//��ǥ�� ������
	void rotationRender(HDC hdc, float destX, float destY, float rotationX, float rotationY, float angle, ROTATION_CP RCP = RCP_CENTER, float alpha = 1.0);

	//=================================================================================================
	// ## [ ������ ���� ] ##
	//=================================================================================================

	//=================================================================================================
	// ## [ ������ ���� ] ##
	//=================================================================================================

	void frameRender(HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float alpha = 1.0);
	void rFrameRender(HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float angle, ROTATION_CP RCP = RCP_CENTER, float alpha = 1.0);
	void rFrameRender(HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float rotationX, float rotationY, float angle, ROTATION_CP RCP = RCP_CENTER, float alpha = 1.0);



	//void frameRender(HDC hdc, int destX, int destY, );


	//=================================================================================================
	// ## [ Ư�� ���� ] ##
	//=================================================================================================
	void xFrameRender(HDC hdc, float destX, float destY, float lengthY, int currentFrameX, float angle, TELESCOPIC_DIRECTION TD = TD_CENTER, ROTATION_CP RCP = RCP_CENTER, float rotationX = 0, float rotationY = 0, float alpha = 1.0);
	//void sFrameRender(HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float rotationX, float rotationY, float angle, ROTATION_CP RCP = RCP_CENTER, float alpha = 1.0);



	//d2d �����
	void createD2D(const WCHAR * fileName);
	// 



	d2dImage();
	~d2dImage();
};

