#include "main.h"
#include <random>
#include <string>

int main(int argc, char* argv[]) {
	SetConsoleOutputCP(CP_UTF8);
	/*random pixel test.
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD originalMode;
	if (output == INVALID_HANDLE_VALUE || !GetConsoleMode(output, &originalMode)) {
		return 1;
	}
	if (!SetConsoleMode(output, originalMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING)) {
		return 1;
	}

	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	if (!GetConsoleScreenBufferInfo(output, &screenInfo)) {
		SetConsoleMode(output, originalMode);
		return 1;
	}

	const int width = screenInfo.srWindow.Right - screenInfo.srWindow.Left + 1;
	const int height = screenInfo.srWindow.Bottom - screenInfo.srWindow.Top + 1;
	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	std::uniform_int_distribution<int> color(0, 255);

	std::string screen = "\033[2J\033[H\033[?7l";
	for (int row = 0; row < height; ++row) {
		if (row > 0) {
			screen += "\033[" + std::to_string(row + 1) + ";1H";
		}
		for (int column = 0; column < width; ++column) {
			const int foregroundRed = color(generator);
			const int foregroundGreen = color(generator);
			const int foregroundBlue = color(generator);
			const int backgroundRed = color(generator);
			const int backgroundGreen = color(generator);
			const int backgroundBlue = color(generator);

			screen += "\033[38;2;" + std::to_string(foregroundRed) + ";" +
				std::to_string(foregroundGreen) + ";" + std::to_string(foregroundBlue) +
				";48;2;" + std::to_string(backgroundRed) + ";" +
				std::to_string(backgroundGreen) + ";" + std::to_string(backgroundBlue) +
				"m\xe2\x96\x84";
		}
	}
	screen += "\033[0m\033[?7h";
	std::cout << screen << std::flush;
	SetConsoleMode(output, originalMode);
	//*/
	return 0;
}
