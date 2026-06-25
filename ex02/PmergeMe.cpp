/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:43:33 by jodone            #+#    #+#             */
/*   Updated: 2026/06/25 10:05:44 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <string>
#include <set>
#include <algorithm>

static std::vector<int> jacobsthal(int n)
{
	std::vector<int> j;
	j.push_back(0);
	j.push_back(1);

	while (1)
	{
		int next = j[j.size() - 1] + 2 * j[j.size() - 2];
		if (next > n)
			break;
		j.push_back(next);
	}
	return j;
}

static std::vector<int> insertionOrder(int size)
{
	std::vector<int> order;
	std::vector<int> jac = jacobsthal(size);
	std::vector<bool> used(size + 1, false);

	for (size_t i = 1; i < jac.size(); i++)
	{
		int end = jac[i];
		int start = jac[i - 1] + 1;

		for (int j = end; j >= start; j--)
		{
			if (j <= size && !used[j])
			{
				order.push_back(j);
				used[j] = true;
			}
		}
	}

	for (int i = size; i >= 1; i--)
	{
		if (!used[i])
			order.push_back(i);
	}

	return order;
}

int PmergeMe::parse(int ac, char **av)
{
	for (int i = 1; i < ac; i++)
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
	for (size_t i = 0; i < _vec.size(); i++)
	{
		std::cout << _vec[i];
		if (i + 1 < _vec.size())
			std::cout << " ";
	}
	std::cout << std::endl;
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

	std::vector<int> smalls;
	std::vector<int> bigs;

	for (size_t i = 0; i < pairs.size(); i++)
	{
		smalls.push_back(pairs[i].first);
		bigs.push_back(pairs[i].second);
	}
	std::sort(bigs.begin(), bigs.end());
	
	std::vector<int> order = insertionOrder(smalls.size());

	for (size_t i = 0; i < order.size(); i++)
	{
		int value = smalls[order[i] - 1];

		std::vector<int>::iterator pos = std::lower_bound(bigs.begin(), bigs.end(), value);

		bigs.insert(pos, value);
	}

	for (size_t i = 0; i < bigs.size(); i++)
	{
		std::cout << bigs[i];
		if (i + 1 < bigs.size())
			std::cout << " ";
	}
	std::cout << std::endl;
}