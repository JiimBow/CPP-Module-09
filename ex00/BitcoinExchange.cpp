/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimbow <jimbow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 08:58:59 by jimbow            #+#    #+#             */
/*   Updated: 2026/06/01 09:52:59 by jimbow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
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
		std::cerr << "Can't open data.csv" << std::endl;
		return ;
	}

	std::string line;

	std::getline(file, line);
	if (line != "date,exchange_rate")
	{
		std::cerr << "Header from data.csv not correct" << std::endl;
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

void	BitcoinExchange::processInput(const std::string& filename)
{
	std::ifstream file(filename.c_str());

	if (!file)
	{
		std::cerr << "Can't open input file" << std::endl;
		return ;
	}

	std::string line;
	std::getline(file, line);
	if (line != "date | value")
	{
		std::cerr << "Header from input not correct" << std::endl;
		return ;
	}

	while (std::getline(file, line))
	{
		size_t pipePos = line.find('|');
		if (pipePos == std::string::npos)
		{
			std::cerr << "Bad input : " << line << std::endl;
			return ;
		}

		std::string date = line.substr(0, pipePos);
		std::string value = line.substr(pipePos + 1);
	}

}
