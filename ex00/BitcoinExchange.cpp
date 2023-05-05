#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange(const std::string&	fn)
{
	fileName = fn;
	fillDatabase();
}

void	checkPipeExistence(std::string line)
{
	std::string::iterator it1 = std::find_if(line.begin(), line.end(), FirstPipe());
	std::string::iterator it2 = std::find_if(++it1, line.end(), FirstPipe());
	if (it1 == line.end() || it2 != line.end())
	{
		std::string	ErrMsg = "Invalid Pipe at: " + line;
		throw (std::runtime_error(ErrMsg.c_str()));
	}
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
			checkPipeExistence(line);
			std::stringstream	ss(line);
			std::string			date ;
			std::string			value ;

			std::getline(ss, date, '|');
			std::getline(ss, value, '|');
			validateDate(date);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		
	}
	
}

bool	BitcoinExchange::isNotNumber(std::string	line)
{
	std::string::iterator it = std::find_if(line.begin(), line.end(), FindNonDigit());
	if (it == line.end())
		return	(false);
	return	(true);
		
}


void	BitcoinExchange::getIntRepresentations(DataRep& year, DataRep& month, DataRep& day)
{
	
	// std::stringstream	ss(year.strRepresentation);
	// ss >> year.intRepresentation;
	// std::cout << year.strRepresentation << " " << month.strRepresentation << day.strRepresentation << std::endl;
	if (isNotNumber(year.strRepresentation) || isNotNumber(month.strRepresentation) || isNotNumber(day.strRepresentation))
	{
		std::string	errMsg = "Invalid year/month/day : " + year.strRepresentation + "-" + month.strRepresentation + "-" + day.strRepresentation + "\n";
		throw	std::runtime_error(errMsg.c_str());
	}
	


	// std::string::iterator start	= std::find_if(line.begin(), line.end(), FindNotSpace());
	// std::string::iterator end	= std::find_if(start, line.end(), FindSpace());
	// std::string(start, end).swap(line);

}


void	BitcoinExchange::validateDate(std::string	date)
{
	std::string	errorMsg = date + ": Invalid date\n";
	DataRep		year;
	DataRep		month;
	DataRep		day;
	// std::cout <<"==" << date << "==" <<std::endl;
	std::stringstream	ss(date);
	if (date[4] != '-' || date[7] != '-')
		throw	std::runtime_error(errorMsg.c_str());

	std::getline(ss, year.strRepresentation, '-');
	std::getline(ss, month.strRepresentation, '-');
	std::getline(ss, day.strRepresentation, '-');
	
	trimSpacesFromStartEnd(year.strRepresentation);
	trimSpacesFromStartEnd(month.strRepresentation);
	trimSpacesFromStartEnd(day.strRepresentation);
	// std::cout << "."<< year.strRepresentation << ". ." << month.strRepresentation << ". ."<< day.strRepresentation << "." << std::endl;
	
	getIntRepresentations(year, month, day);
	
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
