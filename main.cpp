#include "main.h"

float area_of_triangle(const Point2D& A, const Point2D& B, const Point2D& C) {
	// Calculate the area of the triangle using the shoelace formula
	return 0.5f * std::abs(A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
}

int main(int argc, char* argv[]) {
	SetConsoleOutputCP(CP_UTF8);
	//-----------------------------------
	constexpr short width = 128;
	constexpr short height = 72;
	Screen screen(width, height);
	std::vector<Pixel> pixels;

	pixels.reserve(static_cast<size_t>(width) * height);
	for (short y = 0; y < height; y++) {
		for (short x = 0; x < width; x++) {
			Point2D position{ static_cast<float>(x), static_cast<float>(y) };
			Pixel::Color color{
				static_cast<char>(x * 255 / (width - 1)),
				static_cast<char>(y * 255 / (height - 1)),
				static_cast<char>((x + y) * 255 / (width + height - 2))
			};
			pixels.emplace_back(position, color);
		}
	}
	screen.setScreen(pixels);
	screen.show();
	/*---------------test---------------*/
	return 0;
}
