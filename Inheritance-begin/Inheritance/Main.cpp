#include <iostream>
#include <string>
#include <conio.h>
#include <algorithm>

#include "MemeFighter.h"

void TakeWeaponIfDead(MemeFighter& f1, MemeFighter& f2)
{
	if (f1.IsAlive() && !f2.IsAlive() && f2.HasWeapon())
	{
		if (f2.GetWeapon().GetRank() > f1.GetWeapon().GetRank())
		{
			std::cout << f1.GetName() << " takes the " << f2.GetWeapon().GetName() << " from " << f2.GetName() << std::endl;
			f1.GiveWeapon(f2.PilferWeapon());
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
	auto* p1 = &f1;
	auto* p2 = &f2;

	if (p1->GetInitiative() < p2->GetInitiative())
	{
		std::swap(p1, p2);
	}

	p1->SpecialMove(*p2);
	TakeWeaponIfDead(*p1, *p2);
	p2->SpecialMove(*p1);
	TakeWeaponIfDead(*p2, *p1);
}


int main()
{
	// vectors of pointers to the base type! this is the power of polymorphism!
	std::vector<MemeFighter*> t1{
		new MemeFrog("Dat Boi", new Fists),
		new MemeStoner("Good Guy Greg", new Bat),
		new MemeFrog("the WB Frog", new Knife)
	};

	std::vector<MemeFighter*> t2 = {
		new MemeStoner("Bob", new Fists),
		new MemeStoner("jake", new Bat),
		new MemeFrog("Pope", new Knife)
	};

	

	auto alive_pred = [](const MemeFighter* mf)
	{
		return mf->IsAlive();
	};

	while (
		std::any_of(t1.begin(), t1.end(), alive_pred) 
		&& std::any_of(t2.begin(), t2.end(), alive_pred)
	)
	{
		// we do parition to keep live Memes always fighting live memes.
		std::random_shuffle(t1.begin(), t1.end());
		std::partition(t1.begin(), t1.end(), alive_pred);
		std::random_shuffle(t2.begin(), t2.end());
		std::partition(t2.begin(), t2.end(), alive_pred);

		for (size_t i = 0; i < t1.size(); i++)
		{
			// trade blows
			Engage(*t1[i], *t2[i]);
			// special moves
			DoSpecials(*t1[i], *t2[i]);
			std::cout << "-------------------------------------" << std::endl;
		}
		std::cout << "===============================================" << std::endl;


		for (size_t i = 0; i < t1.size(); i++)
		{
			// end of turn maintainence
			t1[i]->Tick();
			t2[i]->Tick();
		}

		std::cout << "===============================================" << std::endl;


		std::cout << "Press any key to continue...";
		while (!_kbhit());
		(void)_getch();
		std::cout << std::endl << std::endl;
	}

	if (std::any_of(t1.begin(), t1.end(), alive_pred))
	{
		std::cout << "Team 1 is victorious!\n";
	}
	else
	{
		std::cout << "Team 2 is victorious!\n";
	}
	
	// big problem with this. 
	// whos destructor is being called?
	// Not calling destructors of our children!
	for (size_t i = 0; i < t1.size(); ++i)
	{
		delete t1[i];
		delete t2[i];
	}

	while (!_kbhit());
	return 0;
}