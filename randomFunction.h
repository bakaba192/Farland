#pragma once
#include "singletonBase.h"
#include <time.h>

//=================================================================================================
//	##	랜덤함수 [ randomFunction ]	##
//=================================================================================================

class randomFunction :	public singletonBase<randomFunction>
{
public:
	//생성자에서 초기화
	randomFunction()
	{
		srand(GetTickCount());	//랜덤 초기화
	}
	~randomFunction() {}

	//초기화
	HRESULT init() { return S_OK; }

	//랜덤 값 가져오기(인수 1개)
	inline int getInt(int num) { return rand() % num; }

	//랜덤 값 가져오기(인수 2개)
	inline int getIntFromTo(int fromNum, int toNum)
	{
		//랜덤함수를 0으로 나누면 오류남
		return rand() % (toNum - fromNum + 1) + fromNum;
	}

	//셔플 함수
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

