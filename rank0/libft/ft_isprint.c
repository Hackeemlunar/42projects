/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:12:31 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/22 18:45:55 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

// int main(void)
// {
//     int a = 33;
//     printf("       num: %c\n", a);
//     printf("ft_isprint: %d\n", ft_isprint(a));
//     printf("   isprint: %d\n", isprint(a));
//     return 0;
// }
