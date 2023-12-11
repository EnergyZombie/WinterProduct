
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "ModeStageConfirmation.h"

bool ModeStageConfirmation::Initialize() {
	if (!base::Initialize()) { return false; }

	_cgStageMap = LoadGraph("res/StageMap.png");

	_x = 0;
	_y = 0;
	_mapCnt = 180;

	return true;
}

bool ModeStageConfirmation::Terminate() {
	base::Terminate();
	DeleteGraph(_cgStageMap);
	return true;
}

bool ModeStageConfirmation::Process() {
	base::Process();

	 if (_mapCnt == 0) // 180f‚Åƒ‚[ƒhØ‘Ö
	 {
		 // ‚±‚Ìƒ‚[ƒh‚ðíœ—\–ñ
		 ModeServer::GetInstance()->Del(this);
		 // ŽŸ‚Ìƒ‚[ƒh‚ð“o˜^
		 ModeServer::GetInstance()->Add(new ModeGame(), 1, "game");
	 }
	 _mapCnt--;

	return true;
}

bool ModeStageConfirmation::Render() {
	base::Render();

	DrawGraph(_x, _y, _cgStageMap, FALSE);

	{
		int x = 0, y = 0, size = 16;
		int Cr = GetColor(255, 0, 0);
		DrawFormatString(x, y, Cr, "ModeStageConfirmation"); y += size;
		DrawFormatString(x, y, Cr, "_mapCnt:%d", _mapCnt); y += size;
	}

	return true;
}
