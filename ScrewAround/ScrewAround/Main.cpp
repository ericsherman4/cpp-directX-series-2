#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

void print(const std::vector<std::string>& vec)
{
	std::cout << "start:" << std::endl;
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
	std::cout << ":end" << std::endl;
}

int main()
{
	// move things to new vector if it is > 10 characters
	std::vector<std::string> from = { "heydad", "my name is smithy", "jack sparrow is cool", "hey i love you"};
	std::vector<std::string> dest;
	dest.reserve(from.size());

	print(from);

	std::copy_if(
		std::make_move_iterator(from.begin()),
		std::make_move_iterator(from.end()),
		std::back_inserter(dest), 
		//dest.end(), // this doesn't work because you have the begin pointer 
		// pointing to element 0 and the end pointer points to element 1 because 
		// the vector is empty. So it fails after two iterations.
		[](const std::string & str)
		{
			return str.length() > 10;
		}
	);

	print(from);
	print(dest);

	std::cin.get();
	return 0;
}