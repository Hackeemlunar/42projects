/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:25:03 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/15 20:25:40 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "libft/libft.h"
#include "ft_printf.h"

int main()
{
    char a[20] = "-423";
    // int64_t a = 21474837867;
    int b = ft_printf("klI : %#2.5s\n", a);
    int c = printf("klI : %#2.5s\n", a);
    printf("ft_printf: %d\n", b);
    printf("printf: %d\n", c);
}