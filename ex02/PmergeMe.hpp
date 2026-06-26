/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimbow <jimbow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:43:22 by jodone            #+#    #+#             */
/*   Updated: 2026/06/26 12:01:41 by jimbow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>
#include <deque>

typedef struct Pair
{
	int first;
	int second;
}	t_pair;

class PmergeMe
{
private:
	std::vector<int>	_vec;
	std::deque<int>		_deq;
public:
	int		parse(int ac, char **av);
	std::vector<int>	fordJohnson(std::vector<int> input);
	std::deque<int>		fordJohnson(std::deque<int> input);

	const std::vector<int>& getVec() const;
	const std::deque<int>& getDeq() const;

	template <typename C1, typename C2>
	bool	areEqual(const C1& a, const C2& b)
	{
		if (a.size() != b.size())
			return false;
		for (std::size_t i = 0; i < a.size(); i++)
		{
			if (a[i] != b[i])
				return false;
		}
		return true;
	}
};

#endif