#include"ModeScript.h"
#include "ApplicationMain.h"



bool ModeScript::Initialize() {
	if (!base::Initialize()) { return false; }


	return true;
}

bool ModeScript::Terminate() {

	base::Terminate();
	return true;
}

bool ModeScript::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();
	// このモードより下のレイヤーはProcess()を呼ばない
	ModeServer::GetInstance()->SkipProcessUnderLayer();
	if (trg & PAD_INPUT_B) {
		// このモードを削除予約
		ModeServer::GetInstance()->Del(this);
	
	}

	return true;
}

bool ModeScript::Render() {
	base::Render();
	SetFontSize(64);
	int x = ApplicationMain::GetInstance()->DispSizeW() / 2 - _str.size() * 64 / 4;
	int y = ApplicationMain::GetInstance()->DispSizeH()/2 - 64 / 2;
	DrawBox(99, 99, ApplicationMain::GetInstance()->DispSizeW() - 99, 621, 0, TRUE);
	DrawBox(ApplicationMain::GetInstance()->DispSizeW() / 2 - 21, 300, ApplicationMain::GetInstance()->DispSizeW()/2 + 21 , 720, 0, TRUE);
	DrawBox(100, 100, ApplicationMain::GetInstance()->DispSizeW() - 100, 620, GetColor(255,255,255), TRUE);
	DrawBox(ApplicationMain::GetInstance()->DispSizeW() / 2 - 20, 300, ApplicationMain::GetInstance()->DispSizeW() / 2 + 20, 720, GetColor(255,255,255), TRUE);
	DrawFormatString(x, y, GetColor(255, 0, 0), "%s",_str.c_str());
	SetFontSize(16);
	return true;
}

