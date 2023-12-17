#pragma once


#include "Surface.h"
#include "Graphics.h"
#include <vector>

class Animation
{

public: 
    // assume animation seq left to right and top to bottom
    Animation(int x, int y, int width, int height, int numFrames, const Surface& sprite, float holdTime, Color chroma= Colors::Magenta);
    void Draw(const Vei2& pos, Graphics& gfx) const;
    void Draw(const Vei2& pos, Graphics& gfx, const RectI& clip) const;
    void Update(float dt);

private:
    void Advance();
private:
    Color chroma;
    const Surface& sprite;
    std::vector<RectI> frames;
    int iCurrFrame = 0;
    float holdTime; // how long any give frame displayed before advance
    float currFrameTime = 0.0f;
};

