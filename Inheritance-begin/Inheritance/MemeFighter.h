#pragma once

#include <iostream>

#include "Dice.h"
#include "Weapon.h"



class MemeFighter
{
public:

	const std::string& GetName() const
	{
		return name;
	}
	int GetInitiative() const
	{
		const int initiative = attr.speed + Roll(2);
		std::cout << name << " got " << initiative << " initiative.\n";
		return initiative;
	}
	bool IsAlive() const
	{
		return attr.hp > 0;
	}
	void Attack(MemeFighter& target) const
	{
		if (IsAlive() && target.IsAlive())
		{
			std::cout << name << " attacks " << target.name << " with his " << pWeapon->GetName() << "!\n";
			ApplyDamageTo(target, pWeapon->CalculateDamage(attr, dice));
		}
	}
	void GiveWeapon(Weapon* pnewWeapon)
	{
		delete pWeapon;
		pWeapon = pnewWeapon;
	}
	bool HasWeapon() const
	{
		return pWeapon != nullptr;
	}
	const Weapon& GetWeapon() const
	{
		return *pWeapon;
	}

	Weapon* PilferWeapon()
	{
		Weapon* temp = pWeapon;
		pWeapon = nullptr;
		return temp;
	}

	virtual void Tick()
	{
		if (IsAlive())
		{
			const int hp_gain = Roll();
			attr.hp += hp_gain;
			std::cout << name << " gained " << hp_gain << " HP.\n";
		}
	}
	virtual void SpecialMove(MemeFighter&) = 0;
	virtual ~MemeFighter()
	{
		std::cout << "Destorying MemeFighter " << name << "\n";
		delete pWeapon;
	}

protected:
	// I guess another way to make not being able to construct the base class is by making the constructor protected
	MemeFighter(int hp, int speed, int power, std::string name, Weapon *pWeapon = nullptr)
		: attr{hp,power,speed}
		, name(name)
		, pWeapon(pWeapon)
	{
		std::cout << name << " enters the ring!\n";
	}

	int Roll(int nDice = 1) const
	{
		return dice.Roll(nDice);
	}
	void ApplyDamageTo(MemeFighter& target, int damage) const
	{
		target.attr.hp -= damage;
	}

protected:
	Attribute attr;
	std::string name;

private:
	mutable Dice dice;
	Weapon* pWeapon = nullptr;
};


class MemeFrog : public MemeFighter
{
public:
	MemeFrog(const std::string& name, Weapon *pWeapon)
		: MemeFighter(69, 7, 14, name, pWeapon)
	{
	}
	void SpecialMove(MemeFighter& target) override
	{
		if (IsAlive() && target.IsAlive())
		{
			// 1/3 chance of happening, lol
			if (Roll(1) < 3)
			{
				std::cout << GetName() << " did a special move on " << target.GetName() << ".\n";
				ApplyDamageTo(target, 20 + Roll(3));
			}
		}
	}
	void Tick() override
	{
		if (IsAlive())
		{
			std::cout << GetName() << " got some self damage.\n";
			ApplyDamageTo(*this, Roll()); //apply damage to self.
			MemeFighter::Tick();

		}
	}
	~MemeFrog()
	{
		std::cout << "Destorying MemeFrog " << name << "\n";
	}
};


class MemeStoner : public MemeFighter
{
public:
	MemeStoner(const std::string& name, Weapon *pWeapon)
		: MemeFighter(80, 4, 10, name, pWeapon)
	{
	}
	void SpecialMove(MemeFighter& other) override
	{
		if (IsAlive())
		{
			// 1/2 chance
			if (Roll() % 2 == 0)
			{

				attr.power = (attr.power * 69) / 42;
				attr.hp += 10;
				attr.speed += 3;

				name = "Super " + name;

				std::cout << GetName() << " rolled a special move and recieved 10 hp, 1 power, 3 speed, and the Super name\n";

			}
		}
	}
	~MemeStoner()
	{
		std::cout << "Destorying MemeStoner " << name << "\n";
	}
};


class MemeCat : public MemeFighter
{
public:
	MemeCat(const std::string& name, Weapon* pWeapon)
		: MemeFighter(80, 4, 10, name, pWeapon)
	{
	}
	void SpecialMove(MemeFighter&) override
	{
		if (IsAlive())
		{
			// 1/2 chance
			if (Roll() % 2 == 0)
			{
				attr.power = (attr.power * 69) / 42;
				attr.hp += 10;
				attr.speed += 3;

				name = "Super " + name;

				std::cout << GetName() << " rolled a special move and recieved 10 hp, 1 power, 3 speed, and the Super name\n";

			}
		}
	}
	~MemeCat()
	{
		std::cout << "Destorying MemeStoner " << name << "\n";
	}
};