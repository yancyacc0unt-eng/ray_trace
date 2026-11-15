#include "pch.h"
#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>
#include <tuple>

struct Pixel {
    uint8_t r, g, b;
};

struct Point {
    float x, y;
};

struct Triangle {
    Point a, b, c;
    uint8_t ra, ga, ba;
    uint8_t rb, gb, bb;
    uint8_t rc, gc, bc;
};

std::tuple<float, float, float> triangleBarycentricCoords(const Point& p, const Triangle& tri) {
    float denom = (tri.b.y - tri.a.y) * (tri.c.x - tri.a.x) +
        (tri.c.y - tri.a.y) * (tri.a.x - tri.b.x);
    if (std::abs(denom) < 1e-6f) return { -1,-1,-1 };

    float u = ((p.y - tri.c.y) * (tri.b.x - tri.a.x) +
        (p.x - tri.c.x) * (tri.c.y - tri.b.y)) / denom;
    float v = ((p.y - tri.a.y) * (tri.c.x - tri.a.x) +
        (p.x - tri.a.x) * (tri.a.y - tri.c.y)) / denom;
    float w = 1.0f - u - v;
    return { u,v,w };
}

__declspec(dllexport) std::vector<std::tuple<uint8_t, uint8_t, uint8_t, short, short>> getFrame() {
    srand(time(nullptr));

    const int width = 256;
    const int height = 144;

    std::vector<Pixel> pixels(width * height);
    for (auto& p : pixels) {
        p.r = p.g = p.b = 0;
    }
    Triangle tri{
        { 195.0f, 14.0f },
        { 57.0f, 45.0f },
        { 132.0f, 97.0f },
        255, 0, 255,
        0, 255, 255,
        255, 255, 0
    };

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Point p{ static_cast<float>(x), static_cast<float>(y) };

            auto [u, v, w] = triangleBarycentricCoords(p, tri);

            if (u >= -1e-4f && v >= -1e-4f && w >= -1e-4f) {

                float r = u * tri.ra + v * tri.rb + w * tri.rc;
                float g = u * tri.ga + v * tri.gb + w * tri.gc;
                float b = u * tri.ba + v * tri.bb + w * tri.bc;

                pixels[y * width + x] = { static_cast<uint8_t>(r),
                                         static_cast<uint8_t>(g),
                                         static_cast<uint8_t>(b) };
            }
        }
    }


    std::vector<std::tuple<uint8_t, uint8_t, uint8_t, short, short>> frameData{};
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            uint8_t r = pixels[y * width + x].r;
            uint8_t g = pixels[y * width + x].g;
            uint8_t b = pixels[y * width + x].b;
            std::tuple<uint8_t, uint8_t, uint8_t, short, short> p{r,g,b,x,y};
            frameData.push_back(p);
        }
    }

    return frameData;
}
