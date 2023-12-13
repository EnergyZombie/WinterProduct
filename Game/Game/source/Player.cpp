#include"Player.h"
#include"ObjectServer.h"
#include"ModeGame.h"
#include"appframe.h"
#include<vector>
#include<algorithm>
#include"Camera.h"


Player::Player(ObjectServer* server):CharaBase(server) {

}

Player::~Player() {

}

bool Player::Initialize() {
		// モデルデータのロード（テクスチャも読み込まれる）
	_object_type = OBJECT_TYPE::kChara;
	_handle = MV1LoadModel("res/SDChar/SDChar.mv1");
	// 3Dモデルの1番目のアニメーションをアタッチする
	_attach_index = 0;
	// アタッチしたアニメーションの総再生時間を取得する
	_total_time = 0.f;
	// 再生時間の初期化
	_play_time = 0.0f;

	_gravity = 0.f;
	_is_stand = true;
	_colSubY = 40.f;

	_radian = 30;

	MV1SetAttachAnimTime(_handle, _attach_index, _play_time);

	_action_state = ACTION_STATE::kIdle;

	ObjectBase::Initialize();
	return true;
}

bool Player::Process() {


	ACTION_STATE old_state = _action_state;

	auto pad = GetObjectServer()->GetGame()->GetPad();
	auto camera = GetObjectServer()->GetGame()->GetCamera();

	_old_pos = _pos;

	ProcessGravity();
	
	if (pad->IsInputLeftStick()) {
		_euler_angle.y = atan2((float)pad->GetLeftStick().x,(float)pad->GetLeftStick().y);
		_euler_angle.y -= camera->RotateY;

	
		Vector3D vDir(0, 0, 0);
		vDir.x = sin(_euler_angle.y);
		vDir.z = cos(_euler_angle.y);
		vDir.Normalized();

		_pos += vDir * 5.f;

		_euler_angle = Vector3D(0, _euler_angle.y, 0);

		_action_state = ACTION_STATE::kWalk;

	}
	else{ _action_state = ACTION_STATE::kIdle; }

	//ジャンプ処理
	if (_is_stand && pad->GetTrgButton() & INPUT_A) {
		_gravity += 25;
		_is_stand = false;
	}

	//移動
	if (_move.Length() > 0.1) {
		_pos += _move;
		_move *= 0.8;
	}
	else {
		_move *= 0;
	}

	//押し出し判定
	if (_old_pos != _pos) {
		IsHitMap();
	}

	// ステータスが変わっていないか？
	if(old_state == _action_state) {
		// 再生時間を進める
		_play_time += 0.5f;
	}
	else {
		// アニメーションがアタッチされていたら、デタッチする
		if(_attach_index != -1) {
			MV1DetachAnim(_handle, _attach_index);
			_attach_index = -1;
		}
		// ステータスに合わせてアニメーションのアタッチ
		switch(_action_state) {
		case ACTION_STATE::kIdle:
			_attach_index = MV1AttachAnim(_handle, MV1GetAnimIndex(_handle, "idle"), -1, FALSE);
			break;
		case ACTION_STATE::kWalk:
			_attach_index = MV1AttachAnim(_handle, MV1GetAnimIndex(_handle, "run"), -1, FALSE);
			break;
		}
		// アタッチしたアニメーションの総再生時間を取得する
		_total_time = MV1GetAttachAnimTotalTime(_handle, _attach_index);
		// 再生時間を初期化
		_play_time = 0.0f;
	}

	// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
	if(_play_time >= _total_time) {
		_play_time = 0.0f;
	}
	ObjectBase::Process();
	return true;
}

bool Player::Render() {
	if (CharaBase::Render()) {

	}
	//DrawFormatString(
	//	0, 0, GetColor(255, 0, 0),
	//	"%fl %fl %fl",
	//	DxConverter::VecToDx(_pos).x,
	//	DxConverter::VecToDx(_pos).y,
	//	DxConverter::VecToDx(_pos).z,
	//	TRUE
	//	);
	//if (_is_stand) {
	//	DrawFormatString(0, 25, GetColor(255, 0, 0), "stand");
	//}

	return true;
}
