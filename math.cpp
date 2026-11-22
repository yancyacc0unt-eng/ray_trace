#include "main.h"
/*
* This file implements arithmetic and geometric operations for 2D and 3D vectors.
* 
* Addition and subtraction operate component by component and return a new vector.
* Unary negation reverses the direction of a vector without changing its length.
* Multiplication and division by a scalar scale each component of the vector.
* Compound arithmetic operators update the vector itself and return it for chaining.
* 
* The length functions calculate each vector's Euclidean distance from the origin.
* Scalar multiplication is supported with the scalar on either side of the vector.
* The dot product combines corresponding components and returns a scalar value.
* Dot products can be used to compare the alignment of two vectors.
* 
* The 2D cross product returns a signed scalar indicating orientation and area.
* The 3D cross product returns a vector perpendicular to both input vectors.
* Its direction follows the right-hand rule, and its magnitude is the spanned area.
*/

namespace LinearAlgebra {
	// These operators return new vectors, leaving the original operands unchanged.
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

	// Compound operators update this vector in place and return it for chaining.
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

	// The 2D vector length is its Euclidean distance from the origin.
	float vector2D::length() const {
		return std::sqrt(x * x + y * y);
	}
	
	// 3D arithmetic follows the same component-wise behavior as the 2D operators.
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

	// Compound operators update this vector in place and return it for chaining.
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

	// The 3D vector length is its Euclidean distance from the origin.
	float vector3D::length() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	// Scalar-left overloads allow multiplication in either operand order.
	vector2D operator*(float s, const vector2D& v) {
		return v * s;
	}
	vector3D operator*(float s, const vector3D& v) {
		return v * s;
	}

	// Dot products measure alignment and return a scalar.
	float dot(const vector2D& v1, const vector2D& v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
	float dot(const vector3D& v1, const vector3D& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	// The 2D cross product returns the signed magnitude of the perpendicular component.
	float cross(const vector2D& v1, const vector2D& v2) {
		return v1.x * v2.y - v1.y * v2.x;
	}
	// The 3D cross product returns a vector perpendicular to both input vectors.
	vector3D cross(const vector3D& v1, const vector3D& v2) {
		return {
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x
		};
	}
}
