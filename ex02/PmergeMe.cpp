/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:43:33 by jodone            #+#    #+#             */
/*   Updated: 2026/06/24 09:57:57 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <string>
#include <set>

int PmergeMe::parse(int ac, char **av)
{
	for (size_t i = 0; i < ac; ++i)
	{
		std::string arg(av[i]);
		if (arg.size() > 11)
		{
			std::cerr << "Error: argument too long" << std::endl;
			return 1;
		}
		long number = std::strtol(av[i], NULL, 10);
		if (number < 0)
		{
			std::cerr << "Error: You must give positives int as arguments" << std::endl;
			return 1;
		}
		if (number > 2147483647)
		{
			std::cerr << "Error: Arguments can't be higher than INT MAX" << std::endl;
			return 1;
		}
		_vec.push_back(static_cast<int>(number));
	
		std::set<int> unique(_vec.begin(), _vec.end());
		if (unique.size() != _vec.size())
		{
			std::cerr << "Error: You must give unique elements" << std::endl;
			return 1;
		}
	}
	return 0;
}

void PmergeMe::sortVector()
{
	std::vector<Pair> pairs;
	bool hasLast = false;
	int last = 0;

	for (size_t i = 0; i + 1 < _vec.size(); i += 2)
	{
		Pair p;

		p.first = _vec[i];
		p.second = _vec[i + 1];

		pairs.push_back(p);
	}
	if (_vec.size() % 2)
	{
		hasLast = true;
		last = _vec.back();
	}
	for (size_t i = 0; i < pairs.size(); i++)
	{
		if (pairs[i].first > pairs[i].second)
			std::swap(pairs[i].first, pairs[i].second);
	}
}