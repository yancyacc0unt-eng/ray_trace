/*
 * This project is an in-progress exploration of building a ray-tracing
 * application. It currently provides foundational vector math, pixel and
 * screen abstractions, and basic triangle geometry; rendering and other
 * features are still under development.
 */
#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
#include <format>
#include <string>
#include <tuple>
#include <charconv>
#include <Windows.h>

// Provides vector types and common vector operations.
namespace LinearAlgebra { //math.cpp
	// Represents a vector in two-dimensional space.
	struct vector2D {
		float x;
		float y;

		// Return the result of the corresponding vector or scalar operation.
		vector2D operator+(const vector2D& v) const;
		vector2D operator-(const vector2D& v) const;
		vector2D operator-() const;
		vector2D operator*(float s) const;
		vector2D operator/(float s) const;

		// Apply the corresponding operation to this vector and return it.
		vector2D& operator+=(const vector2D& v);
		vector2D& operator-=(const vector2D& v);
		vector2D& operator*=(float s);
		vector2D& operator/=(float s);
	};
	// Represents a vector in three-dimensional space.
	struct vector3D {
		float x;
		float y;
		float z;

		// Return the result of the corresponding vector or scalar operation.
		vector3D operator+(const vector3D& v) const;
		vector3D operator-(const vector3D& v) const;
		vector3D operator-() const;
		vector3D operator*(float s) const;
		vector3D operator/(float s) const;

		// Apply the corresponding operation to this vector and return it.
		vector3D& operator+=(const vector3D& v);
		vector3D& operator-=(const vector3D& v);
		vector3D& operator*=(float s);
		vector3D& operator/=(float s);
	};

	// Support scalar multiplication with the scalar on the left.
	vector2D operator*(float s, const vector2D& v);
	vector3D operator*(float s, const vector3D& v);

	// Return the dot product of two vectors.
	float dot(const vector2D& v1, const vector2D& v2);
	float dot(const vector3D& v1, const vector3D& v2);

	// Return the 2D scalar cross product or the 3D vector cross product.
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
	void setScreen(std::vector<Pixel>&); // Replace the screen's pixel buffer.
	void setPixle(Pixel&);               // Update one pixel in the screen buffer.
	void show();                         // Render the screen to standard output.
	~Screen() = default;
};

#endif // !MAIN_H