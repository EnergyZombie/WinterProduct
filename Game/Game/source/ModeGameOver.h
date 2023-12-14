#pragma once
#include "appframe.h"

class ModeGameOver :public ModeBase {
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:

	int _cg;
	int _cgGameOver;
	int _cgGet;
	int _cgContinue;
	int _cgExit;

	int _itemNum;		// ‘I‘ğˆ‚Ì”
	int _selecting;		// ‘I‘ğˆ‚ÌˆÊ’u


};