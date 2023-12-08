#include"GoalFloor.h"
#include"ModeGame.h"
#include"ObjectServer.h"
#include"Map.h"
#include"Player.h"
#include"ModeClear.h"
GoalFloor::GoalFloor(ObjectServer* server):ObjectBase(server) {
}

GoalFloor::~GoalFloor(){}

bool GoalFloor::Initialize() {

	_handle = MV1LoadModel("res/Object/clear.mv1");
	_attach_index = MV1SearchFrame(_handle, "—§•û‘Ì");
	MV1SetupCollInfo(_handle, _attach_index, 8, 8, 8);
	ObjectBase::Initialize();
	return true;
}

bool GoalFloor::Process() {

	auto player = GetObjectServer()->GetPlayer();

	VECTOR p = player->GetDxPos();
	p.y += player->GetRadian();
	VECTOR p2 = p;
	p2.y += player->GetCollSubY();
	//Ÿ”s”»’è
	MV1RefreshCollInfo(_handle, _attach_index);
	MV1_COLL_RESULT_POLY_DIM hit;
	hit = MV1CollCheck_Capsule(this->_handle, this->_attach_index,
		p, p2, player->GetRadian());

	
	if (hit.HitNum > 0) {
		ModeServer::GetInstance()->Add(new ModeClear(), 99, "clear");
	}
	MV1CollResultPolyDimTerminate(hit);
	
	ObjectBase::Process();
	
	return true;
}