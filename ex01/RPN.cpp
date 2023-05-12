#include "RPN.hpp"

RPN::RPN()
	:	result(0),
		expr("")
{}

RPN::RPN(const std::string& rpnExpr)
	:	result(0),
		expr(rpnExpr)
{}


RPN::RPN(const RPN&	rhs)
	:	operands(rhs.operands),
		result(rhs.result),
		expr(rhs.expr)
{}

RPN& RPN::operator=(const RPN& rhs)
{
	if (this != &rhs)
	{
		operands = rhs.operands;
		result = rhs.result;
	}
	return (*this);
}

RPN::~RPN()
{}

bool RPN::isOperator(const char c) const
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

void	RPN::doOperation(OperandStack& operands, Operator op) const
{
	double	operand1, operand2;
	operand2 = operands.top();
	operands.pop();
	operand1 = operands.top();
	operands.pop();
	switch (op)
	{
		case '+':
			operands.push(operand1 + operand2);
			break;
		case '-':
			operands.push(operand1 - operand2);
			break;
		case '*':
			operands.push(operand1 * operand2);
			break;
		case '/':
			if (operand2 == 0)
				throw (std::runtime_error("Division by zero exception"));
			operands.push(operand1 / operand2);
			break;
	}
}

void	RPN::calculate()
{
	try
	{
		result = evaluatePrefix();
		printResult();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void	RPN::printResult() const
{
	std::cout << "Result = " << result << std::endl;
}



double	RPN::evaluatePrefix()
{
	if (expr.length() == 0)
		throw (std::runtime_error("Empty expression exception"));
	for (ForwardIt it = expr.begin(); it != expr.end(); std::advance(it, 1))
	{	
		if (std::isspace(*it))
			continue;	
		else if (std::isdigit(*it))
		{
			operands.push(*it - '0');
		}
		else if (isOperator(*it))
		{
			if (operands.size() < 2)
				throw (std::runtime_error("Wrong Operands count exception"));
			doOperation(operands, *it);
		}
		else
		{
			throw (std::runtime_error("Invalid character exception"));
		}
	}
	if (operands.size() != 1)
		throw (std::runtime_error("Invalid expresion exception"));
	return (operands.top());
}
