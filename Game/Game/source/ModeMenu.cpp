
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeMenu.h"

bool ModeMenu::Initialize() {
	if (!base::Initialize()) { return false; }

	_cgMenuTitle = LoadGraph("res/UI/Flame/ui_menutitle.png");
	_cgMenuFrame01 = LoadGraph("res/UI/Flame/ui_menuframe_01.png");
	_cgMenuFrame02 = LoadGraph("res/UI/Flame/ui_menuframe_02.png");
	_cgMenuFrame03 = LoadGraph("res/UI/Flame/ui_menuframe_03.png");

	_cgResume = LoadGraph("res/UI/SelectItem/Unselct/ui_resume.png");
	_cgControl = LoadGraph("res/UI/SelectItem/Unselct/ui_control.png");
	_cgAudio = LoadGraph("res/UI/SelectItem/Unselct/ui_audio.png");
	_cgToTitle = LoadGraph("res/UI/SelectItem/Unselct/ui_totitle.png");
	_cgGResume = LoadGraph("res/UI/SelectItem/Selct/ui_gtotitle_01.png");
	_cgGControl = LoadGraph("res/UI/SelectItem/Selct/ui_gtotitle_01.png");
	_cgGAudio = LoadGraph("res/UI/SelectItem/Selct/ui_gtotitle_01.png");
	_cgGToTitle = LoadGraph("res/UI/SelectItem/Selct/ui_gtotitle_01.png");

	_selecting = 0;

	return true;
}

bool ModeMenu::Terminate() {
	base::Terminate();

	DeleteGraph(_cgMenuTitle);
	DeleteGraph(_cgMenuFrame01);
	DeleteGraph(_cgMenuFrame02);
	DeleteGraph(_cgMenuFrame03);
	DeleteGraph(_cgResume);
	DeleteGraph(_cgControl);
	DeleteGraph(_cgAudio);
	DeleteGraph(_cgToTitle);
	DeleteGraph(_cgGResume);
	DeleteGraph(_cgGControl);
	DeleteGraph(_cgGAudio);
	DeleteGraph(_cgGToTitle);

	return true;
}

bool ModeMenu::Process() {
	base::Process();

	auto trg = ApplicationMain::GetInstance()->GetPad()->GetTrgButton();

	// このモードより下のレイヤーはProcess()を呼ばない
	ModeServer::GetInstance()->SkipProcessUnderLayer();

	// ModeGameへ
	if (trg & INPUT_A) {
		// このモードを削除予約
		ModeServer::GetInstance()->Del(this);
	}

	//if (trg & INPUT__DPAD_LEFT) { _selecting--; }
	//if (trg & INPUT__DPAD_RIGHT) { _selecting++; }

	return true;
}

bool ModeMenu::Render() {
	base::Render();
	// フレーム、タイトルの描画
	DrawGraph(68, 44, _cgMenuTitle, TRUE);
	DrawGraph(95, 150, _cgMenuFrame01, TRUE);
	DrawGraph(530, 150, _cgMenuFrame02, TRUE);
	DrawGraph(1348, 150, _cgMenuFrame03, TRUE);
	// 選択項目
	DrawGraph(138, 177, _cgResume, TRUE);
	DrawGraph(138, 277, _cgControl, TRUE);

	return true;
}
