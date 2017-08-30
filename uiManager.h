#pragma once
#include "singletonBase.h"
enum uiState
{
	U_NONE = 0, //UI¾È¶ç¿öÁü.
	U_NORMAL, //UI¶ç¿öÁ³À¸³ª ¼±ÅÃ¾ÈµÊ.
	U_MOVE, //
	U_SKILL,
	U_SKILL2,
	U_ITEM,
	U_TURNEND,
	U_SAVE,
	U_SAVE2,
	U_LOAD,
	U_LOAD2

};
class uiManager : public singletonBase<uiManager>
{
private:
	uiState _uState;
	RECT _UIrect[7];
	bool _showDemage;

	int _x;
	int _y;

	int _numberFrame;
	int _numberCount;
	int _numberUpUp;

	int hund;
	int ten;
	int one;

	bool isOnPrintDemage;

	int _saveSlot;

public:
	uiManager() {};
	~uiManager() {};

	HRESULT init(void);
	void release(void);

	void popUpUI(int x, int y);
	uiState& getUiState() { return _uState; }
	void UIrender(HDC hdc);
	bool printDemage(int x, int y, int Demage);
	void DemageRender(HDC hdc);
	RECT* getUIrect() { return _UIrect; }

	int& getSaveSlot() { return _saveSlot; }

};