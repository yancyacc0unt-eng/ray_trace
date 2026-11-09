#include "main.h"
/*
* This class can display the results to stdout, It is the screen of the porgram.
* "\xe2\x96\x84" is the unicode character for a half-solid block,
* which it's foreground can be used as a pixel in odd rows,
* and it's background can be used as a pixel in even rows.
* 
* Setting foreground RGB, use \033[38;2;R;G;Bm.
* Setting background RGB, use \033[48;2;R;G;Bm.
* Reset colors, use \033[0m.
*/
Screen::Screen(short w, short h) : width(w), height(h) {
	Point2D position{};
	Pixel::Color color{};
	pixels.reserve(static_cast<size_t>(w) * h);
	for (int i = 0; i < w * h; i++) {
		pixels.emplace_back(position, color);
	}
}
void Screen::setScreen(std::vector<Pixel>& pxs) {
	if (pxs.size() < pixels.size()) {
		std::cerr << "ERROR : pixels not enough\n";
		return;
	}
	if (pxs.size() > pixels.size()) {
		std::cerr << "ERROR : pixels overflow\n";
		return;
	}
	pixels = pxs;
}
void Screen::setPixle(Pixel& p) {
	const int x = width / 2 + p.position.x;
	const int y = height / 2 - p.position.y;
	if (x < 0 || x >= width || y < 0 || y >= height) {
		return;
	}
	pixels[y * width + x] = p;
}
void Screen::show() {
	std::cout << "\033[H";
	for (int y = 0; y < height; y += 2) {
		std::cout << "\033[2K";
		for (int x = 0; x < width; x++) {
			const Pixel& upper = pixels[y * width + x];
			const Pixel& lower = y + 1 < height ? pixels[(y + 1) * width + x] : upper;
			std::cout << std::format(
				"\033[48;2;{};{};{}m\033[38;2;{};{};{}m\xe2\x96\x84",
				static_cast<unsigned char>(upper.color.red),
				static_cast<unsigned char>(upper.color.green),
				static_cast<unsigned char>(upper.color.blue),
				static_cast<unsigned char>(lower.color.red),
				static_cast<unsigned char>(lower.color.green),
				static_cast<unsigned char>(lower.color.blue));
		}
		std::cout << "\033[0m\n";
	}
	std::cout.flush();
}
