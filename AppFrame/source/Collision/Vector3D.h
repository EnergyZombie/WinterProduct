#pragma once

#include<cmath>

class Vector3D {
public:
	Vector3D() { x = 0.0f; y = 0.0f; z = 0.0f; }
	Vector3D(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector3D(const Vector3D& other) {
		*this = other;
	}
	virtual ~Vector3D() {}

	double x, y, z;

	//�l�̑��
	const Vector3D& operator = (const Vector3D& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	//�x�N�g���̉��Z���
	const Vector3D& operator += (const Vector3D& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	//�x�N�g���̌��Z���
	const Vector3D& operator -= (const Vector3D& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	//�X�P�[�����O���āA���
	const Vector3D& operator *= (const double& scale) {
		x *= scale;
		y *= scale;
		z *= scale;
		return *this;
	}
	bool operator != (const Vector3D& right) {
		if (abs(x - right.x) > 0.00000) { return true; }
		if (abs(y - right.y) > 0.00000) { return true; }
		if (abs(z - right.z) > 0.00000) { return true; }
		return false;
	}
	//�x�N�g���̉��Z
	const Vector3D operator + (const Vector3D& other);


	//�x�N�g���̌��Z
	const Vector3D operator - (const Vector3D& other);

	//�X�P�[�����O
	const Vector3D operator * (const double& scale);

	//����
	static const double Dot(const Vector3D& v1, const Vector3D& v2);

	const double Dot(const Vector3D& v);
	//�O��

	static const Vector3D Cross(const Vector3D& v1, const Vector3D& v2);
	const Vector3D Cross(const Vector3D& other);

	//�x�N�g���̒���
	const double Length();

	static double Length(Vector3D v1, Vector3D v2);
	//�x�N�g���̒����̓��
	const double LengthSquare();

	//���K��
	const Vector3D Normalize();
	void Normalized();

};
