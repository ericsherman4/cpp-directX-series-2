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
	bool IsAlive() const
	{
		return attr.hp > 0;
	}
	int GetInitiative() const
	{
		return attr.speed + Roll(2);
	}
	void Attack(MemeFighter& other) const
	{
		if (IsAlive() && other.IsAlive())
		{
			std::cout << name << " attacks " << other.GetName() << " with his " << pWeapon->GetName()
				<< "!" << std::endl;
			ApplyDamageTo(other, pWeapon->CalculateDamage(attr, d));
		}
	}
	virtual void Tick()
	{
		if (IsAlive())
		{
			const int recovery = Roll();
			std::cout << name << " recovers " << recovery << " HP." << std::endl;
			attr.hp += recovery;
		}
	}
	virtual void SpecialMove(MemeFighter&) = 0;
	virtual ~MemeFighter() = default;
	void GiveWeapon(std::unique_ptr<Weapon> pNewWeapon)
	{
		pWeapon = std::move(pNewWeapon);
	}
	std::unique_ptr<Weapon> PilferWeapon()
	{
		return std::move(pWeapon);
	}
	bool HasWeapon() const
	{
		return pWeapon != nullptr;
	}
	const std::unique_ptr<Weapon>& GetWeapon() const
	{
		return pWeapon;
	}
protected:
	MemeFighter(const std::string& name, int hp, int speed, int power, std::unique_ptr<Weapon> pWeapon)
		:
		name(name),
		attr({ hp,speed,power }),
		pWeapon(std::move(pWeapon))
	{
		std::cout << name << " enters the ring!" << std::endl;
	}
	void ApplyDamageTo(MemeFighter& target, int damage) const
	{
		target.attr.hp -= damage;
		std::cout << target.name << " takes " << damage << " damage." << std::endl;
		if (!target.IsAlive())
		{
			std::cout << "As the life leaves " << target.name << "'s body, so does the poop." << std::endl;
		}
	}
	int Roll(int nDice = 1) const
	{
		return d.Roll(nDice);
	}
protected:
	Attributes attr;
	std::string name;
private:
	std::unique_ptr<Weapon> pWeapon;
	mutable Dice d;
};

class MemeFrog : public MemeFighter
{
public:
	MemeFrog(const std::string& name, std::unique_ptr<Weapon> pWeapon)
		:
		MemeFighter(name, 69, 7, 14, std::move(pWeapon))
	{}
	void SpecialMove(MemeFighter& other) override
	{
		if (IsAlive() && other.IsAlive())
		{
			if (Roll() > 4)
			{
				std::cout << GetName() << " attacks " << other.GetName() << " with a rainbow beam!" << std::endl;
				ApplyDamageTo(other, Roll(3) + 20);
			}
			else
			{
				std::cout << GetName() << " falls off his unicycle." << std::endl;
			}
		}
	}
	void Tick() override
	{
		if (IsAlive())
		{
			std::cout << GetName() << " is hurt by the bad AIDS!" << std::endl;
			ApplyDamageTo(*this, Roll());
			MemeFighter::Tick();
		}
	}
	void Foo()
	{
		std::cout << "Non-virtual MemeFrog function call." << std::endl;
	}
	~MemeFrog() override
	{
		std::cout << "Destroying MemeFrog '" << name << "'!" << std::endl;
	}
};

class MemeCat : public MemeFighter
{
public:
	MemeCat(const std::string& name, std::unique_ptr<Weapon> pWeapon)
		:
		MemeFighter(name, 65, 9, 14, std::move(pWeapon))
	{}
	void SpecialMove(MemeFighter&) override
	{
		if (IsAlive())
		{
			if (Roll() > 2)
			{
				std::cout << GetName() << " eats a cheeseburger and gains 20 HP." << std::endl;
				attr.hp += 20;
			}
			else
			{
				std::cout << GetName() << " meows demurely." << std::endl;
			}
		}
	}
	~MemeCat() override
	{
		std::cout << "Destroying MemeCat '" << name << "'!" << std::endl;
	}
};

class MemeStoner : public MemeFighter
{
public:
	MemeStoner(const std::string& name, std::unique_ptr<Weapon> pWeapon)
		:
		MemeFighter(name, 80, 4, 10, std::move(pWeapon))
	{}
	void SpecialMove(MemeFighter& other) override
	{
		if (IsAlive())
		{
			if (Roll() > 3)
			{
				if (typeid(MemeFrog) == typeid(other))
				{
					std::cout << GetName() + " says: 'Oh sweet dude, it's a cool little froggie bro.'\n";
				}
				else if (typeid(MemeStoner) == typeid(other))
				{
					std::cout << GetName() + " says: 'Duuuuuude.'\n";
				}
				else if (typeid(MemeCat) == typeid(other))
				{
					std::cout << GetName() + " says: 'Hey kitty bro, can I pet you?'\n";
				}
				std::cout << GetName() << " smokes the dank sticky icky, becoming " << "Super " << GetName() << std::endl;
				name = "Super " + name;
				attr.speed += 3;
				attr.power = (attr.power * 69) / 42;
				attr.hp += 10;
			}
			else
			{
				std::cout << GetName() << " spaces out." << std::endl;
			}
		}
	}
	~MemeStoner() override
	{
		std::cout << "Destroying MemeStoner '" << name << "'!" << std::endl;
	}
};