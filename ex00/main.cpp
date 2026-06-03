/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimbow <jimbow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 08:58:18 by jimbow            #+#    #+#             */
/*   Updated: 2026/06/03 09:46:42 by jimbow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Program must have only one argument" << std::endl;
		return 1;
	}

	BitcoinExchange btc;

	btc.loadDatabase();
	btc.processInput(av[1]);

	return 0;
}
