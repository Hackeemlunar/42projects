/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:43:31 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/23 17:13:50 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

// void	test_ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	int	result_libc;
// 	int	result_ft;

// 	result_libc = strncmp(s1, s2, n);
// 	result_ft = ft_strncmp(s1, s2, n);
// 	if (result_libc == result_ft)
// 		printf("PASS: strncmp(\"%s\", \"%s\", %zu) 
// == %d\n", s1, s2, n, result_libc);
// 	else
// 	{
// 		printf("FAIL: strncmp(\"%s\", \"%s\", %zu) 
// == %d, but ft_strncmp == %d\n",
// 			s1, s2, n, result_libc, result_ft);
// 	}
// }

// int	main(void) {
// 	test_ft_strncmp("hello", "hello", 5);
// 	test_ft_strncmp("hello", "hella", 5);
// 	test_ft_strncmp("hello", "hella", 4);
// 	test_ft_strncmp("hello", "helloa", 6);
// 	test_ft_strncmp("hello", "helloa", 5);
// 	test_ft_strncmp("hello", "", 5);
// 	test_ft_strncmp("", "hello", 5);
// 	test_ft_strncmp("", "", 5);
// 	test_ft_strncmp("hello", "hello", 0);
// 	test_ft_strncmp("hello", "helloa", 0);
// 	return (0);
// }
