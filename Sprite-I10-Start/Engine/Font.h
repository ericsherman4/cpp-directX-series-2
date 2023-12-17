#pragma once

#include "Surface.h"
#include "Vec2.h"
#include "Graphics.h"

class Font
{
public:
    Font(const std::string& filename, Color chroma = Colors::White);
    void DrawText(const std::string& text, Color textcolor, const Vei2& pos, Graphics& gfx) const;

private:
    RectI MapGlyphRect(char c) const;

private:
    Surface surface;
    Color chroma;

    int glyphWidth;
    int glyphHeight;

    static constexpr int numColumns = 32;
    static constexpr int numRows = 3;


    static constexpr char firstChar = ' ';
    static constexpr char lastChar = '~';
};

