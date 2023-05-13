#include "PmergeMe.hpp"

#include <deque>
int main()
{
	PmergeMe	b;
	IntList	v;
	v.push_back(9);
	v.push_back(8);
	v.push_back(7);
	v.push_back(6);
	v.push_back(5);
	v.push_back(4);
	v.push_back(3);
	v.push_back(23);
	v.push_back(245);
	v.push_back(453);
	v.push_back(21);
	v.push_back(53);
	v.push_back(12);
	v.push_back(214);
	v.push_back(223);
	v.push_back(2145);
	v.push_back(214);
	v.push_back(54);
	v.push_back(654);
	printRange(v.begin(), v.end());

	b.mergeInsertionSort(v.begin(), v.end());
	
	printRange(v.begin(), v.end());
	std::cout << std::endl;
///////////////////////////////////////////////////////////////////////////////////////////
	std::deque<int>	g;
	g.push_back(9);
	g.push_back(8);
	g.push_back(7);
	g.push_back(6);
	g.push_back(5);
	g.push_back(4);
	g.push_back(3);
	g.push_back(23);
	g.push_back(245);
	g.push_back(453);
	g.push_back(21);
	g.push_back(53);
	g.push_back(12);
	g.push_back(214);
	g.push_back(223);
	g.push_back(2145);
	g.push_back(214);
	g.push_back(54);
	g.push_back(654);
	printRange(g.begin(), g.end());

	b.mergeInsertionSort(g.begin(), g.end());
	
	printRange(g.begin(), g.end());

}