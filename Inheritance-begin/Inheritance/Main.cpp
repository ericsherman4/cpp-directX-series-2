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

	MemeFighter(int hp, int speed, int power, std::string name)
		: hp (hp)
		, speed(speed)
		, power(power)
		, name(name)
	{
	}

	std::string GetName() {
		return name;
	}
	int GetInitiative() {
		const int initiative = speed + dice.Roll(2);
		std::cout << name << " got " << initiative << " initiative.\n";
		return initiative;
	}
	bool IsAlive() {
		return hp <= 0; 
	}
	void Punch(MemeFighter& other)
	{
		if (IsAlive())
		{
			const int damage = power + dice.Roll(2);
			other.hp -= damage;
			std::cout << name << " punched " << other.name << " and did " << damage << " damage.\n";
		}
	}
	void Tick()
	{
		if (IsAlive())
		{
			const int hp_gain = dice.Roll(1);
			hp += hp_gain;
			std::cout << name << " gained " << hp_gain << ".\n";
		}
	}

protected:
	Dice dice;
	int hp;
	int speed;
	int power;
	std::string name;
};

class MemeFrog : public MemeFighter
{
public:
	MemeFrog(std::string name)
		: MemeFighter(69, 7, 14, name)
	{
	}

	void SpecialMove(MemeFighter& other)
	{
		if (IsAlive())
		{
			// 1/3 chance of happening, lol
			if (dice.Roll(1) < 3)
			{
				const int damage = 20 + dice.Roll(3);
				other.hp -= damage;
				std::cout << GetName() << " did a special move on " << other.GetName() << " and did " << damage << " damage.\n";
			}
		}
	}

	void Tick()
	{
		if (IsAlive())
		{
			const int hp_lose = dice.Roll(1);
			hp -= hp_lose;
			std::cout << GetName() << " gained " << hp_lose << ".\n";

		}
	}
};
class MemeStoner : public MemeFighter
{

public:
	MemeStoner(std::string name)
		: MemeFighter(80, 4, 10, name)
	{
	}

	void SpecialMove()
	{
		if (IsAlive())
		{
			// 1/2 chance
			if (dice.Roll(1) % 2 == 0)
			{
				power += 1;
				hp += 10;

				name.insert(name[0], "Super ");

				std::cout << GetName() << " rolled a special move and recieved 10 hp and 1 power and the Super name\n";

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

int main()
{
	MemeFrog f1("Dat Boi");
	MemeStoner f2("Good Guy Greg");

	while (f1.IsAlive() && f2.IsAlive())
	{
		// trade blows
		Engage(f1, f2);
		// special moves
		f2.SpecialMove();
		f1.SpecialMove(f2);
		// end of turn maintainence
		f1.Tick();
		f2.Tick();

		std::cout << "Press any key to continue...";
		while (!_kbhit());
		_getch();
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