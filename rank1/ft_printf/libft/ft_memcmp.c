/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:53:22 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/27 23:08:24 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_cpy;
	unsigned char	*s2_cpy;

	s1_cpy = (unsigned char *) s1;
	s2_cpy = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (s1_cpy[i] != s2_cpy[i])
		{
			return (s1_cpy[i] - s2_cpy[i]);
		}
		i++;
	}
	return (0);
}

// int main(void)
// {
//     char a[] = "hello";
//     char a1[] = "hell4";

//     printf("       num: %s\n", a);
//     printf("ft_memcmp: %d\n", ft_memcmp(a, a1, 5));
//     printf("   memcmp: %d\n", memcmp(a, a1, 5));
//     return 0;
// }
