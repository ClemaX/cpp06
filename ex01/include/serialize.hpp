#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cstring>

struct Data
{
	std::string s1;
	int			n;
	std::string	s2;

	Data();
	Data(std::string const& s1, int n, std::string const& s2);
};

std::ostream&	operator<<(std::ostream &os, Data const& data);

void*	serialize();

Data*	deserialize(void* raw);
