#include <serialize.hpp>

char	randomChar()
{
	char c;

	while (!std::isalnum(c = rand() % 128));

	return c;
}

Data::Data()
{
	s1.clear();
	s2.clear();

	for (int i = 0; i < 8; i++)
	{
		s1 += randomChar();
		s2 += randomChar();
	}
	n = rand();
}

Data::Data(std::string const& s1, int n, std::string const& s2)
	:	s1(s1),
		n(n),
		s2(s2)
{
}

std::ostream&	operator<<(std::ostream& os, Data const& data)
{
	os << "Data: s1: " << data.s1 << ", n: " << data.n << ", s2: " << data.s2;

	return os;
}

void*	serialize()
{
	Data const			data;
	unsigned char		*raw = new unsigned char[2 * 8 + sizeof(int)];

	*reinterpret_cast<u_int64_t*>(raw)
		= *reinterpret_cast<u_int64_t const*>(data.s1.c_str());

	*reinterpret_cast<int*>(raw + 8) = data.n;

	*reinterpret_cast<u_int64_t*>(raw + 8 + sizeof(int))
		= *reinterpret_cast<u_int64_t const*>(data.s2.c_str());

	std::cout << std::setw(13) << std::left << "Serialized " << data
		<< std::endl;

	return raw;
}

Data*	deserialize(void *raw)
{
	unsigned char const*	serialized =
		reinterpret_cast<unsigned char const*>(raw);
	Data*					data = new Data;
	char					s[9];

	s[8] = '\0';

	*reinterpret_cast<u_int64_t*>(s) =
		*reinterpret_cast<u_int64_t const*>(serialized);
	data->s1 = s;

	data->n = *reinterpret_cast<int const*>(serialized + 8);

	*reinterpret_cast<u_int64_t*>(s) =
		*reinterpret_cast<u_int64_t const*>(serialized + 8 + sizeof(int));
	data->s2 = s;

	return data;
}
