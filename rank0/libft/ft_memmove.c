/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 19:23:10 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/22 21:24:43 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_cpy;
	char	*src_cpy;
	size_t	i;

	dst_cpy = (char *) dst;
	src_cpy = (char *) src;
	i = -1;
	if (len == 0 || dst == src)
		return (dst);
	if (dst < src)
	{
		while (++i < len)
		{
			dst_cpy[i] = src_cpy[i];
		}
	}
	else
	{
		while (len > 0)
		{
			dst_cpy[len - 1] = src_cpy[len - 1];
			len--;
		}
	}
	return (dst);
}

// int	main(void)
// {
// 	char a[] = "abcdef";
// 	char aa[] = "abcdef";
// 	char *c = (char *) memmove(a+2, a+2, 3);
// 	char *b = (char *) ft_memmove(aa+2, aa+2, 3);
// 	printf("%s\n", b);
// 	printf("%s\n", a);
// 	printf("%s\n", c);
// 	return 0;
// }
