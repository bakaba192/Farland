#pragma once
#include "singletonBase.h"
#include <time.h>

//=================================================================================================
//	##	�����Լ� [ randomFunction ]	##
//=================================================================================================

class randomFunction :	public singletonBase<randomFunction>
{
public:
	//�����ڿ��� �ʱ�ȭ
	randomFunction()
	{
		srand(GetTickCount());	//���� �ʱ�ȭ
	}
	~randomFunction() {}

	//�ʱ�ȭ
	HRESULT init() { return S_OK; }

	//���� �� ��������(�μ� 1��)
	inline int getInt(int num) { return rand() % num; }

	//���� �� ��������(�μ� 2��)
	inline int getIntFromTo(int fromNum, int toNum)
	{
		//�����Լ��� 0���� ������ ������
		return rand() % (toNum - fromNum + 1) + fromNum;
	}

	//���� �Լ�
	//inline void shuffle(int *_box, int num)
	//{
	//	for (int i = 0; i < 1000; i++)
	//	{
	//		int index1 = rand() % num;
	//		int index2 = rand() % num;
	//		int temp = _box[index1];
	//		_box[index1] = _box[index2];
	//		_box[index2] = temp;

	//	}
	//}
};

