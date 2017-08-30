#pragma once
#include "singletonBase.h"


//�������� ��ȯ���� ���Ǳ� ���� ĳ���͵��� ������ �����ϴ� �̱��� �Լ��̴�.
//ĳ���͵��� ���� �����͸� �����ϴ� ������ ���� �� ȿ������ �� �ϳ�,
//���� ��Ȳ���� �ټ� ���濡 ������� �����Ƿ� �̷� ������ ���Ѵ�.
//������ �̰��� ���, ���� ���� ��� ����Ǿ� ���� ���̴�.

class CharacterData : public singletonBase<CharacterData>
{
private:
	int _alLv;
	int _karinLv;
	int _arisLv;

	int _alExp;
	int _karinExp;
	int _arisExp;

public:
	CharacterData() {};
	~CharacterData() {};
	
	HRESULT init();

	int& getAlLv() { return _alLv; }
	int& getKarinLv() { return _karinLv; }
	int& getArisLv() { return _arisLv; }

	int& getAlExp() { return _alExp; }
	int& getKarinExp() { return _karinExp; }
	int& getArisExp() { return _arisExp; }

};

