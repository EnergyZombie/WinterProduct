
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeStageConfirmation.h"

bool ModeTitle::Initialize() {
	if (!base::Initialize()) { return false; }

	_cg = LoadGraph("res/title.png");

	return true;
}

bool ModeTitle::Terminate() {
	DeleteGraph(_cg);
	base::Terminate();
	return true;
}

bool ModeTitle::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	if (trg & PAD_INPUT_A)	{
		// ���̃��[�h���폜�\��
		ModeServer::GetInstance()->Del(this);
		// ���̃��[�h��o�^
		ModeServer::GetInstance()->Add(new ModeStageConfirmation(), 1, "stage");
	}

	return true;
}

bool ModeTitle::Render() {
	base::Render();

	DrawGraph(0, 0, _cg, TRUE);

	return true;
}

