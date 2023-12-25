#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <numeric>

////////////////////////////////////////////////////////////////////////////
//     !! HOMEWORK !!
// use the C++ <algorithms> as extensively as you can for these problems!

// you may not modify this
struct Pube
{
	int num;
	std::string str;
	bool operator<( const Pube& rhs ) const
	{
		return num < rhs.num;
	}
	operator int() const
	{
		return num;
	}
};

// write your remove_erase_if template function here!
//template<typename T, class UnaryOperator>
//void remove_erase_if(std::vector<T>& v, UnaryOperator op) you did this, more generally

template<typename T, class UnaryOperator>
void remove_erase_if(T& v, UnaryOperator op)
{
	auto it = std::remove_if(
		v.begin(), v.end(), op
	);

	v.erase(it, v.end());
}


// write your custom insertion operator here!
std::ostream& operator<<(std::ostream& lhs, const Pube& rhs)
{
	lhs << rhs.num << ", " << rhs.str << std::endl;
	return lhs;
}

int main()
{
	// materiel (do not modify!)
	const std::vector<Pube> numbers = { 
		{ 0,"zero" },
		{ 9,"nine" },
		{ 7,"seven" },
		{ 2,"two" },
		{ 8,"eight" },
		{ 3,"three" },
		{ 4,"four" },
		{ 1,"one" },
		{ 6,"six" },
		{ 5,"five" }
	};
	const std::vector<Pube> memes = {
		{ 3,"dat boi" },
		{ 1,"yaaaas" },
		{ 3,"soviet russia" },
		{ 1,"damn daniel" },
		{ 1,"hipster ariel" },
		{ 3,"harambe" },
		{ 2,"doge" },
		{ 3,"cash me outside" },
		{ 2,"henlo" },
		{ 3,"kappa" }
	};
	const std::string nambies = "eight one six eight three three eight five four two nine six nine";
	const std::string numpies = { 6, 6, 5, 0, 6, 1, 8, 6 };

	// Problem 1:
	// create a vector that contains 4 copies of each of the elements of memes
	// sort it first by number descending (score from 3 to 1) and then name ascending
	// output sorted meme list w/ score and name using custom insertion operator
	std::cout << "<< Sort Memes >>" << std::endl;
	{
		std::vector<Pube> new_memes;
		new_memes.reserve(memes.size() * 4);
		for (int i{ 0 }; i < 4; ++i)
		{
			// back insert operator from iterator class.
			std::back_insert_iterator<std::vector<Pube>> back_it(new_memes);
			std::copy(memes.begin(), memes.end(),back_it);
		}

		// the thing that you want it to be sorted by first is actually the last operation done.
		// so we want number descending first, but actually this operation should be last!
		std::sort(new_memes.begin(), new_memes.end(),
			[](const Pube & p1, const Pube & p2) {
				return (p1.str.compare(p2.str)) < 0;
			}
		);

		// this will not perserve alphabetical nature. so needs to be stable_sort instead of sort
		std::stable_sort(new_memes.begin(), new_memes.end(), 
			[](const Pube& p1, const Pube& p2) {
				// should return true if the object is ordered before the second
				return p1.num > p2.num;

			}
		);

		//std::copy(new_memes.begin(), new_memes.end(), std::ostream_iterator<Pube>(std::cout, "\n"));
		//std::cout << "============================================" << std::endl << std::endl;

		std::copy(new_memes.begin(), new_memes.end(), std::ostream_iterator<Pube>(std::cout, "\n"));

	}
	std::cout << "============================================" << std::endl << std::endl;

	// Problem 2:
	// output nambies as string of digits without spaces
	// (can be done in single statement!)
	std::cout << "<< Number Words to Digits >>" << std::endl;
	{
		// code goes here
		// this will run on very character.
		//std::copy_if(nambies.begin(), nambies.end(), std::ostream_iterator<int>(std::cout),
		//	[](char &s) 
		//	{
		//		return true;
		//	}
		//);

		//https://stackoverflow.com/questions/23714445/passing-temporary-istringstream-object-to-istream-iteratorstring

		// string streams extract words at a time instead of characters
		std::istringstream iss(nambies);

		std::transform(
			// When reading characters, std::istream_iterator skips whitespace by default
			std::istream_iterator<std::string>(iss),
			std::istream_iterator<std::string>(), //end iterator of istream is just default constructed
			std::ostream_iterator<int>(std::cout),
			// Unary function that accepts one element of the type pointed to by InputIterator as argument, and returns some result value convertible to the type pointed to by OutputIterator.
			// It is automatically space delimited somehow which is cool. 
			[&numbers](const std::string & s) 
			{
				// use numbers as the look up table	
				//auto it = std::find_if(numbers.begin(), numbers.end(), 
				//	[&s](const Pube& p) 
				//	{
				//		return p.str.compare(s) == 0;
				//	}
				//);
				//return it->num;

				// alternatively, you can do the above in one line
				return std::find_if(numbers.begin(), numbers.end(),
					[&s](const Pube& p)
					{
						return p.str.compare(s) == 0;
					}
				)->num; //the find_if returns and iterator and then deference to get the num.
			}
		);

		std::cout << std::endl;




	}
	std::cout << "============================================" << std::endl << std::endl;

	// Problem 3:
	// output numpies as a string of words separated by spaces
	// don't use std::find_if or other searches
	std::cout << "<< Digits to Number Words >>" << std::endl;
	{
		// code goes here

		// the string is build usng ascii numbers so it prints out as garbage
		// std::cout << numpies << std::endl;

		std::vector<Pube> copy = numbers;
		std::sort(copy.begin(), copy.end());

		std::transform(numpies.begin(), numpies.end(), std::ostream_iterator<std::string>(std::cout, " "),
			[&copy](const char & c) // could also just have done int n as a parameter
			{
				return copy[c].str;
			}
		);
	}
	std::cout << "============================================" << std::endl << std::endl;

	// Problem 4:
	// find the product of all numbers in nambies
	// and output of course
	std::cout << "<< Product >>" << std::endl;
	{
		// code goes here
		std::istringstream iss(nambies);

		int res = 1;

		std::for_each(
			std::istream_iterator<std::string>(iss),
			std::istream_iterator<std::string>(),
			[&res, &numbers](const std::string & s)
			{
				auto it = std::find_if(numbers.begin(), numbers.end(), 
					[&s](const Pube& p) 
					{
						return p.str.compare(s) == 0;
					}
				);
				
				res *= it->num;
			}
		);

		// another way you could have done it is with a vector of ints.
		//once you have that, then do:
		// you make a multiplier function object which is cool.
		// int num = std::accumulate(nums_vec.begin(), nums_vec.end(),1,std::multiplies<int>{})

		std::cout << res << std::endl;
		
	}
	std::cout << "============================================" << std::endl << std::endl;

	// Problem 5:
	// find sums of corresponding nums in numbers and memes
	// output as comma separated list
	std::cout << "<< Parallel Sum >>" << std::endl;
	{
		// code goes here
		std::transform(
			numbers.begin(),
			numbers.end(),
			memes.begin(),
			std::ostream_iterator<int>(std::cout, ", "),
			//[](const Pube& p1, const Pube& p2)
			//{
			//	// casting to int operator provided
			//	return int(p1) + int(p2);
			//}
			
			// instead of above, use built in. 
			// also the reason you can do this even with pubes is because pubes 
			// overloaded the int cast operation, so it auto converts to ints for you
			std::plus<int>{}
		);

	}
	std::cout << "============================================" << std::endl << std::endl;

	// Problem 6:
	// write a template function (not here, above int main())
	// that will remove elements from vector based on unary predicate
	// the following code should not be modified
	std::cout << "<< Top Memes >>" << std::endl;
	{
		// copy to get non-const vector
		auto maymays = memes;
		// remove all memes with score below 3
		remove_erase_if( maymays,[]( const Pube& p ) { return p.num < 3; } );
		// output results
		std::copy( maymays.begin(),maymays.end(),std::ostream_iterator<Pube>( std::cout,"\n" ) );
	}
	std::cout << "============================================" << std::endl << std::endl;

	std::cin.get();
	return 0;
}