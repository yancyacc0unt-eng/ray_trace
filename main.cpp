#include "main.h"

float area_of_triangle(const Point2D& A, const Point2D& B, const Point2D& C) {
	// Calculate the area of the triangle using the shoelace formula
	return 0.5f * std::abs(A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
}

int main(int argc, char* argv[]) {
	SetConsoleOutputCP(CP_UTF8);

	Screen screen(128, 72);
	/*----test----
	Point2D A(1.0, 2.0);
	Point2D B(-3.0, -4.0);
	Point2D C(5.0, -6.0);

	std::vector<Pixel> pixels((int)area_of_triangle(A, B, C));

	__m256 X = { 4.0, 1.0, 144.0, 2.2276676, 256.0, 16.0, 9.0, 2.0 };
	__m256 Y = _mm256_rsqrt_ps(X);
	*/
	std::cout << "128px\n72px";
	return 0;
}
