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
	bool operator()(char c){return !::isspace(c);}		
};

struct FirstPipe
{
	bool operator()(char c){return (c == '|');}
};

struct FindSpace
{
	bool operator()(char c){return ::isspace(c);}
};

struct FindNonDigit
{
	bool operator()(char c){return !::isdigit(c);}		
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


class BitcoinExchange
{
	

	public:
		BitcoinExchange(const std::string&);
		// BitcoinExchange(const BitcoinExchange&);
		// BitcoinExchange	&	operator=(const BitcoinExchange&);
		// ~BitcoinExchange();
		void	run(const	std::string&);

	private:
		void	openFile();
		bool	isNotValidHeader(std::string&);
		void	printData();
		void	fillDatabase();
		void	start_parsing(const std::ifstream& file);
		void	trimSpacesFromStartEnd(std::string&);
		void	validateDate(std::string);
		void	getIntRepresentations(DataRep&, DataRep&, DataRep&);
		bool	isNotNumber(std::string	line);


	private:
		std::map<std::string, double>	data__;
		std::string						fileName;

		

};


# endif	//	BITCOIN_EXCHANGE_HPP