#pragma once
#include"Capsule.h"
#include"Polygon.h"
#include"DxLib.h"
#include"Plane3D.h"

constexpr auto zero_com = 0.00001;

//参考サイト


class DxConverter {
public:
	static VECTOR VecToDx(Vector3D v1) {
		return VGet(v1.x, v1.y, v1.z);
	}

	static Vector3D DxToVec(VECTOR v) {
		return Vector3D(v.x, v.y,v.z);
	}

};

class Collision {
public:
	static void clamp01(double& v) {
		if (v < 0.0)
			v = 0.0;
		else if (v > 1.0)
			v = 1.0;
	}

	

	static const double SegPointDist(Vector3D p, Segment3D s ,double& t, bool is_draw = false) {

		Vector3D v1 = p - s.start_point;
		Vector3D v2 = s.end_point - s.start_point;

		t = v1.Dot(v2) / v2.Dot(v2);

		Vector3D result(s.start_point + v2 * t);

		if (v1.Dot(v2) < 0.0f) {
			result = s.start_point;
		}
		else if (Vector3D::Dot(p - s.end_point, s.start_point - s.end_point) < 0.0f) {
			result = s.end_point;
		}

		if (is_draw) {

			DrawLine3D(
				DxConverter::VecToDx(p),
				DxConverter::VecToDx(result),
				GetColor(255, 0, 0)
			);
		}

		return Vector3D::Length(result, p);
	}

	static const Vector3D SegPointLatestPoint(Vector3D p, Segment3D s) {

		Vector3D v1 = p - s.start_point;
		Vector3D v2 = s.end_point - s.start_point;

		double t = v1.Dot(v2) / v2.Dot(v2);

		Vector3D result(s.start_point + v2 * t);

		if (v1.Dot(v2) < 0.0) {
			result = s.start_point;
		}
		else if (Vector3D::Dot(p - s.end_point, s.start_point - s.end_point) < 0.0) {
			result = s.end_point;
		}

		return result;
	}

	static bool Parallel(Segment3D seg1, Segment3D seg2) {

		Vector3D v1(seg1.end_point - seg1.start_point);
		Vector3D v2(seg2.end_point - seg2.start_point);

		Vector3D c = v1.Cross(v2);

		double d = c.Length();

		return -zero_com < d && d < zero_com;
	}

	static double SegPointCoefficient(Vector3D p, Segment3D s) {
		Vector3D v1 = p - s.start_point;
		Vector3D v2 = s.end_point - s.start_point;

		return v1.Dot(v2) / v2.Dot(v2);
	}

	static double LineLineDist(Segment3D s1, Segment3D s2,double& t1,double& t2 ,Segment3D& r) {

		//VECTOR v1 = VSub(s1.e, s1.s);
		//VECTOR v2 = VSub(s2.e, s2.s);


		
		Vector3D v1 = s1.Vector();
		Vector3D v2 = s2.Vector();

		double DV1V2 = v1.Dot(v2);
		double DV1V1 = v1.Dot(v1);
		double DV2V2 = v2.Dot(v2);

		Vector3D P21P11 = s1.start_point - s2.start_point;

		t1 = (DV1V2 * v2.Dot(P21P11) - DV2V2 * v1.Dot(P21P11)) / (DV1V1 * DV2V2 - DV1V2 * DV1V2);
		Vector3D p1 = s1.start_point + (v1 * t1);
		t2 = v2.Dot(p1 - s2.start_point);
		Vector3D p2 = s2.start_point + (v2 * t2);

		r = Segment3D(p1, p2);
		
		return Vector3D(p2 - p1).Length();

	}

