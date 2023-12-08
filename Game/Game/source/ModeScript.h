#pragma once
#include "appframe.h"


class ModeScript : public ModeBase
{
	typedef ModeBase base;
public:
	ModeScript(std::string str) { _str = str; }
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:

	std::string _str;

};
