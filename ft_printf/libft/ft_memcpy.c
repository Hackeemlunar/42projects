/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 19:13:06 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/22 21:24:49 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int		i;
	char	*dst_cpy;
	char	*src_cpy;

	i = 0;
	dst_cpy = (char *) dst;
	src_cpy = (char *) src;
	while (i < (int) n)
	{
		dst_cpy[i] = src_cpy[i];
		i++;
	}
	return (dst);
}

// int	main(void)
// {
// 	char a[] = "abcdef";
// 	char *b = (char *) ft_memcpy(a+2, a+2, 3);
// 	printf("%s\n", b);
// 	printf("%s\n", a);
// 	return 0;
// }
