#include"ObjectServer.h"
#include"Player.h"
#include"ModeGame.h"
#include<algorithm>


ObjectServer::ObjectServer(ModeGame* game) {
	_game = game;
}

ObjectServer::~ObjectServer() {

}

bool ObjectServer::Initialize() {
	return true;
}

bool ObjectServer::Terminate() {
	//管理しているオブジェクトをすべて削除
	ClearObject();
	return true;
}

bool ObjectServer::Process() {
	//巡回処理をする前に追加と削除をしておく
	for (auto& add_obj : _add_obj) {
		_obj.emplace_back(add_obj);

	}
	_add_obj.clear();

	for (auto& delete_obj : _delete_obj) {
		auto itr = std::find(_obj.begin(), _obj.end(), delete_obj);
		if (itr != _obj.end()) {
			_obj.erase(itr);
			delete delete_obj;
		}
	}
	_delete_obj.clear();

	_player->Process();
	//オブジェクトを巡回処理
	for (auto& obj : _obj) {
		if (!obj->Process()) {
			return false;
		}
	}
	return true;
}

bool ObjectServer::Renderer() {
	//オブジェクトを巡回処理
	_player->Render();
	for (auto& obj : _obj) {
		ChangeLightTypePoint(VAdd(obj->GetDxPos(), VGet(0.f, 50.f, 0)), 1000.f, 0.f, 0.005f, 0.f);
		// コリジョン判定用ラインの描画
		//if(_game->GetMap()->_bViewCollision) {
		//	DrawLine3D(VAdd(obj->GetDxPos(), VGet(0, obj->_colSubY, 0)), VAdd(obj->GetDxPos(), VGet(0, -99999.f, 0)), GetColor(255, 0, 0));
		//}
		if (!obj->Render()) {
			return false;
		}
	}
	//DrawFormatString(0, 0, GetColor(255, 0, 0), "%d", _obj.size());
	return true;
}

void ObjectServer::AddObj(ObjectBase* obj) {
	
	//既に追加されているか
	auto itr = std::find(_obj.begin(), _obj.end(), obj);
	if (itr != _obj.end()) {
		return;
	}
	//まだ、追加されていないだけで予約は入っているのでは？
	itr = std::find(_add_obj.begin(), _add_obj.end(), obj);
	if (itr != _add_obj.end()) {
		return;
	}

	obj->Initialize();
	_add_obj.emplace_back(obj);
}

void ObjectServer::SetPlayer(Player* obj) {

	//既に追加されているか
	_player = obj;
	obj->Initialize();
}


void ObjectServer::DeleteObj(ObjectBase* obj) {
	//既に削除予約されているか
	auto itr = std::find(_delete_obj.begin(), _delete_obj.end(), obj);
	if (itr != _delete_obj.end()) {
		return;
	}
	_delete_obj.emplace_back(obj);
}

bool ObjectServer::ClearObject() {

	delete _player;
	_player = nullptr;

	for (auto& obj : _obj) {
		delete obj;
	}
	_obj.clear();
	for (auto& obj : _add_obj) {
		delete obj;
	}
	_add_obj.clear();
	for (auto& obj : _delete_obj) {
		delete obj;
	}
	_delete_obj.clear();
	return true;
}

