#include "Identify.hpp"

#include <iostream>

int main(void)
{
	Base *base;
	int index;

	index = 0;
	while (index < 10)
	{
		base = generate();
		std::cout << "pointer: ";
		identify(base);
		std::cout << "reference: ";
		identify(*base);
		delete base;
		++index;
	}
	return 0;
}
