#include <iostream>
#include <string>
#include <conio.h>
#include <random>

class Dice
{
public:
	int Roll(int nDice)
	{
		int total = 0;
		for (int n = 0; n < nDice; n++)
		{
			total += d6(rng);
		}
		return total;
	}
private:
	std::uniform_int_distribution<int> d6 = std::uniform_int_distribution<int>(1, 6);
	std::mt19937 rng = std::mt19937(std::random_device{}());
};


class MemeFighter
{
public:

	const std::string & GetName() const
	{
		return name;
	}
	int GetInitiative() const
	{
		const int initiative = speed + Roll(2);
		std::cout << name << " got " << initiative << " initiative.\n";
		return initiative;
	}
	bool IsAlive() const 
	{
		return hp > 0; 
	}
	void Punch(MemeFighter& target) const
	{
		if (IsAlive() && target.IsAlive())
		{
			std::cout << name << " punched " << target.name << "\n";
			ApplyDamageTo(target, power + Roll(2));
		}
	}
	void Tick()
	{
		if (IsAlive())
		{
			const int hp_gain = Roll();
			hp += hp_gain;
			std::cout << name << " gained " << hp_gain << " HP.\n";
		}
	}
	virtual void SpecialMove(MemeFighter&) = 0;

protected:
	// I guess another way to make no make the base class is to make constructor protected
	MemeFighter(int hp, int speed, int power, std::string name)
		: hp(hp)
		, speed(speed)
		, power(power)
		, name(name)
	{
		std::cout << name << " enters the ring!\n";
	}
	int Roll(int nDice = 1) const
	{
		return dice.Roll(nDice);
	}
	void ApplyDamageTo(MemeFighter& target, int damage) const
	{
		target.hp -= damage;
	}

protected:
	int hp;
	int speed;
	int power;
	std::string name;
	
private:
	mutable Dice dice;
};


class MemeFrog : public MemeFighter
{
public:
	MemeFrog(const std::string &name)
		: MemeFighter(69, 7, 14, name)
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
	void Tick()
	{
		if (IsAlive())
		{
			std::cout << GetName() << " got some self damage.\n";
			ApplyDamageTo(*this, Roll()); //apply damage to self.
			MemeFighter::Tick();

		}
	}
};


class MemeStoner : public MemeFighter
{
public:
	MemeStoner(const std::string& name)
		: MemeFighter(80, 4, 10, name)
	{
	}
	void SpecialMove(MemeFighter&) override
	{
		if (IsAlive())
		{
			// 1/2 chance
			if (Roll() % 2 == 0)
			{
				power = (power * 69) / 42;
				hp += 10;
				speed += 3;

				name = "Super " + name;

				std::cout << GetName() << " rolled a special move and recieved 10 hp, 1 power, 3 speed, and the Super name\n";

			}
		}
	}
};


void Engage(MemeFighter& f1, MemeFighter& f2)
{
	// pointers for sorting purposes
	auto* p1 = &f1;
	auto* p2 = &f2;
	// determine attack order
	if (p1->GetInitiative() < p2->GetInitiative())
	{
		std::swap(p1, p2);
	}
	// execute attacks
	p1->Punch(*p2);
	p2->Punch(*p1);
}
void DoSpecials(MemeFighter& f1, MemeFighter& f2)
{
	auto* p1 = &f1;
	auto* p2 = &f2;

	if (p1->GetInitiative() < p2->GetInitiative())
	{
		std::swap(p1, p2);
	}

	p1->SpecialMove(*p2);
	p2->SpecialMove(*p1);
}

int main()
{
	MemeFrog f1("Dat Boi");
	MemeStoner f2("Good Guy Greg");

	while (f1.IsAlive() && f2.IsAlive())
	{
		// trade blows
		Engage(f1, f2);
		// special moves
		DoSpecials(f1, f2);
		// end of turn maintainence
		f1.Tick();
		f2.Tick();

		std::cout << "Press any key to continue...";
		while (!_kbhit());
		(void)_getch();
		std::cout << std::endl << std::endl;
	}

	if (f1.IsAlive())
	{
		std::cout << f1.GetName() << " is victorious!";
	}
	else
	{
		std::cout << f2.GetName() << " is victorious!";
	}
	while (!_kbhit());
	return 0;
}