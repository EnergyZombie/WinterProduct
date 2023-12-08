#include"Map.h"
#include"DxLib.h"
#include"ApplicationMain.h"
#include"ModeGame.h"
#include"Player.h"
#include"ObjectServer.h"
#include"ModeClear.h"
#include"ModeGameOver.h"
#include"../../../include/nlohmann/json.hpp"
#include<fstream>
#include"FallWall.h"
#include"GoalFloor.h"
#include"LeanFloor.h"
#include"SignBoard.h"

bool	Map::_bViewCollision;

bool Map::Initialize() {
	_handleSkySphere = MV1LoadModel("res/SkySphere/skysphere.mv1");
#if 0
	// ダンジョン
	_handleMap = MV1LoadModel("res/Dungeon/map.mv1");

	// コリジョン情報の生成
	_frameMapCollision = MV1SearchFrame(_handleMap, "map_collision");
	MV1SetupCollInfo(_handleMap, _frameMapCollision, 16, 16, 16);
	// コリジョンのフレームを描画しない設定
	//MV1SetFrameVisible(_handleMap, _frameMapCollision, FALSE);
#else
	// フィールド
	_handleMap = MV1LoadModel("res/map.mv1");
	_frameMapCollision = MV1SearchFrame(_handleMap, "map");


#endif
	// コリジョン情報の生成

	MV1SetupCollInfo(_handleMap, _frameMapCollision, 16, 16, 16);
	MV1SetFrameVisible(_handleMap, _frameMapCollision, TRUE);

	_graph = LoadGraph("res/cursor.png");


	_is_over = false;

	_bViewCollision = false;

	return true;
}

bool Map::Process(ModeGame* game) {

	auto pad = game->GetPad();
	 //デバッグ機能
	if (pad->GetTrgButton() & INPUT_BACK) {
		_bViewCollision = !_bViewCollision;
	}
	//if (_bViewCollision) {
	//	MV1SetFrameVisible(_handleMap, _frameMapCollision, TRUE);
	//}
	//else {
	//	MV1SetFrameVisible(_handleMap, _frameMapCollision, FALSE);
	//}

	if (game->GetObjectServer()->GetPlayer()->GetPos().y < -500) {
		ModeServer::GetInstance()->Add(new ModeGameOver(), 99, "gameover");
	}


	return true;
}

bool Map::Renderer(){

	MV1DrawModel(_handleMap);
	MV1DrawModel(_handleSkySphere);

	//DrawBillboard3D(VGet(0, 100, 0),0.5f, 0.5f, 100, DegToRad(180), _graph, false);
	return true;
}

bool Map::LoadMap(ModeGame* game) {

	nlohmann::json j;
	std::ifstream file("res/map/map.json");

	if (!file) { return false; }
	file >> j;

	for (auto object : j.at("Objects")) {

		ObjectBase* obj = nullptr;

		std::string name = object.at("name");

		if ("Player" == name) {
			Player* p = new Player(game->GetObjectServer());
			game->GetObjectServer()->SetPlayer(p);
			p->SetPos(Vector3D(object.at("position").at("x"), object.at("position").at("y"), object.at("position").at("z")));
		}
		else if ("Wall" == name) {
			obj = new FallWall(game->GetObjectServer());
		}
		else if ("Clear" == name) {
			obj = new GoalFloor(game->GetObjectServer());
		}
		else if ("LeanFloor" == name) {
			obj = new LeanFloor(game->GetObjectServer());
		}
		else if ("SignBoard" == name) {
			obj = new SignBoard(game->GetObjectServer());
		}

		//情報を入れる
		if (obj) {
			obj->SetPos(Vector3D(object.at("position").at("x"), object.at("position").at("y"), object.at("position").at("z")));
			obj->SetEulerAngle(Vector3D(object.at("euler_angle").at("x"), object.at("euler_angle").at("y"), object.at("euler_angle").at("z")));
			game->GetObjectServer()->AddObj(obj);
		}
	}
	
	return true;
}


//MV1_COLL_RESULT_POLY Map::CheckHitMap(ObjectBase* obj) {
//
//}
