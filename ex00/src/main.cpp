#include <strtold.hpp>
#include <convert.hpp>

static void	convertString(std::string const& str)
{
	const char	c = *str.begin();
	long double	value;

	if (str.length() == 1 && std::isprint(c) && !std::isdigit(c))
		value = static_cast<long double>(c);
	else
	{
		std::string::const_iterator	endIt;

		value = strtold(str, endIt);

		if (endIt != str.end())
		{
			std::cout << "invalid input: " << str << std::endl;
			return;
		}
	}
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
}

int			main(int ac, const char** av)
{
	for (int i = 1; i < ac; i++)
		convertString(av[i]);
	return 0;
}

