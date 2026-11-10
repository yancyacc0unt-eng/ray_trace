#include "main.h"
/*
* This file contains the program entry point and triangle area calculation.
*/

float area_of_triangle(const Point2D& A, const Point2D& B, const Point2D& C) {
	// Calculate the area of the triangle using the shoelace formula
	return 0.5f * std::abs(A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
}

int main(int argc, char* argv[]) {
	SetConsoleOutputCP(CP_UTF8);

	constexpr short width = 128;
	constexpr short height = 72;
	Screen screen(width, height);
	std::vector<Pixel> frame(width * height);
	// --------test--------
	// --------test--------
	return 0;
}
