#include "ScalarConverter.hpp"

#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

namespace
{
	bool isDigit(char c)
	{
		return c >= '0' && c <= '9';
	}

	bool isCharLiteral(const std::string &literal)
	{
		return (literal.length() == 3 && literal[0] == '\''
			&& literal[2] == '\'');
	}

	bool isSingleChar(const std::string &literal)
	{
		return literal.length() == 1 && !isDigit(literal[0]);
	}

	bool isSpecial(const std::string &literal)
	{
		return literal == "nan" || literal == "nanf"
			|| literal == "+inf" || literal == "+inff"
			|| literal == "-inf" || literal == "-inff";
	}

	bool isFloatLiteral(const std::string &literal)
	{
		return literal.length() > 1 && literal[literal.length() - 1] == 'f';
	}

	bool hasValidNumberChars(const std::string &number)
	{
		std::size_t i;

		if (number.empty())
			return false;
		i = 0;
		if (number[i] == '+' || number[i] == '-')
			++i;
		if (i == number.length())
			return false;
		while (i < number.length())
		{
			if (!isDigit(number[i]) && number[i] != '.')
				return false;
			++i;
		}
		return true;
	}

	bool parseDouble(const std::string &literal, double &value)
	{
		std::string number;
		std::istringstream stream;
		char rest;

		number = literal;
		if (isFloatLiteral(number))
			number = number.substr(0, number.length() - 1);
		if (!hasValidNumberChars(number))
			return false;
		if (isFloatLiteral(literal) && number.find('.') == std::string::npos)
			return false;
		stream.str(number);
		stream >> value;
		if (stream.fail())
			return false;
		if (stream >> rest)
			return false;
		return true;
	}

	bool isIntegral(double value)
	{
		if (value < static_cast<double>(std::numeric_limits<long>::min())
			|| value > static_cast<double>(std::numeric_limits<long>::max()))
			return false;
		return static_cast<double>(static_cast<long>(value)) == value;
	}

	void resetFormat(void)
	{
		std::cout.unsetf(std::ios::floatfield);
		std::cout.precision(6);
	}

	void printSpecial(const std::string &literal)
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		if (literal == "nan" || literal == "nanf")
		{
			std::cout << "float: nanf" << std::endl;
			std::cout << "double: nan" << std::endl;
		}
		else if (literal[0] == '-')
		{
			std::cout << "float: -inff" << std::endl;
			std::cout << "double: -inf" << std::endl;
		}
		else
		{
			std::cout << "float: +inff" << std::endl;
			std::cout << "double: +inf" << std::endl;
		}
	}

	void printChar(double value)
	{
		if (!isIntegral(value) || value < 0.0 || value > 127.0)
			std::cout << "char: impossible" << std::endl;
		else if (value < 32.0 || value > 126.0)
			std::cout << "char: Non displayable" << std::endl;
		else
			std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
	}

	void printInt(double value)
	{
		if (!isIntegral(value)
			|| value < static_cast<double>(std::numeric_limits<int>::min())
			|| value > static_cast<double>(std::numeric_limits<int>::max()))
			std::cout << "int: impossible" << std::endl;
		else
			std::cout << "int: " << static_cast<int>(value) << std::endl;
	}

	void printFloat(double value)
	{
		float result;

		if (value > static_cast<double>(std::numeric_limits<float>::max())
			|| value < -static_cast<double>(std::numeric_limits<float>::max()))
		{
			std::cout << "float: impossible" << std::endl;
			return;
		}
		result = static_cast<float>(value);
		std::cout << "float: ";
		if (isIntegral(static_cast<double>(result)))
			std::cout << std::fixed << std::setprecision(1);
		std::cout << result << "f" << std::endl;
		resetFormat();
	}

	void printDouble(double value)
	{
		std::cout << "double: ";
		if (isIntegral(value))
			std::cout << std::fixed << std::setprecision(1);
		std::cout << value << std::endl;
		resetFormat();
	}

	void printAll(double value)
	{
		printChar(value);
		printInt(value);
		printFloat(value);
		printDouble(value);
	}
}

void ScalarConverter::convert(const std::string &literal)
{
	double value;

	if (isSpecial(literal))
	{
		printSpecial(literal);
		return;
	}
	if (isCharLiteral(literal))
	{
		printAll(static_cast<double>(literal[1]));
		return;
	}
	if (isSingleChar(literal))
	{
		printAll(static_cast<double>(literal[0]));
		return;
	}
	if (!parseDouble(literal, value))
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}
	printAll(value);
}
