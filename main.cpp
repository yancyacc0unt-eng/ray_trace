#include "main.h"
/*
 * This file contains the program entry point.
*/

int main(int argc, char* argv[]) {
	SetConsoleOutputCP(CP_UTF8);

	constexpr short width = 1024;
	constexpr short height = 576;

	Screen screen(width, height);
	std::vector<Pixel> frame;
	// --------test--------
	auto pixels = getFrame();
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {

			auto [r, g, b] = pixels[i * width + j];
			LinearAlgebra::vector2D pos{ j,i };
			Pixel::Color col{ r,g,b };

			Pixel p(pos, col);
			frame.push_back(p);
		}
	}

	screen.setScreen(frame);
	screen.show();
	// --------test--------
	return 0;
}
