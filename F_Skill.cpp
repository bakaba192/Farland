#include "stdafx.h"
#include "F_Skill.h"

HRESULT F_Skill::init(string name, int mAtk, int Bounds)
{
	ZeroMemory(&_data, sizeof(tagSkill));

	_name = name;
	_skillBounds = Bounds;


	if (_name == "플레임버스트")
	{
		_skillRange = 5;
		_power = mAtk * 2;
	}
	else if (_name == "힐")
	{
		_skillRange = 5;
		_power = mAtk;
	}

	for (int i = 0; i < 13; i++)
	{
		_data[i].isShow = false;
	}

	_drop = 0;
	_dropCount = 0;

	return S_OK;
}

void F_Skill::release(void)
{
}

void F_Skill::update(void)
{
	for (int i = 0; i < 13; i++)
	{
		if (_name == "플레임버스트")
		{
			if (_data[i].isShow == true && _data[i].frameX == 4)
			{
				if (i + 1 < 13)
				{
					_data[i + 1].isShow = true;
				}
			}

			if (_data[i].isShow)
			{
				_data[i].skillCount++;
				if (_data[i].skillCount % 3 == 0)
				{
					_data[i].skillCount = 0;
					_data[i].frameX++;
					if (_data[i].frameX > 16)
					{
						_data[i].frameX = 0;
						_data[i].isShow = false;
					}
				}
			}
		}
		else if(_name == "힐")
		{
			if (_data[i].isShow)
			{
				_data[i].skillCount++;

				if (_data[i].skillCount % 3 == 0)
				{
					_data[i].frameX++;

					if (_data[i].frameX > 1)
					{
						_data[i].frameX = 0;
					}
				}

				if (_data[i].skillCount % 10 == 0)
				{
					_data[i].frameY++;

					if (_data[i].frameY > 8)
					{
						_data[i].frameX = 0;
						_data[i].frameY = 0;

						_data[i].isShow = false;
					}

				}
			}
		}
	}


	if (_name == "힐")
	{
		_dropCount++;
		if (_dropCount % 3 == 0)
		{
			_drop++;
		}
	}
}

void F_Skill::render(void)
{
	showFireSkill();
}

void F_Skill::skillSetting(int x, int y)
{
	_data[0].indexX = x;
	_data[0].indexY = y;

	//순서 우하 좌하 좌상 우상
	_data[1].indexX = x + 1;
	_data[1].indexY = y;

	_data[2].indexX = x;
	_data[2].indexY = y + 1;

	_data[3].indexX = x;
	_data[3].indexY = y - 1;

	_data[4].indexX = x - 1;
	_data[4].indexY = y;

	_data[5].indexX = x + 2;
	_data[5].indexY = y;

	_data[6].indexX = x + 1;
	_data[6].indexY = y + 1;

	_data[7].indexX = x;
	_data[7].indexY = y + 2;

	_data[8].indexX = x - 1;
	_data[8].indexY = y + 1;

	_data[9].indexX = x - 2;
	_data[9].indexY = y;

	_data[10].indexX = x - 1;
	_data[10].indexY = y - 1;

	_data[11].indexX = x;
	_data[11].indexY = y - 2;

	_data[12].indexX = x + 1;
	_data[12].indexY = y - 1;
}

void F_Skill::showFireSkill()
{
	for (int i = 0; i < 13; i++)
	{
		if (_name == "플레임버스트")
		{
			if (_data[i].isShow)
			{
				if (_data[i].indexX >= 0 && _data[i].indexY >= 0 && _data[i].indexX < TILEMAXI && _data[i].indexY < TILEMAXJ)
				{
					IMAGEMANAGER->focusFrameRender(_name, getMemDC(), MAPDATA->getTileData(_data[i].indexX, _data[i].indexY)->rc.left - 38, MAPDATA->getTileData(_data[i].indexX, _data[i].indexY)->rc.top - 160, _data[i].frameX, _data[i].frameY);
				}
			}
		}
		else if (_name == "힐")
		{
			if (_data[i].isShow)
			{
				if (_data[i].indexX >= 0 && _data[i].indexY >= 0 && _data[i].indexX < TILEMAXI && _data[i].indexY < TILEMAXJ)
				{
					if (_data[i].frameY < 4)
					{
						IMAGEMANAGER->focusFrameRender(_name + "1", getMemDC(), MAPDATA->getTileData(_data[i].indexX, _data[i].indexY)->rc.left - 16, MAPDATA->getTileData(_data[i].indexX, _data[i].indexY)->rc.top - 106 + _drop, _data[i].frameX, _data[i].frameY);
					}
					else
					{
						IMAGEMANAGER->focusFrameRender(_name + "2", getMemDC(), MAPDATA->getTileData(_data[i].indexX, _data[i].indexY)->rc.left - 16, MAPDATA->getTileData(_data[i].indexX, _data[i].indexY)->rc.top - 64, _data[i].frameX, _data[i].frameY);
					}

				}
			}
		}
	}
}

void F_Skill::startFire()//방아쇠
{
	_drop = 0;

	if (_name == "힐")
	{
		for (int i = 0; i < 13; i++)
		{
			if (_skillBounds == 1)
			{
				if (i < 5)
				{
					_data[i].isShow = true;
				}
			}
			else if (_skillBounds == 0)
			{
				if (i < 1)
				{
					_data[i].isShow = true;
				}
			}
		}
	}
	else if (_name == "플레임버스트")
	{

		_data[0].isShow = true;
	}
}
