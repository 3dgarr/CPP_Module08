#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange(const std::string&	fn)
{
	fileName = fn;
	fillDatabase();
}

void	BitcoinExchange::run(const std::string&	input)
{
	std::ifstream	inFile(input);
	std::string		line;
	if (!inFile.is_open())
		throw	std::runtime_error("Can not open input file\n");
	std::getline(inFile, line);
	if (isNotValidHeader(line))
		throw	std::runtime_error("Invalid column names\n");
	while (std::getline(inFile, line))
	{
		try
		{
			std::stringstream	ss(line);
			std::string			date ;
			std::string			value ;

			std::getline(ss, date, '|');
			std::getline(ss, value, '|');
			validateDate(date);
			// // if (0)
			// // {

			// // }
			// // else
			// // {
			// 	std::string	errorMsg = line + ": Invalid date\n";
			// 	throw	std::runtime_error(errorMsg.c_str());
			// }
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		
	}
	
}

void	BitcoinExchange::validateDate(std::string	date)
{
	std::string	errorMsg = date + ": Invalid date\n";
	std::string		year;
	std::string		month;
	std::string		day;
	std::ifstream	ss(date);
	if (date[4] != '-' || date[7] != '-')
		throw	std::runtime_error(errorMsg.c_str());
	std::getline(ss, year, '-');
	std::getline(ss, month, '-');
	std::getline(ss, day, '-');
	trimSpacesFromStartEnd(year);
	trimSpacesFromStartEnd(month);
	trimSpacesFromStartEnd(day);
		///TODO:validation of year, month, day
	
	
}


bool	BitcoinExchange::isNotValidHeader(std::string& line)
{
	std::stringstream	ss(line);
	std::string			date ;
	std::string			value ;

	std::getline(ss, date, '|');
	std::getline(ss, value, '|');
	trimSpacesFromStartEnd(date);
	trimSpacesFromStartEnd(value);
	return (!(date == "date" && value == "value"));
}

void	BitcoinExchange::fillDatabase()
{
	std::string		line;
	std::ifstream	inputFile("data.csv");
	
	if (!inputFile.is_open())
		throw	std::runtime_error("Can not open file");
	std::getline(inputFile, line);

	while (std::getline(inputFile, line))
	{
		std::stringstream	ss(line);
		std::string			key ;
		std::string			value ;

		std::getline(ss, key, ',');
		std::getline(ss, value, ',');
		data__[key] = std::strtod(value.c_str(), NULL);
	}
	if (data__.size() == 0)
		throw	std::runtime_error("Empty file");
	// printData();
}

void	BitcoinExchange::openFile()
{
	std::ifstream	file(fileName);
	if (file.is_open())
	{
		try
		{
			start_parsing(file);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		
	}
}
void	BitcoinExchange::printData() 
{
	std::cout.precision(2);
	for(std::map<std::string, double>::iterator	it = data__.begin(); it != data__.end(); it++)
	{
		std::cout << it->first << " " << std::fixed << it->second  << std::endl;
	}
}

void	BitcoinExchange::trimSpacesFromStartEnd(std::string& line)
{
	std::string::iterator start	= std::find_if(line.begin(), line.end(), FindNotSpace());
	std::string::iterator end	= std::find_if(start, line.end(), FindSpace());
	std::string(start, end).swap(line);
}


void	BitcoinExchange::start_parsing(const std::ifstream& file)
{
	(void) file;
}
