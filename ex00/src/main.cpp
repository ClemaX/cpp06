#include <strtold.hpp>
#include <convert.hpp>
#include <iomanip>

static void	convertString(std::string const& str)
{
	std::streamsize const	precision = std::cout.precision();
	char const				c = *str.begin();
	long double				value;
	bool					isRound;

	if (str.length() == 1 && std::isprint(c) && !std::isdigit(c))
	{
		value = static_cast<long double>(c);
		isRound = true;
	}
	else
	{
		std::string::const_iterator	endIt;

		value = strtold(str, endIt);
		if (endIt != str.end())
		{
			std::cout << "invalid input: " << str << std::endl;
			return;
		}
		isRound = std::fmod(value, 1.0) == 0.0;
	}

	if (isRound)
		std::cout << std::fixed << std::setprecision(1);

	std::cout << "char: ";
	convertChar(value);

	std::cout << std::endl << "int: ";
	convert<int>(value);

	std::cout << std::endl << "float: ";
	if (convert<float>(value))
		std::cout << 'f';

	std::cout << std::endl << "double: ";
	convert<double>(value);
	std::cout << std::endl;

	if (isRound)
	{
		std::cout << std::setprecision(precision);
		std::cout.unsetf(std::ios_base::floatfield);
	}
}

int			main(int ac, const char** av)
{
	for (int i = 1; i < ac; i++)
		convertString(av[i]);
	return 0;
}

