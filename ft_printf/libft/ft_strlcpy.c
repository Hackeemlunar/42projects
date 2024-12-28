/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:03:28 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/28 16:41:39 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = 0;
	while (src[src_len])
		src_len++;
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (i < dstsize - 1 && i < src_len)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	return (src_len);
}

// int	main(void)
// {
// 	char	*a;
// 	char	*aa;
// 	char	aaa[50] = "him";
// 	char	*b;
// 	char	*bb;
// 	char	bbb[50] = "him";

// 	a = "Hello World!";
// 	b = "Hello World!";
// 	aa = (char *) malloc(1);
// 	bb = (char *) malloc(1);

// 	printf("ft_strlcpy: %s len: %zu\n", aaa, ft_strlcpy(aaa, a, 2));
// 	printf("   strlcpy: %s len: %lu\n", bbb, strlcpy(bbb, b, 2));
// 	return (0);
// }