	static double SegSegDist(Segment3D s1, Segment3D s2,bool is_draw = false) {

		double t1 = 0.0;
		double t2 = 0.0;

		Segment3D result;

		if (Collision::Parallel(s1, s2)) {
			t1 = 0.0;
			double len = SegPointDist(s1.start_point, s2,t2);
			result.start_point = s1.start_point;
			result.end_point = s2.start_point + s2.Vector() * t2;
			if (0.0 <= t2 && t2 <= 1.0) {
		/*		if (is_draw) {
					DrawLine3D(
						DxConverter::VecToDx(result.start_point),
						DxConverter::VecToDx(result.end_point),
						GetColor(255, 0, 0)
					);
					DrawFormatString(result.start_point.x, result.start_point.y, GetColor(255, 255, 255), "s");
					DrawFormatString(result.end_point.x, result.end_point.y, GetColor(255, 255, 255), "e");
				}
				DrawFormatString(0, 100, GetColor(255, 255, 255), "1");*/
				return len;
			}
		}
		else {
			double len = LineLineDist(s1, s2, t1, t2,result);

			if (
				0.0f <= t1 && t1 <= 1.0f &&
				0.0f <= t2 && t2 <= 1.0f
				) {
			/*	if (is_draw) {
					DrawLine3D(
						DxConverter::VecToDx(result.start_point),
						DxConverter::VecToDx(result.end_point),
						GetColor(255, 0, 0)
					);
					DrawFormatString(result.start_point.x, result.start_point.y, GetColor(255, 255, 255), "s");
					DrawFormatString(result.end_point.x, result.end_point.y, GetColor(255, 255, 255), "e");
					DrawFormatString(0, 100, GetColor(255, 255, 255), "2");
				}*/
				return len;
			}
		}

		Vector3D v1(s1.Vector());
		Vector3D v2(s2.Vector());

		clamp01(t1);
		result.start_point = s1.start_point + (v1 * t1);
		double len = SegPointDist(result.start_point, s2, t2);

		//calcPointSegmentDist(p1, s2, p2, t2);
		if (0.0f <= t2 && t2 <= 1.0f) {

			result.end_point = s2.start_point + s2.Vector() * t2;
	/*		if (is_draw) {
				DrawLine3D(
					DxConverter::VecToDx(result.start_point),
					DxConverter::VecToDx(result.end_point),
					GetColor(255, 0, 0)
				);
				DrawFormatString(result.start_point.x, result.start_point.y, GetColor(255, 255, 255), "s");
				DrawFormatString(result.end_point.x, result.end_point.y, GetColor(255, 255, 255), "e");
			}
			DrawFormatString(0, 100, GetColor(255, 255, 255), "3");*/
			return len;
		}

		// S2側が外だったのでS2側をクランプ、S1に垂線を降ろす
		clamp01(t2);
		result.end_point = s2.start_point + (v2* t2);
		len = SegPointDist(result.end_point, s1, t1);
		if (0.0f <= t1 && t1 <= 1.0f) {

			result.start_point = s1.start_point + s1.Vector() * t1;
			if (is_draw) {
		/*		DrawLine3D(
					DxConverter::VecToDx(result.start_point),
					DxConverter::VecToDx(result.end_point),
					GetColor(255, 0, 0)*/
		/*		);
				DrawFormatString(result.start_point.x, result.start_point.y, GetColor(255, 255, 255), "s");
				DrawFormatString(result.end_point.x, result.end_point.y, GetColor(255, 255, 255), "e");*/
			}
		/*	DrawFormatString(0, 100, GetColor(255, 255, 255), "4");*/
			return len;
		}

		// 双方の端点が最短と判明
		clamp01(t1);
		result.start_point = s1.start_point + (v1 * t1);
		if (is_draw) {
		/*	DrawLine3D(*/
		/*		DxConverter::VecToDx(result.start_point),
				DxConverter::VecToDx(result.end_point),
				GetColor(255, 0, 0)
			);*/
			//DrawFormatString(result.start_point.x, result.start_point.y, GetColor(255, 255, 255), "s");
			//DrawFormatString(result.end_point.x, result.end_point.y, GetColor(255, 255, 255), "e");
			//DrawFormatString(0, 100, GetColor(255, 255, 255), "5");
		}
		return result.Length();
	}

	static bool CapCapHit(Capsule3D cap1, Capsule3D cap2, bool is_draw = false) {
		double r = SegSegDist(cap1.seg, cap2.seg,is_draw);

		if (r <= cap1.radius + cap2.radius) {
			return true;
		}
		return false;
	}

	static double PointPolygonDist(Polygon3D pol, Vector3D point) {
		double d = -Vector3D::Dot(pol.NormalVector(), pol.ver1);

		return Vector3D::Dot(point, pol.NormalVector()) - d;
	}

	static double SegPolygonDistSq(Segment3D s, Polygon3D pol) {
		return (double)Segment_Triangle_MinLength_Square(
		DxConverter::VecToDx(s.start_point),
		DxConverter::VecToDx(s.end_point),
		DxConverter::VecToDx(pol.ver1),
		DxConverter::VecToDx(pol.ver2),
		DxConverter::VecToDx(pol.ver3)
		);
	}

