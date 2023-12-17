#include "Character.h"

Character::Character(const Vec2& pos)
    : pos( pos)
    , sprite( "link90x90.bmp")
{
    // walking animations
    animations.reserve(static_cast<int>(Sequence::Count));
    for (int i{ 0 }; i <= static_cast<int>(Sequence::WalkingDown); ++i)
    {
        animations.emplace_back(90,90*i,90,90,4,sprite,0.16f);
    }

    // standing animations
    for (int i{ static_cast<int>(Sequence::StandingLeft) }; i <= static_cast<int>(Sequence::StandingDown); ++i)
    {
        animations.emplace_back(0, 90 * (i - static_cast<int>(Sequence::StandingLeft)), 90, 90, 1, sprite, 0.16f);
    }
}

void Character::Draw(Graphics& gfx) const
{
    animations[static_cast<int>(currAnim)].Draw(static_cast<Vei2>(pos), gfx);
}

void Character::SetDirection(const Vec2& dir)
{
    // x dominated motion. if any x motion, y is not used.
    if (dir.x > 0.f)
    {
        currAnim = Sequence::WalkingRight;
    }
    else if (dir.x < 0.f)
    {
        currAnim = Sequence::WalkingLeft;
    }
    else if (dir.y > 0.f)
    {
        currAnim = Sequence::WalkingDown;
    }
    else if (dir.y < 0.f)
    {
        currAnim = Sequence::WalkingUp;
    }
    else
    {
        // we were standing. check velocity to see what is the last direction we were moving in
        if (vel.x > 0.0f)
        {
            currAnim = Sequence::StandingRight;
        }
        else if (vel.x < 0.0f)
        {
            currAnim = Sequence::StandingLeft;
        }
        else if (vel.y > 0.0f)
        {
            currAnim = Sequence::StandingDown;
        }
        else if (vel.y < 0.0f)
        {
            currAnim = Sequence::StandingUp;
        }
    }

    // assuming dir is just a unit vector to the direction
    vel = dir * speed;

}

void Character::Update(float dt)
{
    pos += vel * dt;
    animations[static_cast<int>(currAnim)].Update(dt);
}
