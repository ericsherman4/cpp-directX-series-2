#include "Surface.h"
#include "assert.h"

Surface::Surface(int width_in, int height_in)
    : width(width_in)
    , height(height_in)
    , pPixels(new Color[width* height])
{
}

// thinking i misunderstand copy constructor.
// passing in another object to create a new object.
Surface::Surface(const Surface& rhs)
    : Surface(rhs.width, rhs.height)
{
    for (int i{ 0 }; i < width*height; ++i)
    {
        pPixels[i] = rhs.pPixels[i];
    }
}

Surface::~Surface()
{
    delete[] pPixels;
    pPixels = nullptr;
}

Surface& Surface::operator=(const Surface& rhs)
{
    width = rhs.width;
    height = rhs.height;

    // calling delete on nullptr does no action, delete performs the check

    delete[] pPixels;
    pPixels = new Color[width * height];

    for (int i{ 0 }; i < width * height; ++i)
    {
        pPixels[i] = rhs.pPixels[i];
    }

    return *this;
}

void Surface::PutPixel(int x, int y, Color c)
{
    assert(x >= 0);
    assert(x < width);
    assert(y >= 0);
    assert(y < height);
    pPixels[y * width + x] = c;
}

Color Surface::GetPixel(int x, int y) const
{
    assert(x >= 0);
    assert(x < width);
    assert(y >= 0);
    assert(y < height);
    return pPixels[y * width + x];
}

int Surface::GetWidth() const
{
    return width;
}

int Surface::GetHeight() const
{
    return height;
}
