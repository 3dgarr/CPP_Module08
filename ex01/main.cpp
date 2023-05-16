#include "RPN.hpp"


int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Correct interface: ./RPN \"prefixExpression\"" << std::endl;
		return (1);
	}
	RPN	calculator(argv[1]);
	calculator.calculate();

}