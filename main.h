#ifndef MAIN_H
#define MAIN_H

#include <Windows.h>
#include <iostream>
#include <format>

class Point2D { // pooint.cpp
private:
	double x;
	double y;
public:
	Point2D(double x, double y) : x(x), y(y) {}
	~Point2D() {}
};
class Point3D {
private:
	double x;
	double y;
	double z;
public:
	Point3D(double x, double y, double z) : x(x), y(y), z(z) {}
	~Point3D() {}
};

class Pixel { // screen.cpp
private:
	short x;
	short y;
	struct {
		char r;
		char g;
		char b;
	} color;
public:
	Pixel(short x, short y) : x(x), y(y) {}
	~Pixel() {}
};
class Screen {
private:
	short width;
	short height;
public:
	Screen(short w, short h) : width(w), height(h) {}
	~Screen();
};

#endif // !MAIN_H