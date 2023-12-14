
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeMenu.h"
#include "ModeTitle.h"
#include <cmath>

bool ModeMenu::Initialize() {
	if (!base::Initialize()) { return false; }

	_cgMenuTitle = LoadGraph("res/UI/���j���[/�t���[��/ui_menutitle.png");
	_cgMenuFrame01 = LoadGraph("res/UI/���j���[/�t���[��/ui_menuframe_01.png");
	_cgMenuFrame02 = LoadGraph("res/UI/���j���[/�t���[��/ui_menuframe_02.png");
	_cgMenuFrame03 = LoadGraph("res/UI/���j���[/�t���[��/ui_menuframe_03.png");

	_cgMGet = LoadGraph("res/UI/���j���[/�I������/�I��/ui_mget.png");
	_cgResume = LoadGraph("res/UI/���j���[/�I������/���I��/ui_mresume.png");
	_cgControl = LoadGraph("res/UI/���j���[/�I������/���I��/ui_mcontrol.png");
	_cgAudio = LoadGraph("res/UI/���j���[/�I������/���I��/ui_maudio.png");
	_cgToTitle = LoadGraph("res/UI/���j���[/�I������/���I��/ui_mtotitle.png");

	_itemNum = 4;
	_selecting = 0;
	_blendPal = 0;

	return true;
}

bool ModeMenu::Terminate() {
	base::Terminate();

	DeleteGraph(_cgMenuTitle);
	DeleteGraph(_cgMenuFrame01);
	DeleteGraph(_cgMenuFrame02);
	DeleteGraph(_cgMenuFrame03);
	DeleteGraph(_cgMGet);
	DeleteGraph(_cgResume);
	DeleteGraph(_cgControl);
	DeleteGraph(_cgAudio);
	DeleteGraph(_cgToTitle);

	return true;
}

void ModeMenu::Clear() {
	// �o�^����item��S���폜����
	for (auto ite = _vItems.begin(); ite != _vItems.end();) {
		delete (*ite);
		ite = _vItems.erase(ite);
	}
}

void ModeMenu::Add(MenuItemBase* itemBase) {
	_vItems.push_back(itemBase);
}

bool ModeMenu::Process() {
	base::Process();

	auto trg = ApplicationMain::GetInstance()->GetPad()->GetTrgButton();

	// ���̃��[�h��艺�̃��C���[��Process()���Ă΂Ȃ�
	ModeServer::GetInstance()->SkipProcessUnderLayer();

	bool close = false;
	bool title = false;
	// ���j���[�����
	if (trg & INPUT_A) { close = true; }

	// �I�������@��U�\���L�[�őI������
	if (trg & INPUT_DPAD_UP) { _selecting--; }
	if (trg & INPUT_DPAD_DOWN) { _selecting++; }
	_selecting = (_selecting + _itemNum) % _itemNum;

	switch (_selecting) {
	case 3:
		if (trg & INPUT_A) { title = true; } break;
	}

	// ModeGame��
	// ���̃��[�h���폜�\��
	if (close) { ModeServer::GetInstance()->Del(this); }
	if (title) { 
		ModeServer::GetInstance()->Clear(); 
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	}

	return true;
}

bool ModeMenu::Render() {
	base::Render();
	{	// �t���[���A�^�C�g���̕`��
		int y = 150;
		DrawGraph(68, 44, _cgMenuTitle, TRUE);
		DrawGraph(95, y, _cgMenuFrame01, TRUE);
		DrawGraph(530, y, _cgMenuFrame02, TRUE);
		DrawGraph(1348, y, _cgMenuFrame03, TRUE);
	}
	{	// �I������
		int x = 138; int y = 177;
		DrawGraph(x, y, _cgResume, TRUE); y += 100;
		DrawGraph(x, y, _cgControl, TRUE); y += 100;
		DrawGraph(x, y, _cgAudio, TRUE); y += 497;
		DrawGraph(x, y, _cgToTitle, TRUE);
		switch (_selecting) {
		case 0:
			y = 177; break;
		case 1:
			y = 277; break;
		case 2:
			y = 377; break;
		case 3:
			y = 874; break;
		}
		//if (_blendPal < 255) _blendPal++;
		//else if (_blendPal >= 0) _blendPal--;
		//_blendPal = 0.5 + 0.5 * sin(2.0 * PI * (GetNowCount() / 1.7));
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, _blendPal);
		DrawGraph(x, y, _cgMGet, TRUE);
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	return true;
}
