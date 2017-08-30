#pragma once

//=================================================================================================
//	##	�ﰢ ��ũ���Լ� [ TrigonometricFunction ]	##
//=================================================================================================


//��ó���� �̸����� ���� - ����
#define M_PI			3.141592			//����
#define M_RAD		(M_PI / 180)		//��������
#define M_DIG		(180 / M_PI)		//��׸�����

//float�������� ����üŸ�� ����
typedef struct tagF_POINT
{
	FLOAT x;
	FLOAT y;
} F_POINT, POINT_F;


//���� ������ ���� ���ϴ� �Լ�
inline float getAngleF(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;

	//���� ������ �Ÿ� ���ϴ� ����
	float distance = sqrtf(x * x + y * y);

	//���� ������ ���� ���ϴ� ����
	float angle = acosf(x / distance);
	//acos => 0 ~ 180�������� ���Ȱ��� ����
	//����ó��
	if(endY > startY)
	{
		angle = M_PI - angle;	//���� �� ��ȯ
	}

	return angle;
}



//���� ������ ���� ���ϴ� �Լ�(F_POINT��)
inline float getAngleF(F_POINT P1, F_POINT P2)
{
	float x = P2.x - P1.x;
	float y = P2.y - P1.y;

	//���� ������ �Ÿ� ���ϴ� ����
	float distance = sqrtf(x * x + y * y);

	//���� ������ ���� ���ϴ� ����
	float angle = acosf(x / distance);
	//acos => 0 ~ 180�������� ���Ȱ��� ����
	//����ó��
	if(P2.y > P1.y)
	{
		angle = 2 * M_PI - angle;
	}

	return angle;
}

//���� ������ ���� ���ϴ� �Լ�
inline float getAngleI(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;

	//���� ������ �Ÿ� ���ϴ� ����
	float distance = sqrtf(x * x + y * y);

	//���� ������ ���� ���ϴ� ����
	float angle = acosf(x / distance);
	//acos => 0 ~ 180�������� ���Ȱ��� ����
	//����ó��
	if(endY > startY)
	{
		angle = M_PI - angle;	//���� �� ��ȯ
	}

	return angle;
}

//���� ������ ���� ���ϴ� �Լ�(F_POINT��)
inline float getAngleI(POINT P1, POINT P2)
{
	//P1�� ����
	float x = P2.x - P1.x;
	float y = P2.y - P1.y;

	//���� ������ �Ÿ� ���ϴ� ����
	float distance = sqrtf(x * x + y * y);

	//���� ������ ���� ���ϴ� ����
	float angle = acosf(x / distance);
	//acos => 0 ~ 180�������� ���Ȱ��� ����
	//����ó��
	if(P2.y > P1.y)
	{
		angle = 2 * M_PI - angle;
	}

	return angle;
}



//���� ������ �Ÿ� ���ϴ� �Լ�
inline float getDistanceCP(float X1, float Y1, float X2, float Y2)
{
	//�� ������ ���� �Ÿ� ��ǥ��
	float dX = fabs(X1 - X2);
	float dY = fabs(Y1 - Y2);
	//�� ���� ������ �Ÿ�
	float Distance = sqrt(dX*dX + dY*dY);

	return Distance;
}

//���� ������ �Ÿ� ���ϴ� �Լ�(F_POINT�� �ޱ�)
inline float getDistanceCP(F_POINT P1, F_POINT P2)
{
	//�� ������ ���� �Ÿ� ��ǥ��
	float dX = fabs(P1.x - P2.x);
	float dY = fabs(P1.y - P2.y);
	//�� ���� ������ �Ÿ�
	float Distance = sqrt(dX*dX + dY*dY);

	return Distance;
}

//���� ������ �Ÿ� ���ϴ� �Լ�(F_POINT�� �ޱ�)
inline int getDistanceCP(POINT P1, POINT P2)
{
	//�� ������ ���� �Ÿ� ��ǥ��
	int dX = fabs(P1.x - P2.x);
	int dY = fabs(P1.y - P2.y);
	//�� ���� ������ �Ÿ�
	int Distance = sqrt(dX*dX + dY*dY);

	return Distance;
}


//���� �浹�Լ�
inline bool IntersectCircle(float X1, float Y1, float R1, float X2, float Y2, float R2)
{
	//��Ÿ��� ������ ����� �浹�Լ���

	//�浹����
	bool collision = false;

	//�� �� ������ �հ�
	float sumRadius = (R1 + R2)*(R1 + R2);
	//�� ���� ���� �Ÿ� ��ǥ��
	float dX = fabs(X1 - X2);
	float dY = fabs(Y1 - Y2);

	//�� ���� ������ �Ÿ�
	float CirDistance = (dX*dX + dY*dY);

	//�� �浹 ����
	if(sumRadius > CirDistance)
	{
		collision = true;
	}

	return collision;
}

//��Ʈ �߽���ǥX
inline int getRectCenterX(RECT &RC)
{
	int X = RC.left + (RC.right - RC.left) / 2;

	return X;
}

//��Ʈ �߽���ǥY
inline int getRectCenterY(RECT &RC)
{
	int Y = RC.top + (RC.bottom - RC.top) / 2;

	return Y;
}

//��Ʈ �߽���ǥ POINT
inline F_POINT getRectCenter(RECT &RC)
{
	F_POINT pt;
	pt.x = RC.left + (RC.right - RC.left) / 2;
	pt.y = RC.top + (RC.bottom - RC.top) / 2;

	return pt;
}



inline bool IntersectRCC(RECT &RC1, float R1, RECT &RC2, float R2)
{
	//��Ÿ��� ������ ����� �浹�Լ���

	//�浹����
	bool collision = false;

	int X1 = RC1.left + (RC1.right - RC1.left) / 2;
	int Y1 = RC1.top + (RC1.bottom - RC1.top) / 2;
	int X2 = RC2.left + (RC2.right - RC2.left) / 2;
	int Y2 = RC2.top + (RC2.bottom - RC2.top) / 2;

	//�� �� ������ �հ�
	float sumRadius = (R1 + R2)*(R1 + R2);
	//�� ���� ���� �Ÿ� ��ǥ��
	float dX = fabs(X1 - X2);
	float dY = fabs(Y1 - Y2);

	//�� ���� ������ �Ÿ�
	float CirDistance = (dX*dX + dY*dY);

	//�� �浹 ����
	if(sumRadius > CirDistance)
	{
		collision = true;
	}

	return collision;
}



//���� �浹�Լ� (F_POINT�� �ޱ�)
inline bool IntersectCircle(F_POINT P1, float R1, F_POINT P2, float R2)
{
	//��Ÿ��� ������ ����� �浹�Լ���

	//�浹����
	bool collision = false;

	//�� �� ������ �հ�
	float sumRadius = (R1 + R2)*(R1 + R2);
	//�� ���� ���� �Ÿ� ��ǥ��
	float dX = fabs(P1.x - P2.x);
	float dY = fabs(P1.y - P2.y);

	//�� ���� ������ �Ÿ�
	float CirDistance = (dX*dX + dY*dY);

	//�� �浹 ����
	if(sumRadius > CirDistance)
	{
		collision = true;
	}

	return collision;
}