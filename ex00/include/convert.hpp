#pragma once

#include <iostream>
#include <string>

#include <limits>
#include <cmath>

template<typename To, typename From>
bool	convert(From value)
{
	To cast;

	if (value == 0
	|| (value >= static_cast<From>(std::numeric_limits<To>::min())
	&& value <= static_cast<From>(std::numeric_limits<To>::max()))
	|| (std::isinf(value) && std::numeric_limits<To>::has_infinity))
	{
		cast = static_cast<To>(value);
		std::cout << cast;
		return true;
	}
	std::cout << "impossible";
	return false;
}

template<typename From>
bool	convertChar(From value)
{
	if (value >= std::numeric_limits<char>::min()
	&& value <= std::numeric_limits<char>::max())
	{
		char c = static_cast<char>(value);

		if (std::isprint(c))
		{
			std::cout << c;
			return true;
		}
		std::cout << "Non displayable";
	}
	else
		std::cout << "impossible";
	return false;
}

