#include <serialize.hpp>

int	main()
{
	srand(time(NULL));

	void*	serialized = serialize();

	Data*	data = deserialize(serialized);

	std::cout << "Deserialized " << *data << std::endl;

	return 0;
}
