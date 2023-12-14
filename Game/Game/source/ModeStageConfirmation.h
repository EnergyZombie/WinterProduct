
#include "appframe.h"

class ModeStageConfirmation : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:

	// 画像ハンドル
	int _cgStageMap;
	int _x, _y;

	int		_mapCnt;

};

