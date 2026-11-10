#include "main.h"
/*
* This file contains the implementation of triangle-related functionality.
*/
Triangle::Triangle(LinearAlgebra::Point2D& a, LinearAlgebra::Point2D& b, LinearAlgebra::Point2D& c) {
	A = a;
	B = b;
	C = c;
}
float Triangle::area() {
	// Calculate the area of the triangle using the shoelace formula
	return 0.5f * std::abs(A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
}
