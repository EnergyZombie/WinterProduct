#include"Collision.h"

double Collision::PolToPointDist(Vector3D A, Vector3D P, Vector3D N) {
	//PAƒxƒNƒgƒ‹(A-P)
	Vector3D PA(A - P);
	return abs(PA.Dot(N.Normalize()));
}