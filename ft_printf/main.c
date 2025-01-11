/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 21:25:41 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/11 22:03:45 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include "ft_printf.h"

// int mult(int count, ...) {
//     va_list args;
//     va_start(args, count);
//     va_arg(args, int);
//     va_end(args);
// }

int	main(int argc, char **argv)
{
	argc += 0;
	ft_printf("  Mine: %.2s\n", argv[1]);
	printf("System: %.2s\n", argv[1]);
	return (0);
}
