#pragma once
#include"Vector3D.h"

	class Polygon3D {
	public:
		Polygon3D(Vector3D v1, Vector3D v2, Vector3D v3) {
			ver1 = v1;
			ver2 = v2;
			ver3 = v3;
		}


		const Vector3D& NormalVector() {
			return Vector3D(Vector3D::Cross((ver2 - ver1), (ver3 - ver1)))/*.Normalize()*/;
		}

		//protected:
		Vector3D ver1;
		Vector3D ver2;
		Vector3D ver3;
	};
