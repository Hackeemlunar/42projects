/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:47:50 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/22 18:48:50 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*s_copy;
	int		i;
	size_t	s_len;

	i = 0;
	s_copy = (char *)s;
	s_len = (size_t) ft_strlen(s_copy);
	if (n > s_len)
		n = s_len;
	while (i < (int)n)
	{
		if (s_copy[i] == c)
			return (&s_copy[i]);
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
