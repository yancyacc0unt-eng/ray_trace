#ifndef MAIN_H
#define MAIN_H

/*
 * This file declares the linear algebra, pixel, screen, and triangle interfaces.
 */

#include <iostream>
#include <vector>
#include <format>
#include <string>
#include <immintrin.h>
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

// Stores a pixel's color and two-dimensional position.
class Pixel { // pixel.cpp
public:
	// Holds the pixel's red, green, and blue color components.
	struct Color{
		char red;
		char green;
		char blue;
	} color{};
	// Holds the pixel's horizontal and vertical coordinates.
	struct Pos {
		short x;
		short y;
	} position{};
public:
	// Create a pixel with default-initialized data or with the supplied position and color.
	Pixel() = default;
	Pixel(LinearAlgebra::vector2D&, Color&);
	~Pixel() = default;
};

// Manages a pixel buffer and renders it to the console.
class Screen { // screen.cpp
private:
	// Screen dimensions and the pixels to display.
	short width;
	short height;
	std::vector<Pixel>pixels;
	std::string frameBuffer;
public:
	// Create a screen with the specified width and height.
	Screen(short, short);
	void setScreen(std::vector<Pixel>&); // Replace the screen's pixel buffer.
	void setPixle(Pixel&); // Update one pixel in the screen buffer.
	void show(); // Render the screen to standard output.
	~Screen() = default;
};

// Represents a triangle using three two-dimensional vertices.
class Triangle { // triangle.cpp
private:
	LinearAlgebra::vector2D A;
	LinearAlgebra::vector2D B;
	LinearAlgebra::vector2D C;
public:
	// Create a triangle from its three vertices.
	Triangle(LinearAlgebra::vector2D&, LinearAlgebra::vector2D&, LinearAlgebra::vector2D&);
	// Return the triangle's area and centroid, respectively.
	float area();
	LinearAlgebra::vector2D center();
	~Triangle() = default;
};

#endif // !MAIN_H