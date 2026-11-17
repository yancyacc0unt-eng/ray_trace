#include "main.h"
/*
 * This file implements arithmetic and geometric operations for 2D and 3D vectors.
*/

namespace LinearAlgebra {
	// vector2D arithmetic operators
	vector2D vector2D::operator+(const vector2D& v) const {
		return {
			x + v.x,
			y + v.y
		};
	}
	vector2D vector2D::operator-(const vector2D& v) const {
		return {
			x - v.x,
			y - v.y
		};
	}
	vector2D vector2D::operator-() const {
		return {
			-x,
			-y
		};
	}
	vector2D vector2D::operator*(float s) const {
		return {
			x * s,
			y * s
		};
	}
	vector2D vector2D::operator/(float s) const {
		return {
			x / s,
			y / s
		};
	}

	vector2D& vector2D::operator+=(const vector2D& v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	vector2D& vector2D::operator-=(const vector2D& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}
	vector2D& vector2D::operator*=(float s) {
		x *= s;
		y *= s;
		return *this;
	}
	vector2D& vector2D::operator/=(float s) {
		x /= s;
		y /= s;
		return *this;
	}

	float vector2D::length() const {
		return std::sqrt(x * x + y * y);
	}
	
	// vector3D arithmetic operators
	vector3D vector3D::operator+(const vector3D& v) const {
		return {
			x + v.x,
			y + v.y,
			z + v.z
		};
	}
	vector3D vector3D::operator-(const vector3D& v) const {
		return {
			x - v.x,
			y - v.y,
			z - v.z
		};
	}
	vector3D vector3D::operator-() const {
		return {
			-x,
			-y,
			-z
		};
	}
	vector3D vector3D::operator*(float s) const {
		return {
			x * s,
			y * s,
			z * s
		};
	}
	vector3D vector3D::operator/(float s) const {
		return {
			x / s,
			y / s,
			z / s
		};
	}

	vector3D& vector3D::operator+=(const vector3D& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	vector3D& vector3D::operator-=(const vector3D& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	vector3D& vector3D::operator*=(float s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	vector3D& vector3D::operator/=(float s) {
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}

	float vector3D::length() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	// Scalar multiplication overloads and vector dot and cross products.
	vector2D operator*(float s, const vector2D& v) {
		return v * s;
	}
	vector3D operator*(float s, const vector3D& v) {
		return v * s;
	}

	float dot(const vector2D& v1, const vector2D& v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
	float dot(const vector3D& v1, const vector3D& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	float cross(const vector2D& v1, const vector2D& v2) {
		return v1.x * v2.y - v1.y * v2.x;
	}
	vector3D cross(const vector3D& v1, const vector3D& v2) {
		return {
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x
		};
	}
}
