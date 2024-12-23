/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:58:19 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/23 17:02:37 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == '\0')
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}

// int main(void)
// {
//     const char *str = "Hello, world!";
//     const char *str1 = "Hello, world!";
//     char ch = '\0';
//     char *result = ft_strchr(str, ch);
//     char *result1 = strchr(str, ch);
//     if (result)
//     {
//         printf("First occurrence of '%c' found at position:
//  %ld\n", ch, result - str);
//         printf("First occurrence of '%c' found at position:
//  %ld\n", ch, result1 - str1);
//     }
//     else
//     {
//         printf("Character '%c' not found in the string.\n", ch);
//     }
//     return 0;
// }