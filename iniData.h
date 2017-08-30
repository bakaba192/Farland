#pragma once
#include "singletonBase.h"
//=============================================================
//	## iniData ## (INI 데이터)
//=============================================================

//ini데이터 구조체
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
	
	//데이터 추가하기(섹션, 키, 밸류)
	void addData(char* section, char* key, char* value);
	//세이브(파일이름)
	void saveINI(char* fileName);

	//데이터 추가하기(섹션, 키, 밸류)
	void addStrData(string section, string key, string value);
	//세이브(파일이름)
	void saveStrINI(string fileName);

	//문자로 값 로드하기(파일이름, 섹션, 키)
	char* loadDataString(char* fileName, char* section, char* key);
	
	
	//정수로 값 로드하기(파일이름, 섹셕, 키)
	int loadDataInteger(char* fileName, char* section, char* key);

	//문자로 값 로드하기(파일이름, 섹션, 키)
	char* strLoadDataString(string fileName, string section, string key);

	//정수로 값 로드하기(파일이름, 섹셕, 키)
	int strLoadDataInteger(string fileName, string section, string key);
	

	iniData() {}
	~iniData() {}
};

