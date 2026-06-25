/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimbow <jimbow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 10:36:38 by jimbow            #+#    #+#             */
/*   Updated: 2026/06/03 10:43:44 by jimbow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <string>
#include <stack>

class RPN
{
private:
	bool isOperator(const std::string& token);
	double applyOp(double a, double b, const std::string& op);
public:
	RPN();
	RPN(const RPN& copy);
	RPN& operator=(const RPN& copy);
	~RPN();

	double evaluate(const std::string& expr);
};


#endif