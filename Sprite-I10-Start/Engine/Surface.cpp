#include "Surface.h"
#include "assert.h"
#include "ChiliWin.h"
#include <fstream>

Surface::Surface(const std::string& filename)
{

    std::ifstream bmp_file(filename, std::ios::binary); //open file in binary mode so that it doesnt do any newline conversions.
    assert(bmp_file);

    BITMAPFILEHEADER bmFileheader;
    bmp_file.read(reinterpret_cast<char*>(&bmFileheader), sizeof(bmFileheader));

    BITMAPINFOHEADER bmHeaderInfo;
    bmp_file.read(reinterpret_cast<char*>(&bmHeaderInfo), sizeof(bmHeaderInfo));

    assert(bmHeaderInfo.biBitCount == 24 || bmHeaderInfo.biBitCount == 32);
    assert(bmHeaderInfo.biCompression == BI_RGB);

    width = bmHeaderInfo.biWidth;
    height = bmHeaderInfo.biHeight; //this could be negative which means the image is flipped

    bool isflipped = height < 0;
    height = abs(height);

    pPixels = new Color[width * height];

    bmp_file.seekg(bmFileheader.bfOffBits);

    // width is pixels of the image. each pixel is 3 bytes. pad row size to multiple of 4 bytes.

    int padding;
    if (bmHeaderInfo.biBitCount == 24)
    {
        padding = (4 - (width * 3 % 4)) % 4;
    }
    else
    {
        padding = 0;
    }

    for (int y = height-1; y >= 0; --y)
    {
        for (int x = 0; x < width; x++)
        {

            Color c(bmp_file.get(), bmp_file.get(), bmp_file.get());
            if (isflipped)
            {
                PutPixel(x, height - 1 - y, c);
            }
            else
            {
                PutPixel(x, y, c);
            }
            bmp_file.seekg(bmHeaderInfo.biBitCount == 32, std::ios::cur);
        }

        //for (int w = 0; w < padding; w++)
        //{
        //    bmp_file.get();
        //}
        //cleaner way is to move up the pointer by 3 from cur pos
        bmp_file.seekg(padding, std::ios::cur);
    }
}


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
    // do not allow self assignment
    if (this == &rhs)
    {
        return *this;
    }

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
