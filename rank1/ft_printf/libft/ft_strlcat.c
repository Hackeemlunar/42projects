/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:27:20 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/22 21:52:22 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	src_size;
	unsigned int	dest_size;

	i = 0;
	src_size = ft_strlen(src);
	dest_size = ft_strlen(dst);
	if (dstsize <= dest_size || dstsize == 0)
		return (dstsize + src_size);
	while (src[i] != '\0' && i < dstsize - dest_size - 1)
	{
		dst[dest_size + i] = src[i];
		i++;
	}
	dst[dest_size + i] = '\0';
	return (dest_size + src_size);
}

// int main(void)
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
// 	printf("ft_strlcat: %s len: %zu\n", aaa, ft_strlcat(aaa, a, 12));
// 	printf("   strlcat: %s len: %lu\n", bbb, strlcat(bbb, b, 12));
// 	return (0);
// }
