#include"ModeGameOver.h"
#include "ApplicationMain.h"
#include"ModeGame.h"

bool ModeGameOver::Initialize() {
	return true;
}

bool ModeGameOver::Terminate() {
	return true;
}

bool ModeGameOver::Process() {
	base::Process();

	// ���̃��[�h��艺�̃��C���[��Process()���Ă΂Ȃ�
	ModeServer::GetInstance()->SkipProcessUnderLayer();

	auto trg = ApplicationMain::GetInstance()->GetPad()->GetTrgButton();

	if (trg & INPUT_A) {
		// ���̃��[�h���폜�\��
		ModeServer::GetInstance()->Clear();
		// ���̃��[�h��o�^
		ModeServer::GetInstance()->Add(new ModeGame(), 1, "game");
	}
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
	return true;
}