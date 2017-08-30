#include "stdafx.h"
#include "dataBase.h"
#include "character.h"
#include "F_monster.h"

void dataBase::clearData(const char * fileName)
{
	char str[256];
	ZeroMemory(str, sizeof(str));
	sprintf(str, "%s.txt", fileName);

	ofstream outFile(str, ios_base::trunc);
	outFile.close();
}

void dataBase::saveMapData(const char* fileName, vector<tagFarTile>& v)
{
	char str[256];
	ZeroMemory(str, sizeof(str));
	sprintf(str, "%s.txt", fileName);

	ofstream outFile(str);
	for (int i = 0; i < v.size(); i++)
	{
		outFile <<
			v[i].tileT << ',' <<
			v[i].z << ',' <<
			v[i].objIndex1 << ',' <<
			v[i].objIndex2 << ',' <<
			endl;
	}
	outFile.close();
}

vector<tagFarTile> dataBase::loadMapData(const char * fileName)
{
	char str[256];
	ZeroMemory(str, sizeof(str));
	sprintf(str, "%s.txt", fileName);

	char inputString[256];
	ifstream inFile(str);
	
	

	vector<tagFarTile> arr;
	tagFarTile temp;
	while (!inFile.eof())
	{
		inFile.getline(inputString, 256, ',');
		temp.tileT = (TILETYPE)atoi(inputString);
		inFile.getline(inputString, 256, ',');
		temp.z = atoi(inputString);
		inFile.getline(inputString, 256, ',');
		temp.objIndex1 = (OBJECT1)atoi(inputString);
		inFile.getline(inputString, 256, ',');
		temp.objIndex2 = (OBJECT2)atoi(inputString);
		arr.push_back(temp);
	}
	inFile.close();
	return arr;
}

void dataBase::saveCharaData(const char * fileName, vector<character*>& v)
{
	char str[256];
	ZeroMemory(str, sizeof(str));
	sprintf(str, "%s.txt", fileName);

	ofstream outFile(str);
	for (int i = 0; i < v.size(); i++)
	{
		if (i > 0)
		{
			outFile << endl;
		}

		outFile <<
			v[i]->getCName() << ',' <<
			v[i]->getPosX() << ',' <<
			v[i]->getPosY() << ',' <<
			v[i]->getStatus().lv << ',' <<
			v[i]->getState() << ',' <<
			v[i]->getStatus().hp << ',' <<
			v[i]->getStatus().mp << ',' <<
			v[i]->getStatus().forward << ',' <<
			v[i]->getStatus().isReadyToBehavior << ',' <<
			v[i]->getStatus().isReadyToMove << ',' <<
			v[i]->getStatus().Exp;
		//그러니까... getline은 \n만나면 토큰을 잘라주는 함수이다. 즉 \n을 다음 부터는 다음 라인에 읽는다.
	}
	outFile.close();
}

vector<character*> dataBase::loadCharaData(const char * fileName, bool isInitialize)
{

	char str[256];
	ZeroMemory(str, sizeof(str));
	sprintf(str, "%s.txt", fileName);

	char inputString[256];
	char* context;
	char* token;

	ifstream inFile(str);

	vector<character*> arr;
	character* temp;

	while (!inFile.eof())
	{
		temp = new character;
		
		inFile.getline(inputString, 256);
		

		token = strtok_s(inputString, ",", &context);

		temp->getCName() = (CharaName)atoi(token);
		

		token = strtok_s(NULL, ",", &context);
		temp->getPosX() = atoi(token);
		token = strtok_s(NULL, ",", &context);
		temp->getPosY() = atoi(token);
		token = strtok_s(NULL, ",", &context);
		temp->getStatus().lv = atoi(token);

		if (isInitialize) //캐릭터 불러오기 아니고 스테이지 이동이다.
		{
			//캐릭터의 레벨값은 유지된다.
			switch (temp->getCName())
			{
			case N_AL:
			{
				temp->getStatus().lv =  CHARADATA->getAlLv();
				temp->getStatus().Exp = CHARADATA->getAlExp();
				break;
			}
			case N_ARIS:
			{
				temp->getStatus().lv = CHARADATA->getArisLv();
				temp->getStatus().Exp = CHARADATA->getArisExp();
				break;
			}
			case N_KARIN:
			{
				temp->getStatus().lv = CHARADATA->getKarinLv();
				temp->getStatus().Exp = CHARADATA->getKarinExp();
				break;
			}
			default:
				break;
			}
		}

		temp->init(temp->getPosX(), temp->getPosY(), temp->getCName(), temp->getStatus().lv);

		if (!isInitialize)
		{
			token = strtok_s(NULL, ",", &context);
			temp->getState() = (charaState)atoi(token);
			token = strtok_s(NULL, ",", &context);
			temp->getStatus().hp = atoi(token);
			token = strtok_s(NULL, ",", &context);
			temp->getStatus().mp = atoi(token);
			token = strtok_s(NULL, ",", &context);
			temp->getStatus().forward = atoi(token);
			token = strtok_s(NULL, ",", &context);
			temp->getStatus().isReadyToBehavior = atoi(token);
			token = strtok_s(NULL, ",", &context);
			temp->getStatus().isReadyToMove = atoi(token);
			token = strtok_s(NULL, ",", &context);
			temp->getStatus().Exp = atoi(token);
		}

		arr.push_back(temp);
	}
	inFile.close();
	return arr;

}