	static double SegPolygonDist(Segment3D s, Polygon3D pol) {
		return sqrt(SegPolygonDistSq(s, pol));
	}

	static Vector3D PointPolygonVec(Polygon3D pol, Vector3D p) {
		return DxConverter::DxToVec(Plane_Point_MinLength_Position(
			DxConverter::VecToDx(pol.ver1),
			DxConverter::VecToDx(Vector3D(pol.NormalVector()).Normalize()),
			DxConverter::VecToDx(p)
		));
	}

	static Plane3D PolToPlane(Polygon3D pol) {
		Vector3D ab = pol.ver2 - pol.ver1;
		Vector3D bc = pol.ver3 - pol.ver2;

		Vector3D normal = Vector3D::Cross(ab, bc);
		
		return Plane3D(pol.ver1, normal.Normalize());
	}

	static double PolToPointDist(Vector3D A, Vector3D P, Vector3D N);

	static Vector3D NearPosOnPlane(Vector3D A, Vector3D P, Vector3D N)
	{
		//PAベクトル(A-P)
		Vector3D PA(A-P);

		//法線NとPAを内積
		//法線の順方向に点Aがあればd > 0、 逆方向だとd < 0
		Vector3D normal(N.Normalize());

		double d = Vector3D::Dot(normal, PA);

		//内積値から平面上の最近点を求める
		normal *= d;
		Vector3D ret(A - normal);

		return ret;
	}

	static bool IsHitPointPolygon(Polygon3D pol, Vector3D P) {

		//点と三角形は同一平面上にあるものとしています。同一平面上に無い場合は正しい結果になりません
		//線上は外とみなします。
		//ABCが三角形かどうかのチェックは省略...

		Vector3D AB = pol.ver2 - pol.ver1;
		Vector3D BP = P - pol.ver2;

		Vector3D BC = pol.ver3 - pol.ver2;
		Vector3D CP = P - pol.ver3;
		Vector3D CA = pol.ver1- pol.ver3;
		Vector3D AP = P - pol.ver1;

		Vector3D c1 = Vector3D::Cross(AB, BP);
		Vector3D c2 = Vector3D::Cross(BC, CP);
		Vector3D c3 = Vector3D::Cross(CA, AP);


		//内積で順方向か逆方向か調べる
		double dot_12 = Vector3D::Dot(c1, c2);
		double dot_13 = Vector3D::Dot(c1, c3);

		if (dot_12 > 0 && dot_13 > 0) {
			//三角形の内側に点がある
			return true;
		}

		//三角形の外側に点がある
		return false;
	}

	static Vector3D PolygonPointLatestPoint(Polygon3D pol, Vector3D p) {

		Vector3D result(Collision::NearPosOnPlane(p, Collision::PolToPlane(pol).GetP(), Vector3D(pol.NormalVector()).Normalize()));

		if (!IsHitPointPolygon(pol, result)){
			Segment3D s[3] = { Segment3D(pol.ver1, pol.ver2),Segment3D(pol.ver2, pol.ver3),Segment3D(pol.ver3, pol.ver1) };

			double dis = 99999999999;

			for (int a = 0; a < 3; a++) {
				double old_dis = dis;
				double t = 0;
				dis = SegPointDist(p, s[a],t);
				if (old_dis > dis) {
					result = SegPointLatestPoint(p,s[a]);
				}
				else {
					dis = old_dis;
				}
			}
		}

		return result;

	}

	static SEGMENT_TRIANGLE_RESULT SegmentPolygonAnalyze(Polygon3D pol, Segment3D s) {
		VECTOR ss = DxConverter::VecToDx(s.start_point);
		VECTOR se = DxConverter::VecToDx(s.end_point);
		VECTOR pol1 = DxConverter::VecToDx(pol.ver1);
		VECTOR pol2 = DxConverter::VecToDx(pol.ver2);
		VECTOR pol3 = DxConverter::VecToDx(pol.ver3);
		SEGMENT_TRIANGLE_RESULT result;

		Segment_Triangle_Analyse(&ss, &se, &pol1, &pol2, &pol3, &result);

		return result;
	}


};
