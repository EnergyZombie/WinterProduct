#include "ModeGameOver.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "ModeTitle.h"

bool ModeGameOver::Initialize() {
	base::Initialize();

	_cgGameOver = LoadGraph("res/UI/ゲームオーバー/ui_gameover.png");
	_cgGet = LoadGraph("res/UI/ゲームオーバー/ui_gget.png");
	_cgContinue = LoadGraph("res/UI/ゲームオーバー/ui_continue.png");
	_cgExit = LoadGraph("res/UI/ゲームオーバー/ui_gexit.png");

	_itemNum = 2;
	_selecting = 0;

	return true;
}

bool ModeGameOver::Terminate() {
	base::Terminate();

	DeleteGraph(_cgGameOver);
	DeleteGraph(_cgGet);
	DeleteGraph(_cgContinue);
	DeleteGraph(_cgExit);

	return true;
}

bool ModeGameOver::Process() {
	base::Process();

	// このモードより下のレイヤーはProcess()を呼ばない
	ModeServer::GetInstance()->SkipProcessUnderLayer();

	auto trg = ApplicationMain::GetInstance()->GetPad()->GetTrgButton();

	bool close = false;
	bool cont = false;
	bool title = false;
	// 選択処理　一旦十字キーで選択する
	if (trg & INPUT__DPAD_LEFT) { _selecting--; }
	if (trg & INPUT__DPAD_RIGHT) { _selecting++; }
	_selecting = (_selecting + _itemNum) % _itemNum;
	switch (_selecting) {
	case 0:
		if (trg & INPUT_A) { close = true; cont = true; } break;
	case 1:
		if (trg & INPUT_A) { close = true; title = true; } break;
	}
	// このモードを削除予約
	if(close){ ModeServer::GetInstance()->Clear(); }
	// ゲームモードを登録
	if (cont) { ModeServer::GetInstance()->Add(new ModeGame(), 1, "game"); }
	if (title) { ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title"); }

	return true;
}

bool ModeGameOver::Render() {
	base::Render();
	SetFontSize(64);
	std::string str = "game over";
	int x = ApplicationMain::GetInstance()->DispSizeW()/2 - str.size() * 64 / 4;
	int y = ApplicationMain::GetInstance()->DispSizeH()/2 - 64 / 2;
	DrawFormatString(x, y, GetColor(255, 0, 0), "%s", str.c_str());
	SetFontSize(16);

	DrawGraph(320, 192, _cgGameOver, TRUE);
	{	// 選択肢の描画
		int x = 448; int y = 576; int size = 640;
		DrawGraph(x, y, _cgContinue, TRUE); x += size;
		DrawGraph(x, y, _cgExit, TRUE);
		switch (_selecting){
		case 0:
			x -= size; break;
		case 1:
			break;
		}
		DrawGraph(x, y, _cgGet, TRUE);
	}

	return true;
}
