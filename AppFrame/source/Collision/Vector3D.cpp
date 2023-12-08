#include"Vector3D.h"

const Vector3D Vector3D::operator + (const Vector3D& other) {
	return Vector3D(*this) += other;
}

const Vector3D Vector3D::operator - (const Vector3D& other) {
	return Vector3D(*this) -= other;
}

const Vector3D Vector3D::operator * (const double& scale) {
	return Vector3D(*this) *= scale;
}

//ì‡êœ
const double Vector3D::Dot(const Vector3D& v1, const Vector3D& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

const double Vector3D::Dot(const Vector3D& v) {
	return Dot(*this, v);
}



const double Vector3D::Length() {
	return sqrt(Dot(*this, *this));
}



double Vector3D::Length(Vector3D v1, Vector3D v2) {
	return Vector3D(v1 - v2).Length();
}

const double Vector3D::LengthSquare() {
	return Dot(*this, *this);
}

const Vector3D Vector3D::Normalize(){
	return *this * (1 / Length());
}

void Vector3D::Normalized() {
	*this *= (1 / Length());
}

const Vector3D Vector3D::Cross(const Vector3D& v1, const Vector3D& v2) {
	Vector3D result;
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return result;
}

const Vector3D Vector3D::Cross(const Vector3D& other) {
	return Cross(*this, other);
}