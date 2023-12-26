#include <iostream>
#include <string>

class Smasher
{
public:
	Smasher()
		:
		Smasher( 69,1,"McDefault" )
	{}
	Smasher( int hp,int str,const std::string& name )
		:
		hp( hp ),
		str( str ),
		name( name )
	{}
	int GetStr() const
	{
		return str;
	}
	int GetHP() const
	{
		return hp;
	}
	const std::string& GetName() const
	{
		return name;
	}
	void Smash( Smasher& target ) const
	{
		if( target.IsDead() )
		{
			std::cout << name << " smashes " << target.GetName() << "'s dead body. Still dead.\n";
		}
		else
		{
			std::cout << name << " smashes " << target.GetName() << ".\n";
			target.TakeDamage( GetStr() );
		}
	}
	void TakeDamage( int damage )
	{
		std::cout << name << " takes " << damage << " damage.\n";
		hp -= damage;

		if( IsDead() )
		{
			std::cout << name << " dies.\n";
		}
	}
	bool IsDead() const
	{
		return hp <= 0;
	}

protected:
	int hp;
	int str; //strength

private:
	std::string name;
};

class EliteSmasher : public Smasher
{
public: 

	EliteSmasher(int hp, int str, const std::string& name)
		: Smasher(hp, str, name)
	{
	}

	// we want a supersmash powerup 
	void SuperSmash(Smasher& target)
	{
		if (sp > 0)
		{
			if (target.IsDead())
			{
				std::cout << GetName() << " SUPER smashes " << target.GetName() << "'s dead body. Still dead.\n";
			}
			else
			{
				std::cout << GetName() << " SUPER smashes " << target.GetName() << ".\n";
				target.TakeDamage(GetStr() * 2);
			}
			sp -= 3;
		}
		else
		{
			std::cout << GetName() << " tried to use super smash on " << target.GetName() << ", but he didn't have enough goddam sp." << "\n";
		}
	}

	void PepUp()
	{
		if (sp >= 2)
		{
			std::cout << GetName() << " uses Pep Up and gains 30 hp and 10 str.\n";
			hp += 30;
			str += 10;
			sp -= 2;
		}
		else
		{
			std::cout << GetName() << " tried to use Pep Up but lacks sp.\n";
		}
	}



	// override! or is it? cause cosnt specifier was removed?
	void Smash(Smasher& target)
	{		
		Smasher::Smash(target);
		std::cout << GetName() << " recovers 2 sp.\n";
		sp += 2;
	}

private:
	int sp = 6;

};

int main()
{
	Smasher df( 100,30,"Dik Fuk" );
	EliteSmasher tb(100,35, "Tutor Bill");

	df.Smash(tb); // passed an elitesmasher to a function that just takes smasher as an argument.
	tb.PepUp();
	tb.SuperSmash( df );
	tb.SuperSmash( df );
	tb.SuperSmash(df);
	tb.Smash( df );
	tb.Smash( df );
	tb.SuperSmash( df );


	std::cin.get();
	return 0;
}