#pragma once

#include "Colors.h"

class Surface
{
public:
    Surface(int width_in, int height_in);
    Surface(const Surface& rhs);
    ~Surface();
    Surface& operator=(const Surface& rhs);
    void PutPixel(int x, int y, Color c);
    Color GetPixel(int x, int y) const;
    int GetWidth() const;
    int GetHeight() const;
private:
    int width;
    int height;
    Color* pPixels = nullptr;
};
