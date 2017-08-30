#include "stdafx.h"
#include "CharacterData.h"

HRESULT CharacterData::init()
{
	_alLv = 3;
	_arisLv = 3;
	_karinLv = 3;

	_alExp = 0;
	_karinExp = 0;
	_arisExp = 0;

	return S_OK;
}
