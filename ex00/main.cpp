#include "BitcoinExchange.hpp"


int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "The right way is -> ./btc <inputFileName>" << std::endl;
		return 1;
	}

	try
	{
		BitcoinExchange	b(argv[1]);
		b.run(argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
		

	// std::cout << "*" << trim(a) << "*\n";


	return 0;
}