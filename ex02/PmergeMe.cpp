/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:43:33 by jodone            #+#    #+#             */
/*   Updated: 2026/07/01 14:04:22 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <string>
#include <set>
#include <algorithm>

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
		char *errptr;
		long number = std::strtol(av[i], &errptr, 10);
	
		if (*errptr != '\0')
		{
			std::cerr << "Error: You must give positives int as arguments" << std::endl;
			return 1;
		}

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
		_deq.push_back(static_cast<int>(number));
	
		std::set<int> unique(_vec.begin(), _vec.end());
		if (unique.size() != _vec.size())
		{
			std::cerr << "Error: You must give unique elements" << std::endl;
			return 1;
		}
	}

	std::cout << "Before: ";
	for (size_t i = 0; i < _vec.size(); i++)
	{
		std::cout << _vec[i];
		if (i + 1 < _vec.size())
			std::cout << " ";
	}
	std::cout << std::endl;
	return 0;
}


// VECTOR

static std::vector<int> jacobsthal(int n)
{
	std::vector<int> j;
	j.push_back(1);
	j.push_back(3);

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
	std::vector<bool> used(size, false);

	int prev = 0;

	for (size_t i = 0; i < jac.size(); i++)
	{
		int end = jac[i];
		if (end > size)
			end = size;

		for (int j = end; j > prev; j--)
		{
			if (!used[j - 1])
			{
				order.push_back(j - 1);
				used[j - 1] = true;
			}
		}
		prev = end;
	}

	for (int i = size - 1; i >= 0; i--)
	{
		if (!used[i])
			order.push_back(i);
	}

	return order;
}

std::vector<int>	PmergeMe::fordJohnson(std::vector<int> input)
{
	if (input.size() <= 1)
		return input;
	
	std::vector<Pair> pairs;
	for (size_t i = 0; i + 1 < input.size(); i += 2)
	{
		Pair p;
		if (input[i] < input[i + 1])
		{
			p.first = input[i];
			p.second = input[i + 1];
		}
		else
		{
			p.first = input[i + 1];
			p.second = input[i];
		}
		pairs.push_back(p);
	}

	std::vector<int> bigs;

	for (size_t i = 0; i < pairs.size(); i++)
		bigs.push_back(pairs[i].second);
	
	bigs = fordJohnson(bigs);

	std::vector<int> result = bigs;

	std::vector<int> order = insertionOrder(pairs.size());
	for (size_t i = 0; i < order.size(); i++)
	{
		Pair& p = pairs[order[i]];

		std::vector<int>::iterator partner = std::find(result.begin(), result.end(), p.second);

		std::vector<int>::iterator pos = std::lower_bound(result.begin(), partner, p.first);

		result.insert(pos, p.first);
	}

	if (input.size() % 2 != 0)
	{
		int last = input.back();

		std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.end(), last);
		result.insert(pos, last);
	}

	return result;
}


// DEQUE

static std::deque<int> jacobsthalDeque(int n)
{
	std::deque<int> j;
	j.push_back(1);
	j.push_back(3);

	while (1)
	{
		int next = j[j.size() - 1] + 2 * j[j.size() - 2];
		if (next > n)
			break;
		j.push_back(next);
	}
	return j;
}

static std::deque<int> insertionOrderDeque(int size)
{
	std::deque<int> order;
	std::deque<int> jac = jacobsthalDeque(size);
	std::vector<bool> used(size, false);

	int prev = 0;

	for (size_t i = 0; i < jac.size(); i++)
	{
		int end = jac[i];
		if (end > size)
			end = size;

		for (int j = end; j > prev; j--)
		{
			if (!used[j - 1])
			{
				order.push_back(j - 1);
				used[j - 1] = true;
			}
		}
		prev = end;
	}

	for (int i = size - 1; i >= 0; i--)
	{
		if (!used[i])
			order.push_back(i);
	}

	return order;
}

std::deque<int>	PmergeMe::fordJohnson(std::deque<int> input)
{
	if (input.size() <= 1)
		return input;
	
	std::deque<Pair> pairs;
	for (size_t i = 0; i + 1 < input.size(); i += 2)
	{
		Pair p;
		if (input[i] < input[i + 1])
		{
			p.first = input[i];
			p.second = input[i + 1];
		}
		else
		{
			p.first = input[i + 1];
			p.second = input[i];
		}
		pairs.push_back(p);
	}

	std::deque<int> bigs;

	for (size_t i = 0; i < pairs.size(); i++)
		bigs.push_back(pairs[i].second);
	
	bigs = fordJohnson(bigs);

	std::deque<int> result = bigs;

	std::deque<int> order = insertionOrderDeque(pairs.size());
	for (size_t i = 0; i < order.size(); i++)
	{
		Pair& p = pairs[order[i]];

		std::deque<int>::iterator partner = std::find(result.begin(), result.end(), p.second);

		std::deque<int>::iterator pos = std::lower_bound(result.begin(), partner, p.first);

		result.insert(pos, p.first);
	}

	if (input.size() % 2 != 0)
	{
		int last = input.back();

		std::deque<int>::iterator pos = std::lower_bound(result.begin(), result.end(), last);
		result.insert(pos, last);
	}

	return result;
}


// GETTER

const std::vector<int>& PmergeMe::getVec() const
{
	return _vec;
}

const std::deque<int>& PmergeMe::getDeq() const
{
	return _deq;
}