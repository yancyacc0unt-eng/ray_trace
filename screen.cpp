#include "main.h"
#include <charconv>
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
	LinearAlgebra::Point2D position{};
	Pixel::Color color{};
	pixels.reserve(static_cast<size_t>(w) * h);
	const size_t rowCount = static_cast<size_t>((h + 1) / 2);
	frameBuffer.reserve(3 + rowCount * (static_cast<size_t>(w) * 43 + 9));
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
	frameBuffer.clear();
	// Move the cursor to the home position before drawing the next frame.
	frameBuffer.append("\033[H");
	auto appendComponent = [this](unsigned char value) {
		char digits[3];
		const auto result = std::to_chars(digits, digits + sizeof(digits), static_cast<unsigned int>(value));
		frameBuffer.append(digits, static_cast<size_t>(result.ptr - digits));
	};
	// Append an ANSI true-color sequence using the supplied foreground/background prefix.
	auto appendColor = [this, &appendComponent](const Pixel::Color& color, const char* prefix) {
		frameBuffer.append(prefix);
		appendComponent(static_cast<unsigned char>(color.red));
		frameBuffer.push_back(';');
		appendComponent(static_cast<unsigned char>(color.green));
		frameBuffer.push_back(';');
		appendComponent(static_cast<unsigned char>(color.blue));
		frameBuffer.push_back('m');
	};
	for (int y = 0; y < height; y += 2) {
		frameBuffer.append("\033[2K");
		for (int x = 0; x < width; x++) {
			const Pixel& upper = pixels[y * width + x];
			// The lower-half block uses its background for the upper pixel and foreground for the lower one.
			const Pixel& lower = y + 1 < height ? pixels[(y + 1) * width + x] : upper;
			appendColor(upper.color, "\033[48;2;");
			appendColor(lower.color, "\033[38;2;");
			frameBuffer.append("\xe2\x96\x84");
		}
		frameBuffer.append("\033[0m\n");
	}
	// Write the completed frame in one batch, then flush it to the terminal.
	std::cout.write(frameBuffer.data(), static_cast<std::streamsize>(frameBuffer.size()));
	std::cout.flush();
}
