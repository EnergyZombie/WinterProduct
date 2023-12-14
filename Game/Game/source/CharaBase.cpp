#include"CharaBase.h"
#include"ObjectServer.h"
#include"ModeGame.h"
#include"Map.h"

bool	CharaBase::collision;

CharaBase::CharaBase(ObjectServer* server) :ObjectBase(server) {

}

bool CharaBase::IsHitMap(){
	auto map = GetObjectServer()->GetGame()->GetMap();

	//カプセル判定
	MV1_COLL_RESULT_POLY_DIM hitXZ = MV1CollCheck_Capsule(
		map->GetHandleMap(),
		map->GetCollisionIndex(),
		DxConverter::VecToDx(_pos + Vector3D(0, _radian, 0)),
		DxConverter::VecToDx(_pos + Vector3D(0, _radian + _colSubY, 0)),
		_radian
	);
	if (hitXZ.Dim) {

		double dist = 9999999999;

		Vector3D under_pos(_pos);
		under_pos.y += _radian;
		Vector3D up_pos(_pos);
		up_pos.y += (_colSubY + _radian);

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

		if (dist < _radian * _radian) {
			Vector3D latest_v(pol_latest_point - add_base_point);
			latest_v.Normalized();
			latest_v *= (_radian);
			Vector3D add((pol_latest_point - latest_v));
			_pos += (add - add_base_point);
		}

	}
	MV1CollResultPolyDimTerminate(hitXZ);

	for (auto& obj : GetObjectServer()->GetObjects()) {
		switch (obj->GetObjectType()) {
		case OBJECT_TYPE::kObject:
			IsPushedObject(obj);
			break;
		case OBJECT_TYPE::kChara:
			IsPushedChara((CharaBase*)obj);
			break;
		}
	}


	return true;
}

bool CharaBase::IsPushedObject(ObjectBase* obj) {
	MV1_COLL_RESULT_POLY hit = MV1CollCheck_Line(
		obj->GetHandle(),
		obj->GetAttachIndex(),
		DxConverter::VecToDx(_pos + Vector3D(0, 40, 0)),
		DxConverter::VecToDx(_pos + Vector3D(0, -20, 0))
	);
	if (hit.HitFlag) {
		// 当たった
		// 当たったY位置をキャラ座標にする
		_pos.y = hit.HitPosition.y;
	}

	MV1_COLL_RESULT_POLY_DIM  hitobj = MV1CollCheck_Capsule(
		obj->GetHandle(),
		obj->GetAttachIndex(),
		DxConverter::VecToDx(_pos + Vector3D(0, _radian, 0)),
		DxConverter::VecToDx(_pos + Vector3D(0, _radian + _colSubY, 0)),
		_radian
	);

	if (hitobj.Dim) {

		double dist = 9999999999;

		Vector3D under_pos(_pos);
		under_pos.y += _radian;
		Vector3D up_pos(_pos);
		up_pos.y += (_colSubY + _radian);

		Segment3D coll_seg(under_pos, up_pos);
		Vector3D pol_latest_point(0, 0, 0);
		Vector3D add_base_point(0, 0, 0);

		for (int a = 0; a < hitobj.HitNum; a++) {
			Polygon3D detection = Polygon3D(
				DxConverter::DxToVec(hitobj.Dim[a].Position[0]),
				DxConverter::DxToVec(hitobj.Dim[a].Position[1]),
				DxConverter::DxToVec(hitobj.Dim[a].Position[2])
			);

			SEGMENT_TRIANGLE_RESULT result = Collision::SegmentPolygonAnalyze(detection, coll_seg);

			double dist_com = result.Seg_Tri_MinDist_Square;

			if (dist_com < dist) {
				dist = dist_com;
				pol_latest_point = DxConverter::DxToVec(result.Tri_MinDist_Pos);
				add_base_point = DxConverter::DxToVec(result.Seg_MinDist_Pos);
			}
		}

		if (dist < _radian * _radian) {
			Vector3D latest_v(pol_latest_point - add_base_point);
			latest_v.Normalized();
			latest_v *= (_radian);
			Vector3D add((pol_latest_point - latest_v));
			_pos += (add - add_base_point);
		}



	}
	MV1CollResultPolyDimTerminate(hitobj);
	return true;
}

