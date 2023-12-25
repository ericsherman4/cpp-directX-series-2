#include "Animation.h"
#include "SpriteEffects.h"

Animation::Animation(int x, int y, int width, int height, int numFrames, const Surface& sprite, float holdTime, Color chroma)
    : sprite (sprite)
    , chroma (chroma)
    , holdTime( holdTime)
{
    frames.reserve(numFrames);
    for (int i{ 0 }; i < numFrames; ++i)
    {
        // this does not read the whole grid, just a row of it. x and y indicate what row and how many frames of that row to read / start end.
        frames.emplace_back( x + i * width, x + (i + 1) * width, y, y + height);
    }
}

void Animation::Draw(const Vei2& pos, Graphics& gfx) const
{
    // hw 16
    //gfx.DrawSprite(pos.x, pos.y, frames[iCurrFrame], sprite, SpriteEffect::Ghost{chroma});
    gfx.DrawSprite(pos.x, pos.y, frames[iCurrFrame], sprite, 
        [this](Color cSrc, int xDest, int yDest, Graphics & gfx) 
        {
            if (cSrc != chroma)
            {
                gfx.PutPixel(xDest, yDest,
                    {255u - cSrc.GetR(), 255u - cSrc.GetG(), 255u - cSrc.GetB()}
                );
            }
        }
    );

    //void operator()(Color cSrc, int xDest, int yDest, Graphics & gfx) const
    //{
    //    if (cSrc != chroma)
    //    {
    //        gfx.PutPixel(xDest, yDest, cSrc);
    //    }
    //}

}

void Animation::Draw(const Vei2& pos, Graphics& gfx, const RectI& clip) const
{
    gfx.DrawSprite(pos.x, pos.y, frames[iCurrFrame], clip, sprite, SpriteEffect::Chroma{chroma});
}

void Animation::DrawColor(const Vei2& pos, Graphics& gfx, Color c) const
{
    gfx.DrawSprite(pos.x, pos.y, frames[iCurrFrame], sprite, SpriteEffect::Substitute{ c, chroma });
}

void Animation::Update(float dt)
{
    currFrameTime += dt;
    // use while instead of if so that if the time of multiple frames passes, it consumes all of them.
    while(currFrameTime > holdTime)
    {
        Advance();
        currFrameTime -= holdTime;
    }
}

void Animation::Advance()
{
    iCurrFrame = (iCurrFrame + 1) % static_cast<int>(frames.size());
}
