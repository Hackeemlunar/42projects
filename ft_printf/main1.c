/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:25:03 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/17 18:45:46 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "libft/libft.h"
#include "ft_printf.h"

int	main(void)
{
	char	a[20] = "-423";
	// int64_t a = 21474837867;
	int b = ft_printf("klI : %%42%32c42k\nkk\n", (char)0);
	int c = printf("klI : %%42%32c42k\nkk\n", (char)0);
	printf("ft_printf: %d\n", b);
	printf("printf: %d\n", c);
}