bool CharaBase::IsPushedChara(CharaBase* chara) {
	
	Vector3D this_chara_vector = _pos - chara->GetPos();

	float dis_sq = this_chara_vector.LengthSquare();

	float sum_radian = _radian + chara->GetRadian();

	float sum_radian_sq = sum_radian * sum_radian;

	if (sum_radian_sq > dis_sq) {
		_pos = chara->GetPos() + this_chara_vector.Normalize() * sum_radian;
	}

	return true;
}

void CharaBase::ProcessGravity() {
	auto map = GetObjectServer()->GetGame()->GetMap();
	//重力処理
	if (_gravity > -40.f) {
		_gravity -= 1.f;
	}
	_pos.y += _gravity;

	MV1_COLL_RESULT_POLY hit = MV1CollCheck_Line(
		map->GetHandleMap(),
		map->GetCollisionIndex(),
		DxConverter::VecToDx(_pos + Vector3D(0, _colSubY + _radian * 2, 0)),
		DxConverter::VecToDx(_pos + Vector3D(0, 0, 0))
	);
	if (hit.HitFlag) {
		// 当たった
		// 当たったY位置をキャラ座標にする
		if (_old_pos.y > _pos.y) {
			_pos.y = hit.HitPosition.y;
			_is_stand = true;
		}
		else {
			_pos.y = VSub(hit.HitPosition, VGet(0, _colSubY + _radian * 2, 0)).y;
		}
		_gravity = 0;
		_onObj = nullptr;
	}
	else {
		_is_stand = false;
		for (auto& obj : GetObjectServer()->GetObjects()) {
			MV1_COLL_RESULT_POLY hit = MV1CollCheck_Line(
				obj->GetHandle(),
				obj->GetAttachIndex(),
				DxConverter::VecToDx(_pos + Vector3D(0, _colSubY + _radian * 2, 0)),
				DxConverter::VecToDx(_pos + Vector3D(0, 0, 0))
			);
			if (hit.HitFlag) {

				if (hit.HitPosition.y > _pos.y) {

					_is_stand = true;

					_pos.y = hit.HitPosition.y + 1;

					_onObj = obj;

				}
				else {
					_pos.y = VSub(hit.HitPosition, VGet(0, _colSubY + _radian * 2, 0)).y;
				}
				_gravity = 0;
			}
		}
	}
}

bool CharaBase::Render() {
	if (Map::_bViewCollision) {
		DrawCapsule3D(
			VAdd(DxConverter::VecToDx(_pos), VGet(0, _colSubY + _radian, 0)),
			VAdd(DxConverter::VecToDx(_pos), VGet(0, _radian, 0)),
			_radian, 10,
			GetColor(255, 0, 0),
			GetColor(255, 255, 255),
			FALSE
		);

		DrawLine3D(
			DxConverter::VecToDx(_pos + Vector3D(0, _colSubY + _radian * 2, 0)),
			DxConverter::VecToDx(_pos + Vector3D(0, -1, 0)),
			GetColor(0, 0, 255)
		);
		DrawSphere3D(
			DxConverter::VecToDx(_pos),
			_radian,
			10,
			GetColor(0, 255, 0),
			GetColor(255, 255, 255),
			FALSE
		);
	}
	matrix = MGetIdent();
	matrix = MMult(matrix, MGetRotX(_euler_angle.x));
	matrix = MMult(matrix, MGetRotZ(_euler_angle.z));
	matrix = MMult(matrix, MGetRotY(_euler_angle.y + PI));
	matrix = MMult(matrix, MGetTranslate(DxConverter::VecToDx(_pos)));
	MV1SetMatrix(_handle, matrix);
	MV1SetAttachAnimTime(_handle, _attach_index, _play_time);
	MV1DrawModel(_handle);
	return true;
}