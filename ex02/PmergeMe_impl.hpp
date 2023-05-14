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

template<typename	RandIt>
void	PmergeMe::mergeRange(RandIt start, RandIt mid, RandIt end, std::bidirectional_iterator_tag t)
{
	// std::cout << __PRETTY_FUNCTION__ << std::endl;
	(void)t;//Needs only to determine the code
    typedef typename std::iterator_traits<RandIt>::value_type 	value_type;
	typedef	std::list<value_type>								List;
	typedef	 typename List::iterator							AsocIt;

	List	leftSub(std::distance(start, mid));
	std::copy(start, mid, leftSub.begin());

	List	rightSub(std::distance(mid, end));
	std::copy(mid, end, rightSub.begin());
	
	AsocIt	leftIt	= leftSub.begin();
	AsocIt	rightIt	= rightSub.begin();
	RandIt	curIt	= start;

	mainMerging(leftIt, leftSub.end(), rightIt, rightSub.end(), curIt);
}

template<typename	RandIt>
void	PmergeMe::mergeRange(RandIt start, RandIt mid, RandIt end, std::random_access_iterator_tag t)
{
	// std::cout << __PRETTY_FUNCTION__ << std::endl;
	(void)t;//Needs only to determine the function
    typedef typename std::iterator_traits<RandIt>::value_type 	value_type;
	typedef	std::vector<value_type>								Vector;
	typedef	typename Vector::iterator							AsocIt;

	Vector	leftSub(std::distance(start, mid));
	std::copy(start, mid, leftSub.begin());

	Vector	rightSub(std::distance(mid, end));
	std::copy(mid, end, rightSub.begin());
	
	AsocIt	leftIt	= leftSub.begin();
	AsocIt	rightIt	= rightSub.begin();
	RandIt	curIt	= start;

	mainMerging(leftIt, leftSub.end(), rightIt, rightSub.end(), curIt);
}


template<typename AsocIt, typename Iterator>
void	PmergeMe::mainMerging(AsocIt	leftIt, AsocIt	leftEnd, AsocIt	rightIt, AsocIt	rightEnd, Iterator	currentIt)
{
	while (leftIt != leftEnd && rightIt != rightEnd) 
	{
        if (*leftIt <= *rightIt) 
		{
            *currentIt = *leftIt;
			std::advance(leftIt, 1);
        } 
		else 
		{
            *currentIt = *rightIt;
			std::advance(rightIt, 1);
        }
		std::advance(currentIt, 1);
    }
    std::copy(leftIt, leftEnd, currentIt);
    std::copy(rightIt, rightEnd, currentIt);
}

template<typename	ForwardIt>
void	PmergeMe::mergeInsertionSort(ForwardIt	start, ForwardIt end)
{
	typename std::iterator_traits<ForwardIt>::iterator_category type;
    if (std::distance(start, end) < 16) 
	{
		insertionSort(start, end);
        return;
    }
	// std::cout << __PRETTY_FUNCTION__ << std::endl;
	ForwardIt	mid = next(start, std::distance(start, end) / 2);
	mergeInsertionSort(start, mid);
	mergeInsertionSort(mid, end);
	mergeRange(start, mid, end, type);
}



# endif	//PMERGE_ME_IMPL_HPP

