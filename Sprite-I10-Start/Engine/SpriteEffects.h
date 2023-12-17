#pragma once

#include "Colors.h"
#include "Graphics.h"

namespace SpriteEffect
{
    // create function objects out of these classes
    class Chroma
    {
    public:
        Chroma(Color c)
            : chroma(c)
        {
        }
        void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx) const
        {
            if (cSrc != chroma)
            {
                gfx.PutPixel(xDest, yDest, cSrc);
            }
        }
    private:
        Color chroma;
    };

    class Copy
    {
    public:
        void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx) const
        {
            gfx.PutPixel(xDest, yDest, cSrc);
        }
    };

    class Substitute
    {
    public:
        Substitute(Color sub, Color chroma = Colors::Magenta)
            : chroma(chroma)
            , sub(sub)
        {
        }
        void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx) const
        {
            if (cSrc != chroma)
            {
                gfx.PutPixel(xDest, yDest, sub);
            }
        }
    private:
        Color chroma;
        Color sub;
    };

    class Ghost
    {
    public:
        Ghost(Color c)
            : chroma(c)
        {
        }
        void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx) const
        {
            if (cSrc != chroma)
            {
                const Color dstPixel = gfx.GetPixel(xDest, yDest);
                const Color blendedPixel(
                    (dstPixel.GetR() + cSrc.GetR()) / 2,
                    (dstPixel.GetG() + cSrc.GetG()) / 2,
                    (dstPixel.GetB() + cSrc.GetB()) / 2
                );
                gfx.PutPixel(xDest, yDest, blendedPixel);
            }
        }
    private:
        Color chroma;
    };

}
