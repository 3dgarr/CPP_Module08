#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange(const std::string&	fn)
{
	fileName = fn;
	fillDatabase();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& rhs)
{
	data__ = rhs.data__;
	fileName = rhs.fileName;	
}

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange& rhs)
{
	if (this != &rhs)
	{
		data__ = rhs.data__;
		fileName = rhs.fileName;	
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{}


void	checkPipeExistence(std::string line)
{
	std::string	ErrMsg = "Invalid Pipe at: " + line;
	if (line.find('|') != line.rfind('|'))
		throw (std::runtime_error(ErrMsg.c_str()));
	
	size_t	idx =line.find('|');
	if (idx == std::string::npos || !std::isspace(line[idx - 1]) || !std::isspace(line[idx + 1]))
		throw (std::runtime_error(ErrMsg.c_str()));	
}

void BitcoinExchange::validate_value(std::string& value)
{
	trimSpacesFromStartEnd(value);
	std::string cp(value);
	std::string	errMsg = "Invalid value : " + cp;
	if (cp.find('.') == cp.rfind('.') && cp.find('.') != std::string::npos)
	{
		cp.erase(cp.find('.'), 1);
	}
	if (isNotNumber(cp) || cp.length() == 0)
		throw std::runtime_error(errMsg);
	double	v;
	std::stringstream	ss(cp);
	ss >> v;
	if (v < 0)
	{	
		throw (std::runtime_error("Error: not a positive number."));
	}
	if (v > 1000)
	{	
		throw (std::runtime_error("Error: too large number."));
	}
}

void	BitcoinExchange::printValueFromDb(std::string&	date, std::string& v)
{
	std::stringstream	ss(v);
	double				value;
	ss >> value;
	Database::iterator	it = data__.find(date);
	if (it == data__.end())
	{
		it = data__.lower_bound(date);
		if (it != data__.begin())
			std::advance(it, -1);
		else
			throw (std::runtime_error("Not found in database"));
	}
	std::cout<< date << " => " << value  << " = " << value * it->second<< std::endl;
}


void	BitcoinExchange::run(const std::string&	input)
{
	std::ifstream	inFile(input.c_str());
	std::string		line;
	if (!inFile.is_open())
		throw	std::runtime_error("Can not open input file");
	std::getline(inFile, line);
	if (isNotValidHeader(line))
		throw	std::runtime_error("Invalid column names");
	while (std::getline(inFile, line))
	{
		try
		{
			checkPipeExistence(line);
			std::stringstream	ss(line);
			std::string			date ;
			std::string			value ;

			std::getline(ss, date, '|');
			std::getline(ss, value, '|');
			validateDate(date);
			validate_value(value);
			printValueFromDb(date, value);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
}

bool	BitcoinExchange::isNotNumber(std::string	line)
{
	std::string::iterator	start = line.begin();
	if (line[0] == '-' || line[0] == '+')
		++start;
	std::string::iterator it = std::find_if(start, line.end(), FindNonDigit());
	if (it == line.end())
		return	(false);
	return	(true);	
}


void	BitcoinExchange::getIntRepresentations(DataRep& year, DataRep& month, DataRep& day)
{	
	if (isNotNumber(year.strRepresentation) || isNotNumber(month.strRepresentation) || isNotNumber(day.strRepresentation))
	{
		std::string	errMsg = "Invalid year/month/day : " + year.strRepresentation + "-" + month.strRepresentation + "-" + day.strRepresentation;
		throw	std::runtime_error(errMsg.c_str());
	}
	std::stringstream	ys(year.strRepresentation);
	std::stringstream	ms(month.strRepresentation);
	std::stringstream	ds(day.strRepresentation);
	ys >> year.intRepresentation;
	ms >> month.intRepresentation;
	ds >> day.intRepresentation;
}

bool IsLeapYear(int year)
{
	return ((year % 400 == 0 || ( year % 4 == 0 && year % 100 != 0 )) ? true : false);
}

void	BitcoinExchange::validate_ymd(DataRep& y, DataRep& m, DataRep& d)
{
	int year = y.intRepresentation;
	int month = m.intRepresentation;
	int day = d.intRepresentation;
	std::string	errMsg = "Invalid year/month/day : " + y.strRepresentation + "-" + m.strRepresentation + "-" + d.strRepresentation;
	
	if (year < 2009  || month < 1 || month > 12 || day < 1 || day > 31)
		throw std::runtime_error(errMsg);

	MONTH30 months[] = {APR, JUN, SEP, NOV};
	for (size_t i = 0; i < 4; i++)
	{
		if (months[i] == month && day == 31)
			throw std::runtime_error(errMsg);
	}
	if (month == FEB && day > (28 + IsLeapYear(year)))
		throw std::runtime_error(errMsg);
}

void	BitcoinExchange::validateDate(std::string&	date)
{
	trimSpacesFromStartEnd(date);
	std::string	errorMsg = date + ": Invalid date";
	DataRep		year;
	DataRep		month;
	DataRep		day;
	std::stringstream	ss(date);
	if (date[4] != '-' || date[7] != '-')
		throw	std::runtime_error(errorMsg.c_str());

	std::getline(ss, year.strRepresentation, '-');
	std::getline(ss, month.strRepresentation, '-');
	std::getline(ss, day.strRepresentation, '-');
	
	trimSpacesFromStartEnd(year.strRepresentation);
	trimSpacesFromStartEnd(month.strRepresentation);
	trimSpacesFromStartEnd(day.strRepresentation);
	getIntRepresentations(year, month, day);
	validate_ymd(year, month, day);
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

