#include "Identify.hpp"

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <fstream>
#include <iostream>

namespace
{
	unsigned int randomValue(void)
	{
		std::ifstream input;
		unsigned int value;
		unsigned int index;
		char byte;

		value = 0;
		input.open("/dev/urandom");
		if (input.is_open())
		{
			index = 0;
			while (index < 4 && input.get(byte))
			{
				value = value * 257u + byte;
				++index;
			}
			if (index == 4)
				return value;
		}
		static unsigned int fallback = 0;
		++fallback;
		return fallback;
	}
}

Base *generate(void)
{
	unsigned int choice;

	choice = randomValue() % 3u;
	if (choice == 0u)
		return new A;
	if (choice == 1u)
		return new B;
	return new C;
}

void identify(Base *p)
{
	if (dynamic_cast<A *>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B *>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C *>(p))
		std::cout << "C" << std::endl;
	else
		std::cout << "Unknown" << std::endl;
}

void identify(Base &p)
{
	try
	{
		(void)dynamic_cast<A &>(p);
		std::cout << "A" << std::endl;
		return;
	}
	catch (...)
	{
	}
	try
	{
		(void)dynamic_cast<B &>(p);
		std::cout << "B" << std::endl;
		return;
	}
	catch (...)
	{
	}
	try
	{
		(void)dynamic_cast<C &>(p);
		std::cout << "C" << std::endl;
		return;
	}
	catch (...)
	{
	}
	std::cout << "Unknown" << std::endl;
}
