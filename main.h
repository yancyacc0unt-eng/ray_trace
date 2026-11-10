#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
#include <format>
#include <string>
#include <immintrin.h>
#include <Windows.h>

namespace LinearAlgebra {
	struct Point2D {
		float x;
		float y;
	};
	struct Point3D {
		float x;
		float y;
		float z;
	};
}

class Pixel { // pixel.cpp
public:
	struct Color{
		char red;
		char green;
		char blue;
	} color{};
	struct Pos {
		short x;
		short y;
	} position{};
public:
	Pixel() = default;
	Pixel(LinearAlgebra::Point2D&, Color&);
	~Pixel() = default;
};

class Screen { // screen.cpp
private:
	short width;
	short height;
	std::vector<Pixel>pixels;
	std::string frameBuffer;
public:
	Screen(short, short);
	void setScreen(std::vector<Pixel>&); // flush the whole screen
	void setPixle(Pixel&); // change one pixel
	void show(); // print to stdout
	~Screen() = default;
};

class Triangle { // triangle.cpp
private:
	LinearAlgebra::Point2D A;
	LinearAlgebra::Point2D B;
	LinearAlgebra::Point2D C;
public:
	Triangle(LinearAlgebra::Point2D&, LinearAlgebra::Point2D&, LinearAlgebra::Point2D&);
	float area();
	LinearAlgebra::Point2D center();
	~Triangle() = default;
};

#endif // !MAIN_H