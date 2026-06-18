#include "Serializer.hpp"

#include <iostream>

int main(void)
{
	Data data;
	uintptr_t raw;
	Data *restored;

	data.number = 42;
	data.text = "CPP06";
	data.value = 6.01;
	raw = Serializer::serialize(&data);
	restored = Serializer::deserialize(raw);
	std::cout << "original: " << &data << std::endl;
	std::cout << "raw: " << raw << std::endl;
	std::cout << "restored: " << restored << std::endl;
	if (restored == &data)
		std::cout << "equal: yes" << std::endl;
	else
		std::cout << "equal: no" << std::endl;
	std::cout << "number: " << restored->number << std::endl;
	std::cout << "text: " << restored->text << std::endl;
	std::cout << "value: " << restored->value << std::endl;
	return 0;
}
