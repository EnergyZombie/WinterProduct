
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include"ObjectServer.h"
#include"Player.h"
#include"Camera.h"

bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }
	// マップ
	_map = new Map();
	_map->Initialize();

	_obj_server = new ObjectServer(this);
	_obj_server->Initialize();

	_camera = new Camera(this);
	_camera->SetPos(VGet(0, 50, 0));
	//camera->_vTarget = VGet(100, 100, 100);

	_map->LoadMap(this);

	return true;
}

bool ModeGame::Terminate() {

	base::Terminate();

	_obj_server->Terminate();
	delete _obj_server;
	delete _camera;
	delete _map;
	return true;
}

bool ModeGame::Process() {
	base::Process();

	_map->Process(this);
	if (!_obj_server->Process()) { return false; }
	
	_camera->Process();
	auto trg = GetPad()->GetKeyButton();
	//if (trg & INPUT_DPAD_UP) { camera->_vTarget.y -= 1; }
	//if (trg & INPUT_DPAD_DOWN) { camera->_vTarget.y += 1; }
			// デバッグ機能


	return true;
}

bool ModeGame::Render() {
	base::Render();
	// 3D基本設定
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

#if 0	// 平行ライト
	SetGlobalAmbientLight(GetColorF(0.5f, 0.f, 0.f, 0.f));
	ChangeLightTypeDir(VGet(-1, -1, 0));
#endif
#if 1	// ポイントライト
	SetGlobalAmbientLight(GetColorF(0.f, 0.f, 0.f, 0.f));
	
#endif

	// カメラの設定更新

	_camera->Matrix = MGetIdent();
	VECTOR cps = VScale(_obj_server->GetPlayer()->GetDxPos(), -1);
	 _camera->Matrix = MMult(_camera->Matrix, MGetTranslate(cps));
	 _camera->Matrix = MMult( _camera->Matrix, MGetRotY( _camera->RotateY));
	 _camera->Matrix = MMult( _camera->Matrix, MGetRotX( _camera->RotateX));
	 _camera->Matrix = MMult( _camera->Matrix, MGetTranslate(VGet(0, 0, 400)));

	 SetCameraViewMatrix(_camera->Matrix);

	SetCameraNearFar(10.0f, 10000.f);

	
	//マップ描画

	if(!_map->Renderer()) { return false; }

	if (!_obj_server->Renderer()) { return false; }
	//マップ替わり
	//for(int a = -100; a < 100; a++) {
	//	DrawLine3D(VGet(-10000,0, 100 * a), VGet(10000, 0, 100 * a), GetColor(255, 255, 255));
	//	DrawLine3D(VGet(100 * a,0, -10000), VGet(100 * a, 0, 10000), GetColor(255, 255, 255));
	//}


	////カメラ角度の表示
	//int x = 0, y = 0, size = 16;
	//SetFontSize(size);
	//DrawFormatString(x, y, GetColor(255, 0, 0), "Camera:"); y += size;
	//DrawFormatString(x, y, GetColor(255, 0, 0), "  target = (%5.2f, %5.2f, %5.2f)", _camera->GetTarget().x, _camera->GetTarget().y, _camera->GetTarget().z); y += size;
	//DrawFormatString(x, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _camera->GetPos().x, _camera->GetPos().y, _camera->GetPos().z); y += size;

	//DrawFormatString(0, 600, GetColor(255, 255, 255), "カメラXZ角度 %f", RadToDeg(_camera->_radXZ));
	//DrawFormatString(0, 620, GetColor(255, 0, 0), "入力 %d", GetPad()->GetKeyButton());

	return true;
}

XGamePad* ModeGame::GetPad()const { return ApplicationMain::GetInstance()->GetPad(); }