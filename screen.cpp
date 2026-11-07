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
	pixels.resize(w * h);
}
void Screen::setScreen(std::vector<Pixel>& pxs) {
	if (pxs.size() < pixels.size()) {
		std::cerr << "ERROR : pixels not enough\n";
	}
	else if (pxs.size() > pixels.size()) {
		std::cerr << "ERROR : pixels overflow\n";
	}
	std::clog << "ignored ERROR";
	pixels = pxs;
}
void Screen::setPixle(Pixel& p, short x, short y) {
	pixels[x + width * y] = p;
}
void Screen::show() {
	static std::string temp = "\033[{},{}H\033[48,2,{},{},{}m\033[38,2,{},{},{}m\xe2\x96\x84\033[0m";
	for (int i = 0; i < width * height; i++) {
		// print every pixel.
	}
}
