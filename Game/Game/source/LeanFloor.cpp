#include"LeanFloor.h"
#include"ModeGame.h"
#include"ObjectServer.h"
#include"Map.h"
#include"Player.h"

LeanFloor::LeanFloor(ObjectServer* server):ObjectBase(server) {

}

LeanFloor::~LeanFloor(){}

bool LeanFloor::Initialize() { 
	_handle = MV1LoadModel("res/Object/lean_floor.mv1");
	_attach_index = MV1SearchFrame(_handle, "立方体");
	//MV1SetRotationXYZ(_handle,VGet(0,0,-1));
	MV1SetupCollInfo(_handle, _attach_index, 8, 8, 8);

	_is_lean = 0;
	ObjectBase::Initialize();
	return true; 
}

bool LeanFloor::Process() {
	_old_pos = _pos;

	MV1RefreshCollInfo(_handle, _attach_index);

	if (GetObjectServer()->GetPlayer()->GetOnObject() == this) {
		//GetObjectServer()->GetPlayer()->AddPos(_pos - _old_pos);
		_is_lean = true;
	}

	double rad = GetObjectServer()->GetPlayer()->GetRadian();
	double colsub = GetObjectServer()->GetPlayer()->_colSubY;
	auto pos = GetObjectServer()->GetPlayer()->GetPos();

	//これはGmickクラスを作って共通化するか、処理用クラスを作った方がいい
	MV1_COLL_RESULT_POLY_DIM hitXZ = MV1CollCheck_Capsule(
		_handle,
		_attach_index,
		DxConverter::VecToDx(pos + Vector3D(0, rad, 0)),
		DxConverter::VecToDx(pos + Vector3D(0, rad + colsub, 0)),
		rad
	);
	if (hitXZ.Dim) {

		double dist = 9999999999;

		Vector3D under_pos(pos);
		under_pos.y += rad;
		Vector3D up_pos(pos);
		up_pos.y += (colsub + rad);

		Segment3D coll_seg(under_pos, up_pos);
		Vector3D pol_latest_point(0, 0, 0);
		Vector3D add_base_point(0, 0, 0);

		for (int a = 0; a < hitXZ.HitNum; a++) {
			Polygon3D detection = Polygon3D(
				DxConverter::DxToVec(hitXZ.Dim[a].Position[0]),
				DxConverter::DxToVec(hitXZ.Dim[a].Position[1]),
				DxConverter::DxToVec(hitXZ.Dim[a].Position[2])
			);

			SEGMENT_TRIANGLE_RESULT result = Collision::SegmentPolygonAnalyze(detection, coll_seg);

			double dist_com = result.Seg_Tri_MinDist_Square;

			if (dist_com < dist) {
				dist = dist_com;
				pol_latest_point = DxConverter::DxToVec(result.Tri_MinDist_Pos);
				add_base_point = DxConverter::DxToVec(result.Seg_MinDist_Pos);
			}
		}

		if (dist < rad * rad) {
			Vector3D latest_v(pol_latest_point - add_base_point);
			latest_v.Normalized();
			latest_v *= (rad);
			Vector3D add((pol_latest_point - latest_v));
			GetObjectServer()->GetPlayer()->AddPos(add - add_base_point);
		}

	}
	MV1CollResultPolyDimTerminate(hitXZ);
	ObjectBase::Initialize();
	return true;
}

