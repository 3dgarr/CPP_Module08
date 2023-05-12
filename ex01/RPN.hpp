# ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>

class RPN
{
	public:
		void	calculate();
		void	printResult() const;

	public:
		RPN();
		RPN(const std::string&);
		RPN(const RPN&);
		RPN& operator=(const RPN&);
		~RPN();
	
	public:
		typedef	std::stack<double>				OperandStack;
		typedef	OperandStack::value_type		Value_type;	
		typedef	char							Operator;
		typedef	std::string::reverse_iterator	RForwardIt;
		typedef	std::string::iterator			ForwardIt;
	
	private:
		void	doOperation(OperandStack& operands, Operator op) const;
		double	evaluatePrefix();
		bool	isOperator(const char c) const;

	private:
		OperandStack	operands;
		Value_type		result;
		std::string		expr;
};

# endif	// RPN_HPP