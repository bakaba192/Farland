#include "stdafx.h"
#include "iniData.h"

HRESULT iniData::init(void)
{
	return S_OK;
}

void iniData::release(void)
{
}
//데이터 추가하기(섹션, 키, 밸류)
void iniData::addData(char * section, char * key, char * value)
{
	//ini데이터 구조체 선언후 초기화
	tagIniData iniData;
	iniData.section = section;
	iniData.key = key;
	iniData.value = value;

	//벡터에 ini데이터 구조체를 담기
	_vIniData.push_back(iniData);


}

//세이브(파일이름)
void iniData::saveINI(char * fileName)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	strcat(dir, str);

	for (int i = 0; i < _vIniData.size(); i++)
	{
		WritePrivateProfileString(_vIniData[i].section, _vIniData[i].key, _vIniData[i].value, dir);
	}

	//지우기 - 쓰레기값 출력 방지
	for (int i = 0; i < _vIniData.size(); i++)
	{
		_vIniData.erase(_vIniData.begin() + i);
	}
	_vIniData.clear();

}

//데이터 추가하기(섹션, 키, 밸류) - string형
void iniData::addStrData(string section, string key, string value)
{
	//ini데이터 구조체 선언후 초기화
	tagStrIniData iniStrData;
	iniStrData.section = section;
	iniStrData.key = key;
	iniStrData.value = value;

	//있는지 검사
	for (int i = 0; i < _vStrIniData.size(); i++)
	{
		if (_vStrIniData[i].section == iniStrData.section)
		{
			if (_vStrIniData[i].key == iniStrData.key)
			{
				_vStrIniData[i].value = value;
				return;
			}
		}

	}
	//벡터에 ini데이터 구조체를 담기
	_vStrIniData.push_back(iniStrData);

}

//세이브(파일이름) - string용
void iniData::saveStrINI(string fileName)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(str, "\\%s.ini", fileName.c_str());
	GetCurrentDirectory(256, dir);
	strcat(dir, str);

	for (int i = 0; i < _vStrIniData.size(); i++)
	{
		WritePrivateProfileString(_vStrIniData[i].section.c_str(), _vStrIniData[i].key.c_str(), _vStrIniData[i].value.c_str(), dir);
	}
	//지우기
	for (int i = 0; i < _vStrIniData.size(); i++)
	{
		_vStrIniData.erase(_vStrIniData.begin() + i);
	}
	_vStrIniData.clear();
}


//문자로 값 로드하기(파일이름, 섹션, 키)
char * iniData::loadDataString(char * fileName, char * section, char * key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	strcat(dir, str);

	char data[64] = { NULL };
	GetPrivateProfileString(section, key, "", data, 64, dir);

	return data;
}



//정수로 값 로드하기(파일이름, 섹셕, 키)
int iniData::loadDataInteger(char * fileName, char * section, char * key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	strcat(dir, str);

	return GetPrivateProfileInt(section, key, 0, dir);
}

//문자로 값 로드하기(파일이름, 섹션, 키) - string용
char* iniData::strLoadDataString(string fileName, string section, string key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(str, "\\%s.ini", fileName.c_str());
	GetCurrentDirectory(256, dir);
	strcat(dir, str);

	char data[64];
	GetPrivateProfileString(section.c_str(), key.c_str(), "", data, 64, dir);

	return data;
}

//정수로 값 로드하기(파일이름, 섹셕, 키) - string용
int iniData::strLoadDataInteger(string fileName, string section, string key)
{

	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(str, "\\%s.ini", fileName.c_str());
	GetCurrentDirectory(256, dir);
	strcat(dir, str);

	return GetPrivateProfileInt(section.c_str(), key.c_str(), 0, dir);
}
