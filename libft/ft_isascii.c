/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:04:55 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/22 18:45:21 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

// int main(void)
// {
//     int a = 120;
//     printf("ft_isalnum: %c\n", a);
//     printf("ft_isalnum: %d\n", ft_isascii(a));
//     printf("   isalnum: %d\n", isascii(a));
//     return 0;
// }
