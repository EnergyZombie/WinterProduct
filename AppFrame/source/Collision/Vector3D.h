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

	//値の代入
	const Vector3D& operator = (const Vector3D& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	//ベクトルの加算代入
	const Vector3D& operator += (const Vector3D& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	//ベクトルの減算代入
	const Vector3D& operator -= (const Vector3D& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	//スケーリングして、代入
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
	//ベクトルの加算
	const Vector3D operator + (const Vector3D& other);


	//ベクトルの減算
	const Vector3D operator - (const Vector3D& other);

	//スケーリング
	const Vector3D operator * (const double& scale);

	//内積
	static const double Dot(const Vector3D& v1, const Vector3D& v2);

	const double Dot(const Vector3D& v);
	//外積

	static const Vector3D Cross(const Vector3D& v1, const Vector3D& v2);
	const Vector3D Cross(const Vector3D& other);

	//ベクトルの長さ
	const double Length();

	static double Length(Vector3D v1, Vector3D v2);
	//ベクトルの長さの二乗
	const double LengthSquare();

	//正規化
	const Vector3D Normalize();
	void Normalized();

};
