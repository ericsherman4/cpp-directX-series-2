#pragma once

#include "Colors.h"
#include <string>
#include "Rect.h"
#include <memory>

class Surface
{
public:
    Surface(const std::string& filename);
    Surface(int width_in, int height_in);
    Surface(const Surface& rhs);
    Surface(Surface&& donor) = default;
    ~Surface() = default;
    Surface& operator=(Surface&& donor) = default;
    Surface& operator=(const Surface& rhs);
    void PutPixel(int x, int y, Color c);
    Color GetPixel(int x, int y) const;
    int GetWidth() const;
    int GetHeight() const;
    RectI GetRect() const;
private:
    int width;
    int height;
    std::unique_ptr<Color[]> pPixels;
};
