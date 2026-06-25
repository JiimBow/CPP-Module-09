/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:42:56 by jodone            #+#    #+#             */
/*   Updated: 2026/06/25 10:05:20 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <string>

int	main(int ac, char **av)
{
	if (ac == 1)
	{
		std::cout << "Error: You must give arguments" << std::endl;
		return 1;
	}

	// 8 3 5 1 9 4 7
	PmergeMe p;

	if (p.parse(ac, av))
		return 1;
	std::cout << std::endl;
	p.sortVector();
	return 0;
}
