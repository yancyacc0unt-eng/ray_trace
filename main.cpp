#include "main.h"
/*
 * This file contains the program entry point.
*/

bool intersect(const Ray& line, const Sphere& ball, float& result) {
	// calculate abc
	auto a = LA::dot(line.getDirection(), line.getDirection());
	auto b = LA::dot((2 * line.getDirection()), (line.getOrigin() - ball.getCenter()));
	auto c = (line.getOrigin() - ball.getCenter()).length();c = c * c - ball.getRadius() * ball.getRadius();
	// get the root
	float t1 = (-b + std::sqrt(b * b - 4.0f * a * c)) / (2.0f * a);
	float t2 = (-b - std::sqrt(b * b - 4.0f * a * c)) / (2.0f * a);
	// get the neerest meeting point
	if (t1 >= 0 && t2 >= 0) {
		result = min(t1, t2);
		return true;
	}
	else if (t1 >= 0) {
		result = t1;
		return true;
	}
	else if (t2 >= 0) {
		result = t2;
		return true;
	}
	else {
		result = INFINITE;
		return false;
	}
}

int main(int argc, char* argv[]) {
	SetConsoleOutputCP(CP_UTF8);

	constexpr short width = 256;
	constexpr short height = 144;

	Screen screen(width, height);
	std::vector<Pixel> frame;
	// --------test--------
	float x, y, z, r;
	std::cout << "ball    x:    y:    z:    r:\n";
	std::cin >> x >> y >> z >> r;
	LA::vector3D p(x, y, z);
	Sphere ball(p, r);

	std::cout << "ray     x:    y:    z:    \nfacing  x:    y:    z:    \n";
	std::cin >> x >> y >> z;
	LA::vector3D o(x, y, z);
	std::cin >> x >> y >> z;
	LA::vector3D d(x, y, z);
	Ray line(o, d);

	float result = 0;
	bool meet = intersect(line, ball, result);
	if (meet) {
		std::cout << "meeting point:\nx:    y:    z:\n";
		std::cout << line.at(result).x << "  ";
		std::cout << line.at(result).y << "  ";
		std::cout << line.at(result).z << "  ";
	}
	else {
		std::cout << "dose not meet !";
	}
	// --------test--------
	return 0;
}
// -------- class implemention --------
//----
Sphere::Sphere(LA::vector3D& c, float r) : center(c), radius(r) {
}
LA::vector3D Sphere::getCenter() const { return center; }
float Sphere::getRadius() const { return radius; }
//----
Ray::Ray(LA::vector3D& o, LA::vector3D& d) : origin(o), direction(d) {
}
LA::vector3D Ray::at(float time) {
	return origin + time * direction;
}
LA::vector3D Ray::getOrigin() const { return origin; }
LA::vector3D Ray::getDirection() const { return direction; }
