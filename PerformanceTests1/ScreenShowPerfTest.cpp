#include "pch.h"
#include "CppUnitTest.h"
#include "../main.h"
#include <sstream>
#include <vector>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ray_trace_performance
{
	TEST_CLASS(ScreenShowPerfTest)
	{
	public:
		TEST_METHOD(ShowBaseline)
		{
			constexpr short width = 128;
			constexpr short height = 72;
			Screen screen(width, height);
			std::vector<Pixel> pixels;
			pixels.reserve(static_cast<size_t>(width) * height);
			for (short y = 0; y < height; ++y)
			{
				for (short x = 0; x < width; ++x)
				{
					Point2D position{ static_cast<float>(x), static_cast<float>(y) };
					Pixel::Color color{ static_cast<char>(x), static_cast<char>(y), static_cast<char>(x + y) };
					pixels.emplace_back(position, color);
				}
			}
			screen.setScreen(pixels);
			std::ostringstream capturedOutput;
			std::streambuf* previousBuffer = std::cout.rdbuf(capturedOutput.rdbuf());
			screen.show();
			std::cout.rdbuf(previousBuffer);
		}
	};
}
