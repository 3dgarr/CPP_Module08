# ifndef PMERGE_ME_HPP
# define PMERGE_ME_HPP

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <list>

typedef	std::vector<int>	IntVector;
typedef	std::list<int>		IntList;

template <typename It>
void printRange(It startIt, It endIt);

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(const PmergeMe&);
		PmergeMe& operator=(const PmergeMe&);
		~PmergeMe();
		template<typename	ForwardIt>
		void	mergeInsertionSort(ForwardIt	start, ForwardIt end);

	private:
		template<typename	ForwardIt>
		void	insertionSort(ForwardIt	start, ForwardIt end);

		template<typename	ForwardIt>
		void	mergeRange(ForwardIt& start, ForwardIt& mid, ForwardIt& end);
};




#include "PmergeMe_impl.hpp"

# endif //PMERGE_ME_HPP