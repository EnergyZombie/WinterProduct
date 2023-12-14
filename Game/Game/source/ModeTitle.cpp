
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeStageConfirmation.h"

bool ModeTitle::Initialize() {
	if (!base::Initialize()) { return false; }

	_cg = LoadGraph("res/title.png");
	_cgTitle = LoadGraph("res/UI/�^�C�g��/ui_title.png");
	_cgTget = LoadGraph("res/UI/�^�C�g��/�I��/ui_mget.png");
	_cgStart = LoadGraph("res/UI/�^�C�g��/�I����/ui_start.png");
	_cgTexit = LoadGraph("res/UI/�^�C�g��/�I����/ui_texit.png");

	_itemNum = 2;
	_selecting = 0;

	return true;
}

bool ModeTitle::Terminate() {
	base::Terminate();

	DeleteGraph(_cg);
	DeleteGraph(_cgTitle);
	DeleteGraph(_cgTget);
	DeleteGraph(_cgStart);
	DeleteGraph(_cgTexit);

	return true;
}

bool ModeTitle::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	bool close = false;
	// �I�������@��U�\���L�[�őI������
	if (trg & PAD_INPUT_UP) { _selecting--; }
	if (trg & PAD_INPUT_DOWN) { _selecting++; }
	_selecting = (_selecting + _itemNum) % _itemNum;
	switch (_selecting) {
	case 0:
		if (trg & PAD_INPUT_A) { close = true; } break;
	case 1:
		if (trg & PAD_INPUT_A) {
			ApplicationMain::GetInstance()->GameEnd();
			close = true;
		}
		break;
	}
	// �ǂ����I�����Ă����[�h���폜����
	if (close) {	
		// ���̃��[�h���폜�\��
		ModeServer::GetInstance()->Del(this);
	}
	// �I���t���O��false�Ȃ�A���̃��[�h��o�^����
	if (close && !ApplicationMain::GetInstance()->GetEnd()) {
		// ���̃��[�h��o�^
		ModeServer::GetInstance()->Add(new ModeStageConfirmation(), 1, "stage");
	}


	return true;
}

bool ModeTitle::Render() {
	base::Render();

	DrawGraph(0, 0, _cg, TRUE);

	DrawGraph(448, 384, _cgTitle, TRUE);
	{	// �I�����̕`��
		int x = 832; int y = 768; int size = 64;
		DrawGraph(x, y, _cgStart, TRUE); y += size;
		DrawGraph(x, y, _cgTexit, TRUE);
		switch (_selecting) {	// ���݉���I�����Ă���̂�
		case 0:	// start
			y -= size; break;
		case 1:	// exit
			break;
		}
		DrawGraph(x, y, _cgTget, TRUE);	// �I�𒆂̍��ڂɏd�˂���
	}

	return true;
}

