#include "BitcoinExchange.hpp"

/* ---------------------------- Canonical form ---------------------------- */

BitcoinExchange::BitcoinExchange() : _valid(false)
{
}

BitcoinExchange::BitcoinExchange(const std::string &databaseFile) : _valid(false)
{
	_valid = loadDatabase(databaseFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	*this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		_rates = other._rates;
		_valid = other._valid;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

bool BitcoinExchange::isValid() const
{
	return (_valid);
}

/* ------------------------------- Helpers ---------------------------------- */

// Strips whitespace INCLUDING \r and \n, so CRLF-terminated files don't
// leave stray characters glued onto the last field of a line.
std::string BitcoinExchange::trim(const std::string &s)
{
	size_t start = 0;
	size_t end = s.size();

	while (start < end && std::isspace(static_cast<unsigned char>(s[start])))
		start++;
	while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1])))
		end--;
	return (s.substr(start, end - start));
}

bool BitcoinExchange::isLeapYear(int year)
{
	if (year % 4 != 0)
		return (false);
	if (year % 100 == 0 && year % 400 != 0)
		return (false);
	return (true);
}

// Full calendar validation: digits in the right places, month 1-12,
// day within that month's actual length (leap years included).
bool BitcoinExchange::isValidDate(const std::string &date)
{
	if (date.size() != 10)
		return (false);
	if (date[4] != '-' || date[7] != '-')
		return (false);
	for (size_t i = 0; i < date.size(); i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(static_cast<unsigned char>(date[i])))
			return (false);
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (year < 2009 || year > 9999)
		return (false);
	if (month < 1 || month > 12)
		return (false);
	if (day < 1)
		return (false);

	static const int daysInMonth[12] =
		{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int maxDay = daysInMonth[month - 1];
	if (month == 2 && isLeapYear(year))
		maxDay = 29;
	if (day > maxDay)
		return (false);
	return (true);
}

/* ------------------------------- Database ---------------------------------- */

// Returns false on any failure that leaves _rates unusable. The caller
// (constructor -> _valid) is responsible for making sure processInputFile()
// never runs in that case -- calling getRate() on an empty map is
// undefined behavior, so that check can't be skipped.
bool BitcoinExchange::loadDatabase(const std::string &databaseFile)
{
	std::ifstream ifs(databaseFile.c_str());
	if (!ifs.is_open())
	{
		std::cout << "Error: could not open database file." << std::endl;
		return (false);
	}

	std::string line;
	bool firstLine = true;
	while (std::getline(ifs, line))
	{
		if (line.empty())
			continue;
		if (firstLine)
		{
			firstLine = false;
			continue; // skip "date,exchange_rate" header
		}
		size_t pos = line.find(',');
		if (pos == std::string::npos)
			continue;

		std::string date = trim(line.substr(0, pos));
		std::string valueStr = trim(line.substr(pos + 1));

		if (!isValidDate(date) || valueStr.empty())
			continue;

		char *endptr = NULL;
		double rate = std::strtod(valueStr.c_str(), &endptr);
		if (endptr == valueStr.c_str() || *endptr != '\0')
			continue;

		_rates[date] = rate;
	}

	if (_rates.empty())
	{
		std::cout << "Error: database is empty or invalid." << std::endl;
		return (false);
	}
	return (true);
}

double BitcoinExchange::getRate(const std::string &date) const
{
	std::map<std::string, double>::const_iterator it = _rates.lower_bound(date);

	if (it != _rates.end() && it->first == date)
		return (it->second);
	if (it == _rates.begin())
		return (it->second); // no earlier date exists; best available
	--it;
	return (it->second);
}

/* ----------------------------- Input processing ----------------------------- */

bool BitcoinExchange::processInputFile(const std::string &inputFile) const
{
	std::ifstream ifs(inputFile.c_str());
	if (!ifs.is_open())
	{
		std::cout << "Error: could not open file." << std::endl;
		return (false);
	}

	std::string line;
	std::getline(ifs, line);
	while (std::getline(ifs, line))
	{
		line = trim(line); // handles CRLF-terminated input files too
		if (line.empty())
			continue;
		size_t pos = line.find('|');
		if (pos == std::string::npos || line.find('|', pos + 1) != std::string::npos)
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string datePart = trim(line.substr(0, pos));
		std::string valuePart = trim(line.substr(pos + 1));

		if (!isValidDate(datePart))
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		if (valuePart.empty())
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}

		char *endptr = NULL;
		double value = std::strtod(valuePart.c_str(), &endptr);
		if (endptr == valuePart.c_str() || *endptr != '\0')
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}

		if (value < 0)
		{
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000)
		{
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}

		double rate = getRate(datePart);
		std::cout << datePart << " => " << valuePart << " = "
			<< (value * rate) << std::endl;
	}
	return (true);
}