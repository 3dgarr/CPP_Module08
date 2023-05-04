#include "BitcoinExchange.hpp"

std::string trim(std::string to_trim)
{
	std::string ret;

	for (size_t i = 0; i < to_trim.size(); ++i)
	{
		if (!(::isspace(to_trim[i])))
			ret.push_back(to_trim[i]);
	}
	std::cout << ret << "*\n";
	return ret;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "The right way is -> ./btc <inputFileName>" << std::endl;
		return 1;
	}

	try
	{
		BitcoinExchange	b("hi");
		b.run(argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
		
	std::string a =      "      ba     rev        ";
	trim(a);

	// std::cout << "*" << trim(a) << "*\n";


	return 0;
}