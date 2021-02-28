#include <strtold.hpp>

long double	strtold(std::string const& str,
	std::string::const_iterator& endIt)
{
	long double	value = 0;

	endIt = str.end();
	if (str == "-inf" || str == "-inff")
		value = -std::numeric_limits<long double>::infinity();
	else if (str == "+inf" || str == "+inff")
		value = std::numeric_limits<long double>::infinity();
	else if (str == "nan" || str == "nanf")
		value = std::numeric_limits<long double>::quiet_NaN();
	else
	{
		std::string::const_iterator			it = str.begin();
		std::string::const_iterator const	end = str.end();
		char								sign = 1;

		while (it != end)
		{
			if (*it == '-')
				sign *= -1;
			else if (*it != '+')
				break;
			it++;
		}
		while (it != end && std::isdigit(*it))
			value = value * 10 + *it++ - '0';
		if (*it == '.')
		{
			it++;

			long double	decDivisor = 10;

			while (it != end && std::isdigit(*it))
			{
				value += ((*it++ - '0') / decDivisor);
				decDivisor *= 10;
			}
		}
		if (*it == 'f')
		{
			it++;
			value = static_cast<long double>(static_cast<float>(value));
		}
		endIt = it;
		value *= sign;
	}
	return value;
}
