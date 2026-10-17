#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(const std::string &databaseFile);
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		bool	isValid() const;
		bool	processInputFile(const std::string &inputFile) const;

	private:
		std::map<std::string, double>	_rates;
		bool							_valid;

		bool	loadDatabase(const std::string &databaseFile);
		double	getRate(const std::string &date) const;

		static bool			isValidDate(const std::string &date);
		static bool			isLeapYear(int year);
		static std::string	trim(const std::string &s);
};

#endif