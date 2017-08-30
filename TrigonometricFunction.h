#pragma once

//=================================================================================================
//	##	삼각 매크로함수 [ TrigonometricFunction ]	##
//=================================================================================================


//전처리기 이름변수 선언 - 수학
#define M_PI			3.141592			//파이
#define M_RAD		(M_PI / 180)		//라디안으로
#define M_DIG		(180 / M_PI)		//디그리으로

//float포인터형 구조체타입 선언
typedef struct tagF_POINT
{
	FLOAT x;
	FLOAT y;
} F_POINT, POINT_F;


//두점 사이의 각도 구하는 함수
inline float getAngleF(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;

	//두점 사이의 거리 구하는 공식
	float distance = sqrtf(x * x + y * y);

	//두점 사이의 각도 구하는 공식
	float angle = acosf(x / distance);
	//acos => 0 ~ 180도까지의 라디안값을 리턴
	//예외처리
	if(endY > startY)
	{
		angle = M_PI - angle;	//라디안 값 반환
	}

	return angle;
}



//두점 사이의 각도 구하는 함수(F_POINT용)
inline float getAngleF(F_POINT P1, F_POINT P2)
{
	float x = P2.x - P1.x;
	float y = P2.y - P1.y;

	//두점 사이의 거리 구하는 공식
	float distance = sqrtf(x * x + y * y);

	//두점 사이의 각도 구하는 공식
	float angle = acosf(x / distance);
	//acos => 0 ~ 180도까지의 라디안값을 리턴
	//예외처리
	if(P2.y > P1.y)
	{
		angle = 2 * M_PI - angle;
	}

	return angle;
}

//두점 사이의 각도 구하는 함수
inline float getAngleI(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;

	//두점 사이의 거리 구하는 공식
	float distance = sqrtf(x * x + y * y);

	//두점 사이의 각도 구하는 공식
	float angle = acosf(x / distance);
	//acos => 0 ~ 180도까지의 라디안값을 리턴
	//예외처리
	if(endY > startY)
	{
		angle = M_PI - angle;	//라디안 값 반환
	}

	return angle;
}

//두점 사이의 각도 구하는 함수(F_POINT용)
inline float getAngleI(POINT P1, POINT P2)
{
	//P1이 원점
	float x = P2.x - P1.x;
	float y = P2.y - P1.y;

	//두점 사이의 거리 구하는 공식
	float distance = sqrtf(x * x + y * y);

	//두점 사이의 각도 구하는 공식
	float angle = acosf(x / distance);
	//acos => 0 ~ 180도까지의 라디안값을 리턴
	//예외처리
	if(P2.y > P1.y)
	{
		angle = 2 * M_PI - angle;
	}

	return angle;
}



//중점 사이의 거리 구하는 함수
inline float getDistanceCP(float X1, float Y1, float X2, float Y2)
{
	//두 중점의 실제 거리 좌표차
	float dX = fabs(X1 - X2);
	float dY = fabs(Y1 - Y2);
	//두 중점 사이의 거리
	float Distance = sqrt(dX*dX + dY*dY);

	return Distance;
}

//중점 사이의 거리 구하는 함수(F_POINT로 받기)
inline float getDistanceCP(F_POINT P1, F_POINT P2)
{
	//두 중점의 실제 거리 좌표차
	float dX = fabs(P1.x - P2.x);
	float dY = fabs(P1.y - P2.y);
	//두 중점 사이의 거리
	float Distance = sqrt(dX*dX + dY*dY);

	return Distance;
}

//중점 사이의 거리 구하는 함수(F_POINT로 받기)
inline int getDistanceCP(POINT P1, POINT P2)
{
	//두 중점의 실제 거리 좌표차
	int dX = fabs(P1.x - P2.x);
	int dY = fabs(P1.y - P2.y);
	//두 중점 사이의 거리
	int Distance = sqrt(dX*dX + dY*dY);

	return Distance;
}


//원형 충돌함수
inline bool IntersectCircle(float X1, float Y1, float R1, float X2, float Y2, float R2)
{
	//피타고라스 정리를 사용한 충돌함수임

	//충돌여부
	bool collision = false;

	//두 원 반지름 합계
	float sumRadius = (R1 + R2)*(R1 + R2);
	//두 원의 실제 거리 좌표차
	float dX = fabs(X1 - X2);
	float dY = fabs(Y1 - Y2);

	//두 원의 사이의 거리
	float CirDistance = (dX*dX + dY*dY);

	//원 충돌 판정
	if(sumRadius > CirDistance)
	{
		collision = true;
	}

	return collision;
}

//렉트 중심좌표X
inline int getRectCenterX(RECT &RC)
{
	int X = RC.left + (RC.right - RC.left) / 2;

	return X;
}

//렉트 중심좌표Y
inline int getRectCenterY(RECT &RC)
{
	int Y = RC.top + (RC.bottom - RC.top) / 2;

	return Y;
}

//렉트 중심좌표 POINT
inline F_POINT getRectCenter(RECT &RC)
{
	F_POINT pt;
	pt.x = RC.left + (RC.right - RC.left) / 2;
	pt.y = RC.top + (RC.bottom - RC.top) / 2;

	return pt;
}



inline bool IntersectRCC(RECT &RC1, float R1, RECT &RC2, float R2)
{
	//피타고라스 정리를 사용한 충돌함수임

	//충돌여부
	bool collision = false;

	int X1 = RC1.left + (RC1.right - RC1.left) / 2;
	int Y1 = RC1.top + (RC1.bottom - RC1.top) / 2;
	int X2 = RC2.left + (RC2.right - RC2.left) / 2;
	int Y2 = RC2.top + (RC2.bottom - RC2.top) / 2;

	//두 원 반지름 합계
	float sumRadius = (R1 + R2)*(R1 + R2);
	//두 원의 실제 거리 좌표차
	float dX = fabs(X1 - X2);
	float dY = fabs(Y1 - Y2);

	//두 원의 사이의 거리
	float CirDistance = (dX*dX + dY*dY);

	//원 충돌 판정
	if(sumRadius > CirDistance)
	{
		collision = true;
	}

	return collision;
}



//원형 충돌함수 (F_POINT로 받기)
inline bool IntersectCircle(F_POINT P1, float R1, F_POINT P2, float R2)
{
	//피타고라스 정리를 사용한 충돌함수임

	//충돌여부
	bool collision = false;

	//두 원 반지름 합계
	float sumRadius = (R1 + R2)*(R1 + R2);
	//두 원의 실제 거리 좌표차
	float dX = fabs(P1.x - P2.x);
	float dY = fabs(P1.y - P2.y);

	//두 원의 사이의 거리
	float CirDistance = (dX*dX + dY*dY);

	//원 충돌 판정
	if(sumRadius > CirDistance)
	{
		collision = true;
	}

	return collision;
}