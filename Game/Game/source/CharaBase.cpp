#include"CharaBase.h"
#include"ObjectServer.h"
#include"ModeGame.h"
#include"Map.h"

CharaBase::CharaBase(ObjectServer* server) :ObjectBase(server) {

}

bool CharaBase::IsHitMap(){
	auto map = GetObjectServer()->GetGame()->GetMap();

	//カプセル判定
	MV1_COLL_RESULT_POLY_DIM hitXZ = MV1CollCheck_Capsule(
		map->GetHandleMap(),
		map->GetCollisionIndex(),
		DxConverter::VecToDx(_pos + Vector3D(0, radian, 0)),
		DxConverter::VecToDx(_pos + Vector3D(0, radian + _colSubY, 0)),
		radian
	);
	if (hitXZ.Dim) {

		double dist = 9999999999;

		Vector3D under_pos(_pos);
		under_pos.y += radian;
		Vector3D up_pos(_pos);
		up_pos.y += (_colSubY + radian);

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

		if (dist < radian * radian) {
			Vector3D latest_v(pol_latest_point - add_base_point);
			latest_v.Normalized();
			latest_v *= (radian);
			Vector3D add((pol_latest_point - latest_v));
			_pos += (add - add_base_point);
		}

	}
	MV1CollResultPolyDimTerminate(hitXZ);

	for (auto obj : GetObjectServer()->GetObjects()) {
		MV1_COLL_RESULT_POLY_DIM  hitobj = MV1CollCheck_Capsule(
			obj->GetHandle(),
			obj->GetAttachIndex(),
			DxConverter::VecToDx(_pos + Vector3D(0, radian, 0)),
			DxConverter::VecToDx(_pos + Vector3D(0, radian + _colSubY, 0)),
			radian
		);

		if (hitobj.Dim) {

			double dist = 9999999999;

			Vector3D under_pos(_pos);
			under_pos.y += radian;
			Vector3D up_pos(_pos);
			up_pos.y += (_colSubY + radian);

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

			if (dist < radian * radian) {
				Vector3D latest_v(pol_latest_point - add_base_point);
				latest_v.Normalized();
				latest_v *= (radian);
				Vector3D add((pol_latest_point - latest_v));
				_pos += (add - add_base_point);
			}

		}
		MV1CollResultPolyDimTerminate(hitobj);
	}

	MV1_COLL_RESULT_POLY hit = MV1CollCheck_Line(
		map->GetHandleMap(),
		map->GetCollisionIndex(),
		DxConverter::VecToDx(_pos + Vector3D(0, 40, 0)),
		DxConverter::VecToDx(_pos + Vector3D(0, -20, 0))
	);
	if (hit.HitFlag) {
		// 当たった
		// 当たったY位置をキャラ座標にする
		_pos.y = hit.HitPosition.y;

	}

	for (auto& obj : GetObjectServer()->GetObjects()) {
		hit = MV1CollCheck_Line(
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
	}

	return true;
}

bool CharaBase::Renderer() {
	matrix = MGetIdent();
	matrix = MMult(matrix, MGetRotX(_euler_angle.x));
	matrix = MMult(matrix, MGetRotZ(_euler_angle.z));
	matrix = MMult(matrix, MGetRotY(_euler_angle.y));
	matrix = MMult(matrix, MGetTranslate(DxConverter::VecToDx(_pos)));
	MV1SetMatrix(_handle, matrix);
	MV1SetAttachAnimTime(_handle, _attach_index, _play_time);
	MV1DrawModel(_handle);
	return true;
}