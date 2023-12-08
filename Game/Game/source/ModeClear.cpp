#include"ModeClear.h"
#include"ModeTitle.h"
#include "ApplicationMain.h"

bool ModeClear::Initialize() {
	return true;
}

bool ModeClear::Terminate() {

	return true;
}

bool ModeClear::Process() {
	base::Process();

	// ���̃��[�h��艺�̃��C���[��Process()���Ă΂Ȃ�
	ModeServer::GetInstance()->SkipProcessUnderLayer();

	auto trg = ApplicationMain::GetInstance()->GetPad()->GetTrgButton();

	if (trg & INPUT_A) { 
		// ���̃��[�h���폜�\��
		ModeServer::GetInstance()->Clear();
		// ���̃��[�h��o�^
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	}

	return true;
}

bool ModeClear::Render() {
	base::Render();
	SetFontSize(64);


	std::string str = "clear";
	int x = ApplicationMain::GetInstance()->DispSizeW()/2 - str.size() * 64 / 4;
	int y = ApplicationMain::GetInstance()->DispSizeH()/2 - 64 / 2;
	DrawFormatString(x, y, GetColor(255, 0, 0), "%s",str.c_str());
	SetFontSize(16);
	return true;
}