#pragma once
#include "singletonBase.h"

struct tagFarTile;
class character;
class F_monster;

class dataBase : public singletonBase<dataBase>
{
private:
	

	dataBase(const dataBase&);
	const dataBase operator=(const dataBase&);
public:
	explicit dataBase() {}
	~dataBase() {}

	void clearData(const char* fileName);
	void saveMapData(const char* fileName, vector<tagFarTile>& v);
	vector<tagFarTile> loadMapData(const char* fileName);

	void saveCharaData(const char* fileName, vector<character*>& v);
	vector<character*> loadCharaData(const char* fileName, bool isInitialize = false);

	void saveMonsterData(const char* fileName, vector<F_monster*>& v);
	vector<F_monster*> loadMonsterData(const char* fileName, bool isInitialize = false);

	void saveSlot(int i);
	void loadSlot(int i);
};

