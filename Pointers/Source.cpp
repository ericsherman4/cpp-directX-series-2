#include <conio.h>
#include <fstream>


namespace sherm {

	void print(const char* s)
	{
		for (; *s != 0; s++)
		{
			_putch(*s);
		}
	}

	void read(char* buf, int maxSize)
	{
		const char* const pEnd = buf + maxSize;
		for (char c = _getch(); c != 13 && (buf + 1 < pEnd); c = _getch(), buf++)
		{
			_putch(c);
			*buf = c;
		}
		*buf = 0;
	}

	int str2int(const char* s)
	{
		// scan to start point
		const char* p = s;
		for (; *p >= '0' && *p <= '9'; p++);
		p--;

		int val = 0;
		int place = 1;
		// convert place values and accumulate
		for (; p >= s; p--)
		{
			val += (*p - '0') * place;
			place *= 10;
		}

		return val;
	}

	int fib(int n)
	{
		if (n < 2)
		{
			return n;
		}
		return fib(n - 1) + fib(n - 2);
	}

	void strrev(char* pl)
	{
		// scan to start point
		char* pr = pl;
		for (; *pr != 0; pr++);
		pr--;

		for (; pl < pr; pl++, pr--)
		{
			const char temp = *pl;
			*pl = *pr;
			*pr = temp;
		}
	}

	void int2str(int val, char* buf, int size)
	{
		char* const pStart = buf;
		char* const pEnd = buf + size;
		for (; val > 0 && (buf + 1 < pEnd); val /= 10, buf++)
		{
			*buf = '0' + val % 10;
		}
		*buf = 0;
		strrev(pStart);
	}
}

int main()
{

	std::ifstream warp_file("warp.txt");
	constexpr int file_size = 3359405 + 1; // when you read in this file, new lines will be translated from two characters to one if you remember
											// so the file will be shorter. but also add an extra byte for new line character in case there is no newlines in the file
	char *warp_string =  new char[file_size];
	if (!warp_string)
		return -1;

	int i = 0;
	for (char c = warp_file.get(); warp_file.good(); c = warp_file.get())
	{
		warp_string[i++] = c;
	}
	warp_string[i++] = 0; // null terminator

	char buffer[256];
	sherm::int2str(i, buffer, sizeof(buffer));
	sherm::print(buffer);

	delete [] warp_string;

	while (!_kbhit());
	return 0;
}