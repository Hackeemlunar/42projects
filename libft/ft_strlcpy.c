/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:03:28 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/22 17:55:11 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(src);
	if (dstsize == 0)
		return (len);
	while (i < (int)dstsize - 1 && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
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
