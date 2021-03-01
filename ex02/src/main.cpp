#include <A.hpp>
#include <B.hpp>
#include <C.hpp>

#include <iostream>
#include <iomanip>

#include <cstdlib>

Base*	generate(void)
{
	static const unsigned	count = 3;
	static const char		names[count] = {'A', 'B', 'C'};

	int const	type = rand() % count;
	Base*		object;

	switch (type)
	{
		case 0:		object = new A;	break;
		case 1:		object = new B;	break;
		case 2:		object = new C;	break;
		default:	object = NULL;	break;
	}

	std::cout << "Generated " << names[type] << "!" << std::endl;

	return object;
}

void	identify_from_pointer(Base* ptr)
{
	std::string	type;

	if (dynamic_cast<A*>(ptr))
		type = "A";
	else if (dynamic_cast<B*>(ptr))
		type = "B";
	else if (dynamic_cast<C*>(ptr))
		type = "C";
	else
		type = "unknown";

	std::cout << "Type is " << type << '!' << std::endl;
}

void	identify_from_reference(Base& ref)
{
	std::string	type;

	try { static_cast<void>(dynamic_cast<A&>(ref)); type = "A";}
	catch(std::exception const&)
	{
		try { static_cast<void>(dynamic_cast<B&>(ref)); type = "B";}
		catch(std::exception const&)
		{
			try { static_cast<void>(dynamic_cast<C&>(ref)); type = "C";}
			catch(std::exception const&) { type = "unknown"; }
		}
	}

	std::cout << "Type is " << type << '!' << std::endl;
}

int	main()
{
	static const unsigned	iterations = 3;
	unsigned				i = 0;
	Base*					object;

	srand(time(NULL));

	while (i < iterations)
	{
		object = generate();

		std::cout << std::setw(16) << std::left << "From pointer: ";
		identify_from_pointer(object);

		std::cout << "From reference: ";
		identify_from_reference(*object);

		if (++i != iterations)
			std::cout << std::endl;
	}

	return 0;
}
