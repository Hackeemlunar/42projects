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
	char *str = "!%+15d!";
	int a = ft_printf(str, k);
	printf("\n");
	int b = printf(str, k);
	printf("\n");
	printf("ft_printf: %d\n", a);
	printf("printf: %d\n", b);
	return (0);
}
