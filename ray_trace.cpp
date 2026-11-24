#include "main.h"
#include <chrono>
/*
* This file contains the program entry point.
* And ... Somtimes with a little bit of tests.
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
	/* --------test--------
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
	// --------test--------*/
	constexpr float topX = 0.0f;
	constexpr float topY = 54.0f;
	constexpr float leftX = -52.0f;
	constexpr float leftY = -54.0f;
	constexpr float rightX = 52.0f;
	constexpr float rightY = -54.0f;
	constexpr float denominator = (leftY - rightY) * (topX - rightX) +
		(rightX - leftX) * (topY - rightY);

	for (int y = 0; y < height; ++y) {
		const float pointY = static_cast<float>(height / 2 - y);
		for (int x = 0; x < width; ++x) {
			const float pointX = static_cast<float>(x - width / 2);
			const float redWeight = ((leftY - rightY) * (pointX - rightX) +
				(rightX - leftX) * (pointY - rightY)) / denominator;
			const float greenWeight = ((rightY - topY) * (pointX - rightX) +
				(topX - rightX) * (pointY - rightY)) / denominator;
			const float blueWeight = 1.0f - redWeight - greenWeight;
			if (redWeight < 0.0f || greenWeight < 0.0f || blueWeight < 0.0f) {
				continue;
			}

			LA::vector2D position{ static_cast<float>(pointX), pointY };
			Pixel::Color color{
				static_cast<char>(static_cast<unsigned char>(255.0f * redWeight)),
				static_cast<char>(static_cast<unsigned char>(255.0f * greenWeight)),
				static_cast<char>(static_cast<unsigned char>(255.0f * blueWeight))
			};
			Pixel pixel(position, color);
			screen.setPixle(pixel);
		}
	}

	const auto outputStart = std::chrono::steady_clock::now();
	for (int frame = 0; frame < 10; ++frame) {
		screen.show();
	}
	const auto outputElapsed = std::chrono::steady_clock::now() - outputStart;
	std::cerr << "10 terminal frames: "
		<< std::chrono::duration<double>(outputElapsed).count() << " s\n";
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
