#pragma once
#include"Vector3D.h"

class Segment3D {
public:
	Segment3D() {
		start_point = Vector3D(0, 0, 0);
		end_point = Vector3D(0, 0, 0);
	}
	Segment3D(Vector3D s , Vector3D e){
		start_point = s;
		end_point = e;
	}

	Vector3D start_point;
	Vector3D end_point;

	double Length() {
		return Vector3D(end_point - start_point).Length();
	}

	Vector3D Vector() {
		return end_point - start_point;
	}
};