
#include "appframe.h"

class ModeMenu : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:
	// UI
	int _cgMenuTitle;
	int _cgMenuFrame01;
	int _cgMenuFrame02;
	int _cgMenuFrame03;
	int _cgResume;
	int _cgControl;
	int _cgAudio;
	int _cgToTitle;
	int _cgGResume;
	int _cgGControl;
	int _cgGAudio;
	int _cgGToTitle;

	int _selecting;
};

