# ifndef	BITCOIN_EXCHANGE_HPP
# define	BITCOIN_EXCHANGE_HPP

#include <iostream>
#include <map>
#include <iterator>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

struct FindNotSpace
{
	bool operator()(char c){ return !::isspace(c); }
};

struct FirstPipe
{
	bool operator()(char c){ return (c == '|'); }
};

struct FindSpace
{
	bool operator()(char c){ return ::isspace(c); }
};

struct FindNonDigit
{
	bool operator()(char c){ return !::isdigit(c); }
};

typedef struct	s_DataRep
{	
	s_DataRep()
	{
		strRepresentation = "";
		intRepresentation = -1;
	}

	int				intRepresentation;
	std::string		strRepresentation;
}	DataRep;

enum	MONTH30 
{
	FEB = 2,
	APR = 4,
	JUN = 6,
	SEP = 9,
	NOV = 11
};

typedef std::map<std::string, double> Database;

class BitcoinExchange
{
	

	public:
		BitcoinExchange(const std::string&);
		BitcoinExchange(const BitcoinExchange&);
		BitcoinExchange	&	operator=(const BitcoinExchange&);
		~BitcoinExchange();
		void	run(const	std::string&);

	private:
		bool	isNotValidHeader(std::string&);
		void	printData();
		void	fillDatabase();
		void	trimSpacesFromStartEnd(std::string&);
		void	validateDate(std::string&);
		void	validate_ymd(DataRep&, DataRep&, DataRep&);
		void	getIntRepresentations(DataRep&, DataRep&, DataRep&);
		bool	isNotNumber(std::string	line);
		void 	validate_value(std::string&);
		void	printValueFromDb(std::string&, std::string&);

	private:
		Database		data__;
		std::string		fileName;
};


# endif	//	BITCOIN_EXCHANGE_HPP