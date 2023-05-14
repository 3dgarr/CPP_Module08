#include "PmergeMe.hpp"


PmergeMe::PmergeMe()
	:	numbers_line(""),
		string_numbers(0)
{}

PmergeMe::~PmergeMe()
{}

PmergeMe::PmergeMe(const PmergeMe& rhs)
	:	numbers_line(rhs.numbers_line),
		string_numbers(rhs.string_numbers)
{}

PmergeMe& PmergeMe::operator=(const PmergeMe& rhs)
{
	if (this != &rhs)
	{
		numbers_line = rhs.numbers_line;
		string_numbers = rhs.string_numbers;
	}
	return (*this);
}

void PmergeMe::get_sequance_as_str(int argc, char** argv)
{
	int i = 0;
	while (++i < argc)
	{
		numbers_line += std::string(argv[i]) + " ";
	}
}

void PmergeMe::validate_sequance()
{
	std::stringstream	ss(numbers_line);
	std::string			line;
	while (std::getline(ss, line, ' '))
	{
		if (line.length() == 0)
			continue;
		if (isNotNumber(line))
			throw	std::runtime_error("Invalid element in sequance");
		std::stringstream	ss(line);
		long n;
		ss >> n;
		if (n > 2147483647)
			throw	std::runtime_error("Out of range element in sequance");
		string_numbers.push_back(line);		
	}
}

void	PmergeMe::sort_vector()
{
	std::vector<int>	vector(string_numbers.size());
	struct timeval start_time, end_time;

	gettimeofday(&start_time, NULL);
	std::transform(string_numbers.begin(), string_numbers.end(), vector.begin(), String2Number());
	mergeInsertionSort(vector.begin(), vector.end());
	gettimeofday(&end_time, NULL);

	std::cout << "Before:\t" << std::flush;
	printRange(string_numbers.begin(), string_numbers.end());
	std::cout << "After:\t" << std::flush;
	printRange(vector.begin(), vector.end());
	std::cout << "Time to process a range of " << vector.size() << " elements with std::vector : " << get_time_diff(start_time, end_time)<<" us\n" << std::endl;
}

void	PmergeMe::sort_list()
{
	std::list<int>	list(string_numbers.size());
	struct timeval	start_time, end_time;

	gettimeofday(&start_time, NULL);
	std::transform(string_numbers.begin(), string_numbers.end(), list.begin(), String2Number());
	mergeInsertionSort(list.begin(), list.end());
	gettimeofday(&end_time, NULL);

	std::cout << "Before:\t" << std::flush;
	printRange(string_numbers.begin(), string_numbers.end());
	std::cout << "After:\t" << std::flush;
	printRange(list.begin(), list.end());
	std::cout << "Time to process a range of " << list.size() << " elements with std::list :\t" << get_time_diff(start_time, end_time)<<" us\n" << std::endl;
}

void	PmergeMe::sort_deque()
{
	std::deque<int>	deque(string_numbers.size());
	struct timeval start_time, end_time;

	gettimeofday(&start_time, NULL);
	std::transform(string_numbers.begin(), string_numbers.end(), deque.begin(), String2Number());
	mergeInsertionSort(deque.begin(), deque.end());
	gettimeofday(&end_time, NULL);

	std::cout << "Before:\t" << std::flush;
	printRange(string_numbers.begin(), string_numbers.end());
	std::cout << "After:\t" << std::flush;
	printRange(deque.begin(), deque.end());
	std::cout << "Time to process a range of " << deque.size() << " elements with std::deque :\t" << get_time_diff(start_time, end_time)<<" us\n" << std::endl;
}

void	PmergeMe::run(int argc, char** argv)
{
	if (argc == 1)
	{
		(void)argv;
		std::cout << "Correct interface: ./pmergeMe <sequance of numbers>" << std::endl;
		return ;
	}
	try
	{
		get_sequance_as_str(argc, argv);
		validate_sequance();
		sort_vector();
		sort_list();
		sort_deque();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}	
}

bool	PmergeMe::isNotNumber(std::string	line)
{
	std::string::iterator	start = line.begin();
	if (line[0] == '+' || line[0] == '-')
		++start;
	std::string::iterator it = std::find_if(start, line.end(), FindNonDigit());
	if (it == line.end())
		return	(false);
	return	(true);	
}

double	PmergeMe::get_time_diff(struct timeval &t1, struct timeval &t2)
{
	return ( (t2.tv_sec - t1.tv_sec) * 1000 + (t2.tv_usec - t1.tv_usec) / 1000.0);
}