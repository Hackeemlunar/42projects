#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error: could not open file." << std::endl;
		return (1);
	}

	BitcoinExchange exchange("data.csv");
	if (!exchange.isValid())
		return (1);

	if (!exchange.processInputFile(argv[1]))
		return (1);

	return (0);
}
