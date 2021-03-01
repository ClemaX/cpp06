#include <serialize.hpp>

int	main()
{
	srand(time(NULL));

	void*	serialized = serialize();

	Data*	data = deserialize(serialized);

	std::cout << "Deserialized " << *data << std::endl;

	delete[] reinterpret_cast<unsigned char*>(serialized);
	delete data;

	//system("../leaks.sh serialize");

	return 0;
}
