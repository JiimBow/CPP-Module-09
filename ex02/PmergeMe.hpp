/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:43:22 by jodone            #+#    #+#             */
/*   Updated: 2026/06/25 09:57:27 by jodone           ###   ########.fr       */
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
	void	sortVector();
	void	sortDeque();
};

#endif