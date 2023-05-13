# ifndef PMERGE_ME_IMPL_HPP
# define PMERGE_ME_IMPL_HPP

#include "PmergeMe.hpp"

template<typename T>
T next(T it, typename std::iterator_traits<T>::difference_type n = 1) 
{
    std::advance(it, n);
    return it;
}

template<typename T>
T prev(T it, typename std::iterator_traits<T>::difference_type n = -1) 
{
    std::advance(it, n);
    return it;
}

template <typename It>
void printRange(It startIt, It endIt) 
{
	if (std::distance(startIt, endIt) > 7)
	{
    	std::copy(startIt, next(startIt, 7), std::ostream_iterator<typename It::value_type>(std::cout, "\t"));
		std::cout << "[...]\t" ;
    	std::copy(prev(endIt, -2), endIt, std::ostream_iterator<typename It::value_type>(std::cout, "\t"));
		std::cout << std::endl;

	}
	else
	{
		std::copy(startIt, endIt, std::ostream_iterator<typename It::value_type>(std::cout, "\t"));
		std::cout << std::endl;
	}
}


template <typename ForwardIt>
void PmergeMe::insertionSort(ForwardIt start, ForwardIt end) 
{
	// std::cout << __PRETTY_FUNCTION__ << std::endl;
    typedef typename std::iterator_traits<ForwardIt>::value_type  value_type;
    for (ForwardIt it = start; it != end; std::advance(it, 1)) 
	{
        value_type key		=	*it;
        ForwardIt sorted_it	=	it;
        while (sorted_it != start && key < *prev(sorted_it)) 
		{
            *sorted_it = *(prev(sorted_it));
            std::advance(sorted_it, -1);
        }
        *sorted_it = key;
    }
}

template<typename	ForwardIt>
void	PmergeMe::mergeRange(ForwardIt& start, ForwardIt& mid, ForwardIt& end)
{
    typedef typename std::iterator_traits<ForwardIt>::value_type 	value_type;
	typedef	std::vector<value_type>									Vector;
	typedef	typename Vector::iterator								Iterator;

	Vector	leftSub(std::distance(start, mid));
	std::copy(start, mid, leftSub.begin());

	Vector	rightSub(std::distance(mid, end));
	std::copy(mid, end, rightSub.begin());
	
	Iterator	leftIt = leftSub.begin();
	Iterator	rightIt = rightSub.begin();
	ForwardIt	curIt = start;

    while (leftIt != leftSub.end() && rightIt != rightSub.end()) 
	{
        if (*leftIt <= *rightIt) 
		{
            *curIt = *leftIt;
			std::advance(leftIt, 1);
        } 
		else 
		{
            *curIt = *rightIt;
			std::advance(rightIt, 1);
        }
		std::advance(curIt, 1);
    }
    std::copy(leftIt, leftSub.end(), curIt);
    std::copy(rightIt, rightSub.end(), curIt);

}

template<typename	ForwardIt>
void	PmergeMe::mergeInsertionSort(ForwardIt	start, ForwardIt end)
{
    if (std::distance(start, end) < 16) 
	{
		insertionSort(start, end);
        return;
    }
	// std::cout << __PRETTY_FUNCTION__ << std::endl;
	ForwardIt	mid = next(start, std::distance(start, end) / 2);
	mergeInsertionSort(start, mid);
	mergeInsertionSort(mid, end);
	mergeRange(start, mid, end);
}



# endif	//PMERGE_ME_IMPL_HPP