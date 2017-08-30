#pragma once
//=================================================================================================
//	##	�̱��� ���� [ singletonBase ]	##
//=================================================================================================

template <class T> // == template<typename T>
class singletonBase
{
protected:
	static T* singleton;

	singletonBase() {}
	~singletonBase() {}

public:
	//�̱��� ��������
	static T* getSingleton(void);
	//�̱��� �޸𸮿��� ����
	void releaseSingleton(void);

};

//�̱��� �ʱ�ȭ
template <class T>
T* singletonBase<T>::singleton = 0;

//�̱��� ��������
template<class T>
T * singletonBase<T>::getSingleton(void)
{
	//�̱����� ������ ���� ����
	if (!singleton) singleton = new T;
	return singleton;
}

//�̱��� �޸� ����
template<class T>
void singletonBase<T>::releaseSingleton(void)
{
	//�̱����� �ִٸ� �޸� ����
	if (singleton)
	{
		delete singleton;
		singleton = 0;
	}
}
