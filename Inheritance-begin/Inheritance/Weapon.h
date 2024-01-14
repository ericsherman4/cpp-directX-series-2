#pragma once

#include <iostream>

struct Attributes
{
    int hp;
    int power;
    int speed;
};

class Weapon
{
public:
    Weapon(const std::string& name, int rank)
        :
        name(name),
        rank(rank)
    {}
    const std::string& GetName() const
    {
        return name;
    }
    int GetRank() const
    {
        return rank;
    }
    virtual int CalculateDamage(const Attributes& attr, Dice& d) const = 0;
private:
    std::string name;
    int rank;
};

class Fists : public Weapon
{
public:
	Fists()
		:
		Weapon("fists", 0)
	{}
	virtual int CalculateDamage(const Attributes& attr, Dice& d) const
	{
		return attr.power + d.Roll(2);
	}
};

class Knife : public Weapon
{
public:
	Knife()
		:
		Weapon("knife", 2)
	{}
	virtual int CalculateDamage(const Attributes& attr, Dice& d) const
	{
		return attr.speed * 3 + d.Roll(3);
	}
};

class Bat : public Weapon
{
public:
	Bat()
		:
		Weapon("bat", 1)
	{}
	virtual int CalculateDamage(const Attributes& attr, Dice& d) const
	{
		return attr.power * 2 + d.Roll(1);
	}
};

