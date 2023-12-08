#pragma once
#include"Segment.h"

class Capsule3D {
public:
	Capsule3D() {
		seg = Segment3D(Vector3D(0,0,0), Vector3D(0, 0, 0));
		radius = 0;
	}
	Capsule3D(Segment3D seg, double rad) {
		this->seg = seg;
		radius = rad;
	}
	Capsule3D(Vector3D s,Vector3D e, double rad) {
		seg = Segment3D(s,e);
		radius = rad;
	}
	Segment3D seg;
	double radius;
};
