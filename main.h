#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
#include <format>
#include <string>
#include <immintrin.h>
#include <Windows.h>

namespace LinearAlgebra { //math.cpp
	struct vector2D {
		float x;
		float y;

		vector2D operator+(const vector2D& v) const;
		vector2D operator-(const vector2D& v) const;
		vector2D operator-() const;
		vector2D operator*(float s) const;
		vector2D operator/(float s) const;

		vector2D& operator+=(const vector2D& v);
		vector2D& operator-=(const vector2D& v);
		vector2D& operator*=(float s);
		vector2D& operator/=(float s);
	};
	struct vector3D {
		float x;
		float y;
		float z;

		vector3D operator+(const vector3D& v) const;
		vector3D operator-(const vector3D& v) const;
		vector3D operator-() const;
		vector3D operator*(float s) const;
		vector3D operator/(float s) const;

		vector3D& operator+=(const vector3D& v);
		vector3D& operator-=(const vector3D& v);
		vector3D& operator*=(float s);
		vector3D& operator/=(float s);
	};

	vector2D operator*(float s, const vector2D& v);
	vector3D operator*(float s, const vector3D& v);

	float dot(const vector2D& v1, const vector2D& v2);
	float dot(const vector3D& v1, const vector3D& v2);

	float cross(const vector2D& v1, const vector2D& v2);
	vector3D cross(const vector3D& v1, const vector3D& v2);
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
	Pixel(LinearAlgebra::vector2D&, Color&);
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
	LinearAlgebra::vector2D A;
	LinearAlgebra::vector2D B;
	LinearAlgebra::vector2D C;
public:
	Triangle(LinearAlgebra::vector2D&, LinearAlgebra::vector2D&, LinearAlgebra::vector2D&);
	float area();
	LinearAlgebra::vector2D center();
	~Triangle() = default;
};

#endif // !MAIN_H