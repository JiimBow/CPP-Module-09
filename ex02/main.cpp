/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimbow <jimbow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:42:56 by jodone            #+#    #+#             */
/*   Updated: 2026/06/26 12:01:09 by jimbow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <string>
#include <sys/time.h>

int	main(int ac, char **av)
{
	if (ac == 1)
	{
		std::cout << "Error: You must give arguments" << std::endl;
		return 1;
	}

	struct timeval startVec, startDeq, endVec, endDeq;
	PmergeMe p;

	if (p.parse(ac, av))
		return 1;

	gettimeofday(&startVec, NULL);
	std::vector<int> sortedVec = p.fordJohnson(p.getVec());
	gettimeofday(&endVec, NULL);

	gettimeofday(&startDeq, NULL);
	std::deque<int> sortedDeq = p.fordJohnson(p.getDeq());
	gettimeofday(&endDeq, NULL);

	if (!p.areEqual(sortedVec, sortedDeq))
	{
		std::cout << "Error: Both vector and deque are not equal" << std::endl;
		return 1;
	}

	std::cout << "After: ";
	for (size_t i = 0; i < sortedVec.size(); i++)
	{
		std::cout << sortedVec[i];
		if (i + 1 < sortedVec.size())
			std::cout << " ";
	}
	std::cout << std::endl;

	long secVec = endVec.tv_sec - startVec.tv_sec;
	long usecVec = endVec.tv_usec - startVec.tv_usec;
	double time_usVec = secVec * 1000000 + usecVec;

	std::cout << "Time to process a range of " << sortedVec.size() << " elements with std::vector : " << time_usVec << " us" << std::endl;

	long secDeq = endDeq.tv_sec - startDeq.tv_sec;
	long usecDeq = endDeq.tv_usec - startDeq.tv_usec;
	double time_usDeq = secDeq * 1000000 + usecDeq;

	std::cout << "Time to process a range of " << sortedDeq.size() << " elements with std::deque : " << time_usDeq << " us" << std::endl;
	return 0;
}
