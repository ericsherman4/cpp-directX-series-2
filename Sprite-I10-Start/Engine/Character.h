#pragma once

#include "Animation.h"
#include "Vec2.h"

class Character
{
private:
    enum class Sequence
    {
        WalkingLeft,
        WalkingRight,
        WalkingUp,
        WalkingDown,
        StandingLeft,
        StandingRight,
        StandingUp,
        StandingDown,
        Count // this is super clever. last thing in enum is obviously going to be the size.
    };

public:
    Character(const Vec2& pos);
    void Draw(Graphics& gfx) const;
    void SetDirection(const Vec2& dir);
    void Update(float dt);
    void ActivateEffect();

private:
    Surface sprite;
    Vec2 pos;
    Vec2 vel = { 0.0f, 0.0f };
    std::vector<Animation> animations;
    Sequence currAnim = Sequence::StandingDown;
    float speed = 110.f;
    static constexpr float effectDuration = 0.045;
    float effectTime = 0.0f;
    bool effectActive = false;
};

