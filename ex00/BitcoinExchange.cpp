/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimbow <jimbow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 08:58:59 by jimbow            #+#    #+#             */
/*   Updated: 2026/06/03 10:26:51 by jimbow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy) : _rates(copy._rates)
{
	
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& copy)
{
	if (this != &copy)
		_rates = copy._rates;

	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

void	BitcoinExchange::loadDatabase()
{
	std::ifstream file("data.csv");

	if (!file)
	{
		std::cerr << "Error : could not open data.csv." << std::endl;
		return ;
	}

	std::string line;

	std::getline(file, line);
	if (line != "date,exchange_rate")
	{
		std::cerr << "Error : Header from data.csv not correct." << std::endl;
		return ;
	}

	while  (std::getline(file, line))
	{
		size_t commaPos = line.find(',');

		std::string date = line.substr(0, commaPos);
		std::string rateStr = line.substr(commaPos + 1);

		double rate = std::atof(rateStr.c_str());

		_rates[date] = rate;
	}
}

bool	BitcoinExchange::isValidDate(const std::string& date) const
{
	if (date.length() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;

	for (size_t i = 0; i < date.length(); i++)
	{
		if (i == 4 || i == 7)
			continue;
		
		if (!std::isdigit(date[i]))
			return false;
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12)
		return false;

	int dayInMonth[] = 
	{
		31, 28, 31, 30,
		31, 30, 31, 31,
		30, 31, 30, 31
	};

	bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

	if (month == 2 && leap)
		dayInMonth[1] = 29;

	if (day < 1 || day > dayInMonth[month - 1])
		return false;

	if (date < "2009-01-02")
		return false;

	return true;
}

static	std::string trim(const std::string& str)
{
	size_t start = str.find_first_not_of(" \t");
	size_t end = str.find_last_not_of(" \t");

	if (start == std::string::npos)
		return "";

	return str.substr(start, end - start + 1);
}

void	BitcoinExchange::processInput(const std::string& filename)
{
	std::ifstream file(filename.c_str());

	if (!file)
	{
		std::cerr << "Error : could not open input file." << std::endl;
		return ;
	}

	std::string line;
	std::getline(file, line);
	if (line != "date | value")
	{
		std::cerr << "Error : Header from input not correct." << std::endl;
		return ;
	}

	while (std::getline(file, line))
	{
		size_t pipePos = line.find('|');
		if (pipePos == std::string::npos)
		{
			std::cerr << "Error : Bad input => " << line << std::endl;
			continue;
		}

		std::string date = line.substr(0, pipePos);
		std::string valueStr = line.substr(pipePos + 1);

		date = trim(date);
		valueStr = trim(valueStr);

		if (!isValidDate(date))
		{
			std::cerr << "Error : Bad input => " << line << std::endl;
			continue;
		}

		std::stringstream ss(valueStr);
		double value;
		char c;

		if (!(ss >> value) || (ss >> c))
		{
			std::cerr << "Error : bad input => " << line << std::endl;
			continue;
		}

		if (value < 0)
		{
			std::cerr << "Error : not a positive number." << std::endl;
			continue;
		}

		if (value > 1000)
		{
			std::cerr << "Error : too large number." << std::endl;
			continue;
		}

		std::map<std::string, double>::iterator it;

		it = _rates.lower_bound(date);

		if (it == _rates.end() || it->first != date)
		{
			if (it != _rates.begin())
				--it;
		}

		double result = value * it->second;

		std::cout << date << " => " << value << " = " << result << std::endl;
	}
}
