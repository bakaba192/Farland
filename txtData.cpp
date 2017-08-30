#include "stdafx.h"
#include "txtData.h"


HRESULT txtData::init(void)
{
	return S_OK;
}

//세이브
void txtData::txtSave(char * saveFileName, vector<string> vStr)
{
	HANDLE file;
	char str[128];
	DWORD write;

	strcpy_s(str, 128, vectorArrayCombine(vStr));

	file = CreateFile(saveFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, str, 128, &write, NULL);

	CloseHandle(file);
}

char * txtData::vectorArrayCombine(vector<string> vArray)
{
	char str[128];
	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); i++)
	{
		strcat(str, vArray[i].c_str());
		if (i + 1 < vArray.size())
		{
			strcat(str, ",");
		}
	}

	return str;
}

//로드
vector<string> txtData::txtLoad(char * loadFileName)
{
	HANDLE file;
	char str[128];
	ZeroMemory(str, sizeof(str));
	DWORD read;

	file = CreateFile(loadFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, str, 128, &read, NULL);

	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> txtData::charArraySeparation(char charArray[])
{
	vector<string> vArray;
	char* separator = ",";
	char* token;
	//a,b,c...
	token = strtok(charArray, separator);
	vArray.push_back(token);

	while (NULL != (token = strtok(NULL, separator)))
	{
		vArray.push_back(token);
	}

	return vArray;
}
