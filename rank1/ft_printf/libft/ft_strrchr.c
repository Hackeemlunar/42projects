/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:05:52 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/23 16:07:41 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*last_occurrence;

	i = 0;
	last_occurrence = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			last_occurrence = (char *)&s[i];
		}
		i++;
	}
	if (c == '\0')
	{
		return ((char *)&s[i]);
	}
	return (last_occurrence);
}

// int main(void)
// {
//     // Example test for *ft_strrchr
//     const char *str = "Hello, world!";
//     char ch = 'o';
//     char *result = ft_strrchr(str, ch);
//     if (result)
//     {
//         printf("Last occurrence of '%c' found at position:
//  %ld\n", ch, result - str);
//     }
//     else
//     {
//         printf("Character '%c' not found in the string.\n", ch);
//     }
//     return 0;
// }
