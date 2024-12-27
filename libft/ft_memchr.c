/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:47:50 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/27 22:53:09 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_copy;
	size_t			i;

	i = 0;
	s_copy = (unsigned char *)s;
	while (i < n)
	{
		if (s_copy[i] == (unsigned char) c)
			return ((void *) &s_copy[i]);
		i++;
	}
	return (NULL);
}

// int main(void)
// {
//     char a[] = "Hello 43";
//     char *b = ft_memchr(a, '5', 15000);
//     if (b != NULL)
//     {
//         printf("%c", *b);
//     } else {
//         printf("NULL");
//     }
//     return 0;
// }
