#include <iostream>
#include <string>
#include <conio.h>
#include <algorithm>
#include <typeinfo>
#include <memory>


#include "MemeFighter.h"

void TakeWeaponIfDead(MemeFighter& taker, MemeFighter& giver)
{
	if (taker.IsAlive() && !giver.IsAlive() && giver.HasWeapon())
	{
		if (giver.GetWeapon()->GetRank() > taker.GetWeapon()->GetRank())
		{
			std::cout << taker.GetName() << " takes the " << giver.GetWeapon()->GetName()
				<< " from " << giver.GetName() << "'s still-cooling corpse." << std::endl;
			taker.GiveWeapon(giver.PilferWeapon());
		}
	}
}

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
	p1->Attack(*p2);
	TakeWeaponIfDead(*p1, *p2);
	p2->Attack(*p1);
	TakeWeaponIfDead(*p2, *p1);
}

void DoSpecials(MemeFighter& f1, MemeFighter& f2)
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
	p1->SpecialMove(*p2);
	TakeWeaponIfDead(*p1, *p2);
	p2->SpecialMove(*p1);
	TakeWeaponIfDead(*p2, *p1);
}

bool AreSameType(MemeFighter& f1, MemeFighter& f2)
{
	if (typeid(f1) == typeid(f2))
	{
		return true;
	}
	return false;
}

int main()
{
	std::vector<std::unique_ptr<MemeFighter>> t1;
	t1.push_back(std::make_unique<MemeFrog>("Dat Boi", new Fists));
	t1.push_back(std::make_unique<MemeStoner>("Good Guy Greg", new Bat));
	t1.push_back(std::make_unique<MemeCat>("Haz Cheeseburger", new Knife));

	std::vector<std::unique_ptr<MemeFighter>> t2;
	t2.push_back(std::make_unique<MemeCat>("NEDM", new Fists));
	t2.push_back(std::make_unique<MemeStoner>("Scumbag Steve", new Bat));
	t2.push_back(std::make_unique<MemeFrog>("Pepe", new Knife));

	const auto alive_pred = [](const std::unique_ptr<MemeFighter>& pf) 
	{ return pf->IsAlive(); };

	while (
		std::any_of(t1.begin(), t1.end(), alive_pred) &&
		std::any_of(t2.begin(), t2.end(), alive_pred))
	{
		std::random_shuffle(t1.begin(), t1.end());
		std::partition(t1.begin(), t1.end(), alive_pred);
		std::random_shuffle(t2.begin(), t2.end());
		std::partition(t2.begin(), t2.end(), alive_pred);

		for (size_t i = 0; i < t1.size(); i++)
		{
			Engage(*t1[i], *t2[i]);
			DoSpecials(*t1[i], *t2[i]);
			std::cout << "------------------------------------" << std::endl;
		}
		std::cout << "=====================================" << std::endl;

		for (size_t i = 0; i < t1.size(); i++)
		{
			t1[i]->Tick();
			t2[i]->Tick();
		}
		std::cout << "=====================================" << std::endl;

		std::cout << "Press any key to continue...";
		while (!_kbhit());
		_getch();
		std::cout << std::endl << std::endl;
	}

	if (std::any_of(t1.begin(), t1.end(), alive_pred))
	{
		std::cout << "Team ONE is victorious!" << std::endl;
	}
	else
	{
		std::cout << "Team TWO is victorious!" << std::endl;
	}

	while (!_kbhit());
	return 0;
}