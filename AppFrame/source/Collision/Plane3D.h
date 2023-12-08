#pragma once
#include"Vector3D.h"

class Plane3D {
public:
	Plane3D(){}
	Plane3D(double a, double b, double c, double d){
		this->a;
		this->b;
		this->c;
		this->d;
	}

	Plane3D(Vector3D p,Vector3D normal) {
		a = normal.x;
		b = normal.y;
		c = normal.z;
		d = p.Dot(normal);
	}
	double a, b, c, d;
	Vector3D GetP() {
		return Vector3D(a * d, b * d, c * d);
	}
};