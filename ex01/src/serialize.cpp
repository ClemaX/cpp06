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
	void				*raw = ::operator new(2 * 8 + sizeof(int));

	std::memcpy(raw, data.s1.c_str(), 8);
	std::memcpy((unsigned char*)raw + 8, &data.n, sizeof(int));
	std::memcpy((unsigned char*)raw + 8 + sizeof(int), data.s2.c_str(), 8);

	std::cout << std::setw(13) << std::left << "Serialized " << data
		<< std::endl;

	return raw;
}

Data*	deserialize(void *raw)
{
	Data*		data = new Data;
	char		s[9];

	s[8] = '\0';
	std::memcpy(s, raw, 8);
	data->s1 = s;
	std::memcpy(&data->n, (unsigned char*)raw + 8, sizeof(int));
	std::memcpy(s, (unsigned char*)raw + 8 + sizeof(int), 8);
	data->s2 = s;

	return data;
}
