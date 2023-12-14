
#include "appframe.h"


class ModeTitle : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:

	int _cg;
	int _cgTitle;
	int _cgTget;
	int _cgStart;
	int _cgTexit;

	int _itemNum;		// ‘I‘ğˆ‚Ì”
	int _selecting;		// ‘I‘ğˆ‚ÌˆÊ’u

}; 
