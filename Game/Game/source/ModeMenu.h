
#include "appframe.h"
#include "MenuItemBase.h"

#include <vector>

// モード
class ModeMenu : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	void	Add(MenuItemBase* itemBase);
	void	Clear();

protected:

	// UI
	int _cgMenuTitle;
	int _cgMenuFrame01;
	int _cgMenuFrame02;
	int _cgMenuFrame03;

	int _cgMGet;
	int _cgResume;
	int _cgControl;
	int _cgAudio;
	int _cgToTitle;

	std::vector<MenuItemBase*>	_vItems;

	int _itemNum;		// 選択肢の数
	int _selecting;		// 選択肢の位置
	float _blendPal;

};

