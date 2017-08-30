#pragma once
#include "singletonBase.h"
//=============================================================
//	## iniData ## (INI ������)
//=============================================================

//ini������ ����ü
struct tagIniData
{
	char* section;
	char* key;
	char* value;
};

struct tagStrIniData
{
	string section;
	string key;
	string value;
};


class iniData : public singletonBase <iniData>
{
private:
	vector<tagIniData> _vIniData;
	
	vector<tagStrIniData> _vStrIniData;

public:
	HRESULT init(void);
	void release(void);
	
	//������ �߰��ϱ�(����, Ű, ���)
	void addData(char* section, char* key, char* value);
	//���̺�(�����̸�)
	void saveINI(char* fileName);

	//������ �߰��ϱ�(����, Ű, ���)
	void addStrData(string section, string key, string value);
	//���̺�(�����̸�)
	void saveStrINI(string fileName);

	//���ڷ� �� �ε��ϱ�(�����̸�, ����, Ű)
	char* loadDataString(char* fileName, char* section, char* key);
	
	
	//������ �� �ε��ϱ�(�����̸�, ����, Ű)
	int loadDataInteger(char* fileName, char* section, char* key);

	//���ڷ� �� �ε��ϱ�(�����̸�, ����, Ű)
	char* strLoadDataString(string fileName, string section, string key);

	//������ �� �ε��ϱ�(�����̸�, ����, Ű)
	int strLoadDataInteger(string fileName, string section, string key);
	

	iniData() {}
	~iniData() {}
};

