#pragma once
//=================================================================================================
//	##	싱글톤 패턴 [ singletonBase ]	##
//=================================================================================================

template <class T> // == template<typename T>
class singletonBase
{
protected:
	static T* singleton;

	singletonBase() {}
	~singletonBase() {}

public:
	//싱글톤 가져오기
	static T* getSingleton(void);
	//싱글톤 메모리에서 해제
	void releaseSingleton(void);

};

//싱글톤 초기화
template <class T>
T* singletonBase<T>::singleton = 0;

//싱글톤 가져오기
template<class T>
T * singletonBase<T>::getSingleton(void)
{
	//싱글톤이 없으면 새로 생성
	if (!singleton) singleton = new T;
	return singleton;
}

//싱글톤 메모리 해제
template<class T>
void singletonBase<T>::releaseSingleton(void)
{
	//싱글톤이 있다면 메모리 해제
	if (singleton)
	{
		delete singleton;
		singleton = 0;
	}
}
