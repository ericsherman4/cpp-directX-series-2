#include "Font.h"
#include "assert.h"

Font::Font(const std::string& filename, Color chroma)
    : surface(filename)
    , chroma(chroma)
    , glyphWidth (surface.GetWidth() / numColumns)
    , glyphHeight (surface.GetHeight() / numRows)
{
    assert(glyphWidth * numColumns == surface.GetWidth());
    assert(glyphHeight * numRows == surface.GetHeight());
}

void Font::DrawText(const std::string& text, Color textcolor, const Vei2& pos, Graphics& gfx) const
{
    Vei2 currpos = pos;
    for (char c : text)
    {
        if (c == '\n')
        {
            currpos.x = pos.x;
            currpos.y += glyphHeight;
            continue;
        }
        // skip space because space is just blank dont need to draw anything
        if (c >= (firstChar + 1) && c <= lastChar)
        {
            gfx.DrawSpriteSubstitue(currpos.x, currpos.y, textcolor, MapGlyphRect(c),surface, chroma);
        }
        currpos.x += glyphWidth;
    }
}

RectI Font::MapGlyphRect(char c) const
{

    assert(c >= firstChar && c <= lastChar);

    char index = c - firstChar;
    const int left = (index % numColumns) * glyphWidth;
    const int right = left + glyphWidth;
    const int top = (index / numColumns) * glyphHeight;
    const int bottom = top +  glyphHeight;

    return RectI(left, right , top, bottom);
}
