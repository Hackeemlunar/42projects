/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:25:03 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/18 18:04:47 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "libft/libft.h"
#include "ft_printf.h"

int	main(void)
{
	
	// char	a[20] = "-423";
	// int64_t a = 21474837867;
	int b = ft_printf("klI : \\!/%48c\\!/", (char)0);
	printf("\n");
	int c = printf("klI : \\!/%48c\\!/", (char)0);
	printf("\n");
	printf("ft_printf: %d\n", b);
	printf("printf: %d\n", c);
	printf("ints\n");
	ft_printf("%d\n", -200000);
	printf("%d\n", -200000);
}
