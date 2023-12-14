
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeStageConfirmation.h"

bool ModeTitle::Initialize() {
	if (!base::Initialize()) { return false; }

	_cg = LoadGraph("res/title.png");
	_cgTitle = LoadGraph("res/UI/タイトル/ui_title.png");
	_cgTget = LoadGraph("res/UI/タイトル/選択中/ui_mget.png");
	_cgStart = LoadGraph("res/UI/タイトル/選択肢/ui_start.png");
	_cgTexit = LoadGraph("res/UI/タイトル/選択肢/ui_texit.png");

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
	// 選択処理　一旦十字キーで選択する
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
	// どちらを選択してもモードを削除する
	if (close) {	
		// このモードを削除予約
		ModeServer::GetInstance()->Del(this);
	}
	// 終了フラグがfalseなら、次のモードを登録する
	if (close && !ApplicationMain::GetInstance()->GetEnd()) {
		// 次のモードを登録
		ModeServer::GetInstance()->Add(new ModeStageConfirmation(), 1, "stage");
	}


	return true;
}

bool ModeTitle::Render() {
	base::Render();

	DrawGraph(0, 0, _cg, TRUE);

	DrawGraph(448, 384, _cgTitle, TRUE);
	{	// 選択肢の描画
		int x = 832; int y = 768; int size = 64;
		DrawGraph(x, y, _cgStart, TRUE); y += size;
		DrawGraph(x, y, _cgTexit, TRUE);
		switch (_selecting) {	// 現在何を選択しているのか
		case 0:	// start
			y -= size; break;
		case 1:	// exit
			break;
		}
		DrawGraph(x, y, _cgTget, TRUE);	// 選択中の項目に重ねるやつ
	}

	return true;
}

