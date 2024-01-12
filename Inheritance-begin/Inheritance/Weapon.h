#pragma once

#include <iostream>

struct Attribute
{
    int hp;
    int power;
    int speed;
};


class Weapon
{
public:
    Weapon(const std::string& name, int rank)
        : name(name)
        , rank(rank)
    {
    }
    const std::string& GetName() const
    {
        return name;
    }
    int GetRank() const
    {
        return rank;
    }
    virtual int CalculateDamage(const Attribute& attr, Dice& dice) const = 0;

private:
    std::string name;
    int rank;
};

class Fists : public Weapon
{
public:
    Fists()
        : Weapon("fists", 0)
    {}
    int CalculateDamage(const Attribute& attr, Dice& dice) const
    {
        return attr.power + dice.Roll(2);
    }
};


class Knife : public Weapon
{
public:
    Knife()
        : Weapon("knife", 2)
    {}
    int CalculateDamage(const Attribute& attr, Dice& dice) const
    {
        return attr.speed * 3 + dice.Roll(3);
    }
};

class Bat : public Weapon
{
public:
    Bat()
        : Weapon("bat", 1)
    {}
    int CalculateDamage(const Attribute& attr, Dice& dice) const
    {
        return attr.power * 2 + dice.Roll(1);
    }
};


