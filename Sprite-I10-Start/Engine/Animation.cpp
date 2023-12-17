#include "Animation.h"

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
    gfx.DrawSprite(pos.x, pos.y, frames[iCurrFrame], sprite, chroma);
}

void Animation::Draw(const Vei2& pos, Graphics& gfx, const RectI& clip) const
{
    gfx.DrawSprite(pos.x, pos.y, frames[iCurrFrame], clip, sprite, chroma);
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