void dataBase::saveMonsterData(const char * fileName, vector<F_monster*>& v)
{
	char str[256];
	ZeroMemory(str, sizeof(str));
	sprintf(str, "%s.txt", fileName);

	ofstream outFile(str);
	for (int i = 0; i < v.size(); i++)
	{
		if (i > 0)
		{
			outFile << endl;
		}
		outFile <<
			v[i]->getMName() << ',' <<
			v[i]->getPosX() << ',' <<
			v[i]->getPosY() << ',' <<
			v[i]->getMStatus().lv << ',' <<
			v[i]->getMStatus().hp << ',' <<
			v[i]->getMStatus().mp << ',' <<
			v[i]->getMStatus().forward << ',' <<
			v[i]->getMStatus().isReadyToBehavior << ',' <<
			v[i]->getMStatus().isReadyToMove;
	}
	outFile.close();
}

vector<F_monster*> dataBase::loadMonsterData(const char * fileName, bool isInitialize)
{
	char str[256];
	ZeroMemory(str, sizeof(str));
	sprintf(str, "%s.txt", fileName);

	char inputString[256];
	char* context;
	char* token;

	ifstream inFile(str);

	vector<F_monster*> arr;
	F_monster* temp;
	while (!inFile.eof())
	{
		temp = new F_monster;
		
		inFile.getline(inputString, 256);
		token = strtok_s(inputString, ",", &context);

		temp->getMName() = (MonsterName)atoi(inputString);

		token = strtok_s(NULL, ",", &context);
		temp->getPosX() = atoi(token);
		token = strtok_s(NULL, ",", &context);
		temp->getPosY() = atoi(token);
		token = strtok_s(NULL, ",", &context);
		temp->getMStatus().lv = atoi(token);

		temp->init(temp->getPosX(), temp->getPosY(), temp->getMName(), temp->getMStatus().lv);

		if (!isInitialize)
		{
			token = strtok_s(NULL, ",", &context);
			temp->getMStatus().hp = atoi(token);
			token = strtok_s(NULL, ",", &context);
			temp->getMStatus().mp = atoi(token);
			token = strtok_s(NULL, ",", &context);
			temp->getMStatus().forward = atoi(token);
			token = strtok_s(NULL, ",", &context);
			temp->getMStatus().isReadyToBehavior = atoi(token);
			token = strtok_s(NULL, ",", &context);
			temp->getMStatus().isReadyToMove = atoi(token);
		}

		arr.push_back(temp);
	}
	inFile.close();
	return arr;
}

void dataBase::saveSlot(int i)
{
	char str[256];
	ZeroMemory(str, sizeof(str));
	string str1 = "ini/슬롯" + to_string(i);
	sprintf(str, "%s.txt", str1.c_str());

	ofstream outFile(str);
	outFile << MAPDATA->getStageNumber() << "," << 
		ENDINGMANAGER->getStageClear()[0] << "," <<
		ENDINGMANAGER->getStageClear()[1] << "," << 
		ENDINGMANAGER->getStageClear()[2] ;

}

void dataBase::loadSlot(int i)
{
	char str[256];
	ZeroMemory(str, sizeof(str));
	string str1 = "ini/슬롯" + to_string(i);
	sprintf(str, "%s.txt", str1.c_str());

	char inputString[256];
	char* context;
	char* token;


	ifstream inFile(str);

	inFile.getline(inputString, 256);

	token = strtok_s(inputString, ",", &context);

	MAPDATA->getStageNumber() = atoi(token);

	token = strtok_s(NULL, ",", &context);

	ENDINGMANAGER->getStageClear()[0] = atoi(token);

	token = strtok_s(NULL, ",", &context);

	ENDINGMANAGER->getStageClear()[1] = atoi(token);

	token = strtok_s(NULL, ",", &context);

	ENDINGMANAGER->getStageClear()[2] = atoi(token);
}


//
//void dataBase::saveCharaLv(const char * fileName)
//{
//	char str[256];
//	ZeroMemory(str, sizeof(str));
//	sprintf(str, "%s.txt", fileName);
//
//	ofstream outFile(str);
//
//	outFile << CHARADATA->getAlLv() << endl;
//	outFile << CHARADATA->getArisLv() << endl;
//	outFile << CHARADATA->getKarinLv() << endl;
//
//	outFile.close();
//}
//
//void dataBase::loadCharaLv(const char * fileName)
//{
//	char str[256];
//	ZeroMemory(str, sizeof(str));
//	sprintf(str, "%s.txt", fileName);
//
//	char inputString[256];
//
//	ifstream inFile(str);
//
//	inFile.getline(inputString, 256);
//	CHARADATA->getAlLv() = atoi(inputString);
//
//	inFile.getline(inputString, 256);
//	CHARADATA->getArisLv() = atoi(inputString);
//
//	inFile.getline(inputString, 256);
//	CHARADATA->getKarinLv() = atoi(inputString);
//
//	inFile.close();
//}
