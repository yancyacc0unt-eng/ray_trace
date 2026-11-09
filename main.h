#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
#include <format>
#include <string>
#include <immintrin.h>
#include <Windows.h>

struct Point2D {
	float x;
	float y;
};
struct Point3D {
	float x;
	float y;
	float z;
};

class Pixel { // pixel.cpp
public:
	struct Color{
		char red;
		char green;
		char blue;
	} color;
	struct Pos {
		short x;
		short y;
	} position;
public:
	Pixel(Point2D&, Color&);
	~Pixel() = default;
};

class Screen { // screen.cpp
private:
	short width;
	short height;
	std::vector<Pixel>pixels;
public:
	Screen(short, short);
	void setScreen(std::vector<Pixel>&); // flush the whole screen
	void setPixle(Pixel&); // change one pixel
	void show(); // print to stdout
	~Screen() = default;
};

#endif // !MAIN_H