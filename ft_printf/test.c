/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:52:17 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/20 19:42:39 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	main(void)
{
	int k = 9223372;
	int a = ft_printf("!%+-020.15d!", k);
	printf("\n");
	int b = printf("!%+-020.15d!", k);
	printf("\n");
	printf("ft_printf: %d\n", a);
	printf("printf: %d\n", b);
	return (0);
}
