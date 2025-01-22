/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:52:17 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/22 23:13:56 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	main(void)
{
	int k = 11111111;
	char *str = "%0#52x";
	int a = ft_printf(str, k);
	printf("\n");
	int b = printf(str, k);
	printf("\n");
	printf("ft_printf: %d\n", a);
	printf("printf: %d\n", b);
	return (0);
}
