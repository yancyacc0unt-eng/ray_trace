#include "main.h"
/*
 * This file contains the program entry point.
*/

#include <tuple>
__declspec(dllimport) std::vector<std::tuple<uint8_t, uint8_t, uint8_t, short, short>> getFrame();

int main(int argc, char* argv[]) {
	SetConsoleOutputCP(CP_UTF8);

	constexpr short width = 256;
	constexpr short height = 144;
	Screen screen(width, height);
	std::vector<Pixel> frame;
	// --------test--------
	auto pixels = getFrame();
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			auto [r, g, b, x, y] = pixels[i * width + j];
			LinearAlgebra::Point2D pos{ x,y };
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
