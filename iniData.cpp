#include "stdafx.h"
#include "iniData.h"

HRESULT iniData::init(void)
{
	return S_OK;
}

void iniData::release(void)
{
}
//������ �߰��ϱ�(����, Ű, ���)
void iniData::addData(char * section, char * key, char * value)
{
	//ini������ ����ü ������ �ʱ�ȭ
	tagIniData iniData;
	iniData.section = section;
	iniData.key = key;
	iniData.value = value;

	//���Ϳ� ini������ ����ü�� ���
	_vIniData.push_back(iniData);


}

//���̺�(�����̸�)
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

	//����� - �����Ⱚ ��� ����
	for (int i = 0; i < _vIniData.size(); i++)
	{
		_vIniData.erase(_vIniData.begin() + i);
	}
	_vIniData.clear();

}

//������ �߰��ϱ�(����, Ű, ���) - string��
void iniData::addStrData(string section, string key, string value)
{
	//ini������ ����ü ������ �ʱ�ȭ
	tagStrIniData iniStrData;
	iniStrData.section = section;
	iniStrData.key = key;
	iniStrData.value = value;

	//�ִ��� �˻�
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
	//���Ϳ� ini������ ����ü�� ���
	_vStrIniData.push_back(iniStrData);

}

//���̺�(�����̸�) - string��
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
	//�����
	for (int i = 0; i < _vStrIniData.size(); i++)
	{
		_vStrIniData.erase(_vStrIniData.begin() + i);
	}
	_vStrIniData.clear();
}


//���ڷ� �� �ε��ϱ�(�����̸�, ����, Ű)
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



//������ �� �ε��ϱ�(�����̸�, ����, Ű)
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

//���ڷ� �� �ε��ϱ�(�����̸�, ����, Ű) - string��
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

//������ �� �ε��ϱ�(�����̸�, ����, Ű) - string��
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
