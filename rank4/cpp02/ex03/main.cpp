/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:28:09 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/25 15:54:53 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Point.hpp"

int main(void)
{
	Point a(0.0f, 0.0f);
	Point b(10.0f, 0.0f);
	Point c(0.0f, 10.0f);

	Point inside(1.0f, 1.0f);
	Point outside(10.0f, 10.0f);
	Point onEdge(5.0f, 0.0f);
	Point vertex(0.0f, 0.0f);

	std::cout << "inside: " << (bsp(a, b, c, inside) ? "true" : "false") << "\n";
	std::cout << "outside: " << (bsp(a, b, c, outside) ? "true" : "false") << "\n";
	std::cout << "on edge: " << (bsp(a, b, c, onEdge) ? "true" : "false") << "\n";
	std::cout << "vertex: " << (bsp(a, b, c, vertex) ? "true" : "false") << "\n";

	return 0;
}
