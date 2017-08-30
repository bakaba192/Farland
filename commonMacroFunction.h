#pragma once

//=================================================================================================
//	##	매크로 함수	##	(필요한 함수를 만들자!!!)
//=================================================================================================

//마우스 좌표
inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}


//한선 그리기
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

//한선 그리기(옵션 : 색깔, 선 굵기)
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY, COLORREF pen_RGB , int penWidth = 1,int penStyle = PS_SOLID)
{
	HPEN pen = CreatePen(penStyle, penWidth, pen_RGB);		//펜의 종류 : PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT
	HPEN oldPen = (HPEN)SelectObject(hdc, pen);
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
	SelectObject(hdc, oldPen);
	DeleteObject(pen);

}

//RECT 만들기
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

//RECT 중심점에 만들기
inline RECT RectMakeCP(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

//RECT 중심점에 만들기(for문 필수)
inline RECT RectArrayMCP(int startX, int startY, int width, int height, int distanceX, int distanceY, int lineNum, int forNum)
{
	RECT rc = RectMakeCP(startX + distanceX*(forNum % lineNum), startY + distanceY* (forNum / lineNum),  width, height);		
	return rc;
}

//사각형 그리기 (렉탱글함수 사용)
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

//타원 그리기 (일립스함수 사용)
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//타원 센터점 중심으로 그리기 (일립스함수 사용)
inline void EllipseMakeCP(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}


//RECT를 받아 사각형 그리기
inline void setRectangle(HDC hdc, RECT &rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}


//RECT를 받아 사각형 그리기! (옵션: 색깔)
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

//RECT를 받아 사각형 그리기! (옵션: 선색)
inline void setRectangle(HDC hdc, RECT &rc, COLORREF pen_RGB, COLORREF bru_RGB, int penWidth = 1, bool transparent = false, int penStyle = PS_SOLID)
{
	
	//선언
	HPEN pen = CreatePen(penStyle, penWidth ,pen_RGB);		//펜의 종류 : PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT
	HBRUSH brush = CreateSolidBrush(bru_RGB);

	//세팅
	SelectObject(hdc, pen);
	//SelectObject(hdc, GetStockObject(NULL_PEN));
	SelectObject(hdc, brush);
	if(transparent == true) SelectObject(hdc, GetStockObject(NULL_BRUSH));

	//사각형 그리기
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	
	//삭제
	DeleteObject(brush);
	DeleteObject(pen);
}

//RECT를 받아 원 그리기
inline void setEllipse(HDC hdc, RECT &rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//RECT를 받아 원 그리기! (옵션: 색깔)
inline void setEllipse(HDC hdc, RECT &rc, COLORREF RGB)
{
	HBRUSH brush = CreateSolidBrush(RGB);
	HBRUSH oldBrush= (HBRUSH)SelectObject(hdc, brush);
	SelectObject(hdc, GetStockObject(NULL_PEN));
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
	SelectObject(hdc, oldBrush);
	DeleteObject(brush);
}


//폰트 크기 조정하기
inline void setFont(HDC hdc, int size, char* str, int startX, int startY, COLORREF RGB = RGB(0,0,0),  LPCTSTR fontKind = "굴림체", INT bkMode = TRANSPARENT)
{

HFONT Font = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, fontKind);
HFONT oldFont = (HFONT)SelectObject(hdc, Font);
SetTextColor(hdc, RGB);				//글자색
SetBkMode(hdc, bkMode);				//불투명도 조정							
TextOut(hdc, startX, startY, str, strlen(str));
SelectObject(hdc, oldFont);
DeleteObject(Font);

//     int nHeight,						// 높이
//     int nWidth,						// 폭. 0을 넣어주면 높이에 비례함
//     int nEscapement,					// 글자 전체 기울기
//     int nOrientation,				// 기준선이 정해져 있고 기우는 기울기
//     int fnWeight,					// 폰트의 두께
//     DWORD fdwItalic,					// 이탤릭
//     DWORD fdwUnderline,				// 밑줄
//     DWORD fdwStrikeOut,				// 취소선
//     DWORD fdwCharSet,				// 캐릭터 셋
//     DWORD fdwOutputPrecision,		// 정밀도
//     DWORD fdwClipPrecision,			// 정밀도
//     DWORD fdwQuality,				// 정밀도
//     DWORD fdwPitchAndFamily,			// 정밀도
//     LPCTSTR lpszFace					// 글꼴이름
}