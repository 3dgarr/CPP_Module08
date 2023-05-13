# ifndef PMERGE_ME_HPP
# define PMERGE_ME_HPP

# include <algorithm>
# include <deque>
# include <iterator>
# include <iostream>
# include <list>
# include <sstream>
# include <vector>

# include <ctime>
# include <sys/time.h>
# include <cstdlib>

typedef	std::vector<int>	IntVector;
typedef	std::list<int>		IntList;

struct FindNonDigit
{
	bool operator()(char c){ return !::isdigit(c); }
};

struct String2Number
{
	int	operator()(const std::string& str)
	{
		std::stringstream	ss(str);
		int number;
		ss >> number ;
		return (number); 
	}
};

template <typename It>
void printRange(It startIt, It endIt);

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(const PmergeMe&);
		PmergeMe& operator=(const PmergeMe&);
		~PmergeMe();
		void	run(int, char**);

	private:
		template<typename	ForwardIt>
		void	mergeInsertionSort(ForwardIt	start, ForwardIt end);
		void	get_sequance_as_str(int, char**);
		void	validate_sequance();
		bool	isNotNumber(std::string	line);
		void	sort_vector();
		void	sort_list();
		void	sort_deque();

		double	get_time_diff(struct timeval &t1, struct timeval &t2);


		template<typename	ForwardIt>
		void	insertionSort(ForwardIt	start, ForwardIt end);

		template<typename	ForwardIt>
		void	mergeRange(ForwardIt& start, ForwardIt& mid, ForwardIt& end);


	private:
		std::string					numbers_line;
		std::vector<std::string>	string_numbers;
};




#include "PmergeMe_impl.hpp"

# endif //PMERGE_ME_HPP