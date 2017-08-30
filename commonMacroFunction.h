#pragma once

//=================================================================================================
//	##	��ũ�� �Լ�	##	(�ʿ��� �Լ��� ������!!!)
//=================================================================================================

//���콺 ��ǥ
inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}


//�Ѽ� �׸���
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

//�Ѽ� �׸���(�ɼ� : ����, �� ����)
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY, COLORREF pen_RGB , int penWidth = 1,int penStyle = PS_SOLID)
{
	HPEN pen = CreatePen(penStyle, penWidth, pen_RGB);		//���� ���� : PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT
	HPEN oldPen = (HPEN)SelectObject(hdc, pen);
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
	SelectObject(hdc, oldPen);
	DeleteObject(pen);

}

//RECT �����
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

//RECT �߽����� �����
inline RECT RectMakeCP(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

//RECT �߽����� �����(for�� �ʼ�)
inline RECT RectArrayMCP(int startX, int startY, int width, int height, int distanceX, int distanceY, int lineNum, int forNum)
{
	RECT rc = RectMakeCP(startX + distanceX*(forNum % lineNum), startY + distanceY* (forNum / lineNum),  width, height);		
	return rc;
}

//�簢�� �׸��� (���ʱ��Լ� ���)
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

//Ÿ�� �׸��� (�ϸ����Լ� ���)
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//Ÿ�� ������ �߽����� �׸��� (�ϸ����Լ� ���)
inline void EllipseMakeCP(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}


//RECT�� �޾� �簢�� �׸���
inline void setRectangle(HDC hdc, RECT &rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}


//RECT�� �޾� �簢�� �׸���! (�ɼ�: ����)
inline void setRectangle(HDC hdc, RECT &rc, COLORREF RGB, bool On = false)
{
	HBRUSH brush = CreateSolidBrush(RGB);
	if (On == false)
	{
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
		SelectObject(hdc, oldBrush);
		
	}
	else
	{
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
		FillRect(hdc, &rc, brush);
	}
	DeleteObject(brush);
}

//RECT�� �޾� �簢�� �׸���! (�ɼ�: ����)
inline void setRectangle(HDC hdc, RECT &rc, COLORREF pen_RGB, COLORREF bru_RGB, int penWidth = 1, bool transparent = false, int penStyle = PS_SOLID)
{
	
	//����
	HPEN pen = CreatePen(penStyle, penWidth ,pen_RGB);		//���� ���� : PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT
	HBRUSH brush = CreateSolidBrush(bru_RGB);

	//����
	SelectObject(hdc, pen);
	//SelectObject(hdc, GetStockObject(NULL_PEN));
	SelectObject(hdc, brush);
	if(transparent == true) SelectObject(hdc, GetStockObject(NULL_BRUSH));

	//�簢�� �׸���
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	
	//����
	DeleteObject(brush);
	DeleteObject(pen);
}

//RECT�� �޾� �� �׸���
inline void setEllipse(HDC hdc, RECT &rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//RECT�� �޾� �� �׸���! (�ɼ�: ����)
inline void setEllipse(HDC hdc, RECT &rc, COLORREF RGB)
{
	HBRUSH brush = CreateSolidBrush(RGB);
	HBRUSH oldBrush= (HBRUSH)SelectObject(hdc, brush);
	SelectObject(hdc, GetStockObject(NULL_PEN));
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
	SelectObject(hdc, oldBrush);
	DeleteObject(brush);
}


//��Ʈ ũ�� �����ϱ�
inline void setFont(HDC hdc, int size, char* str, int startX, int startY, COLORREF RGB = RGB(0,0,0),  LPCTSTR fontKind = "����ü", INT bkMode = TRANSPARENT)
{

HFONT Font = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, fontKind);
HFONT oldFont = (HFONT)SelectObject(hdc, Font);
SetTextColor(hdc, RGB);				//���ڻ�
SetBkMode(hdc, bkMode);				//������ ����							
TextOut(hdc, startX, startY, str, strlen(str));
SelectObject(hdc, oldFont);
DeleteObject(Font);

//     int nHeight,						// ����
//     int nWidth,						// ��. 0�� �־��ָ� ���̿� �����
//     int nEscapement,					// ���� ��ü ����
//     int nOrientation,				// ���ؼ��� ������ �ְ� ���� ����
//     int fnWeight,					// ��Ʈ�� �β�
//     DWORD fdwItalic,					// ���Ÿ�
//     DWORD fdwUnderline,				// ����
//     DWORD fdwStrikeOut,				// ��Ҽ�
//     DWORD fdwCharSet,				// ĳ���� ��
//     DWORD fdwOutputPrecision,		// ���е�
//     DWORD fdwClipPrecision,			// ���е�
//     DWORD fdwQuality,				// ���е�
//     DWORD fdwPitchAndFamily,			// ���е�
//     LPCTSTR lpszFace					// �۲��̸�
}