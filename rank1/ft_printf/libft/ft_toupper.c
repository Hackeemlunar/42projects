/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:24:44 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/27 18:41:40 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return ('A' + (c - 'a'));
	return (c);
}

// int main(void)
// {
//     int a = '0';
//     printf("       num: %c\n", a);
//     printf("ft_toupper: %c\n", ft_toupper(a));
//     printf("  touppper: %c\n", toupper(a));
//     return 0;
// }
