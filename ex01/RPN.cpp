/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimbow <jimbow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 10:37:07 by jimbow            #+#    #+#             */
/*   Updated: 2026/06/03 11:15:46 by jimbow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>
#include <iostream>
#include <stdexcept>

RPN::RPN()
{
}

RPN::RPN(const RPN& copy)
{
	(void)copy;
}

RPN& RPN::operator=(const RPN& copy)
{
	(void)copy;
	return *this;
}

RPN::~RPN()
{
}

bool RPN::isOperator(const std::string& token)
{
	return token == "+" || token == "-" || token == "*" || token == "/";
}

double RPN::applyOp(double a, double b, const std::string& op)
{
	if (op == "+")
		return a + b;
	if (op == "-")
		return a - b;
	if (op == "*")
		return a * b;
	if (op == "/")
	{
		if (b == 0)
			throw std::runtime_error("Divided by 0");
		return a / b;
	}
	
	throw std::runtime_error("Unknown operator");
}

double RPN::evaluate(const std::string& expr)
{
	std::stack<double> st;
	std::istringstream iss(expr);
	std::string token;

	while (iss >> token)
	{
		if (!isOperator(token))
		{
			if (token.size() != 1 || !isdigit(token[0]))
				throw std::runtime_error("Invalid token");
			
			st.push(token[0] - '0');
		}
		else
		{
			if (st.size() < 2)
				throw std::runtime_error("Invalid expression");

			double b = st.top();
			st.pop();
			double a = st.top();
			st.pop();

			st.push(applyOp(a, b, token));
		}
	}

	if (st.size() != 1)
		throw std::runtime_error("Invalid expression");

	return st.top();
}