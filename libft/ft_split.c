/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:24:46 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/23 20:27:18 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	in_charset(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

int	count_words(char *str, char *charset)
{
	int	all_words;
	int	i;
	int	state;

	i = 0;
	all_words = 0;
	state = 0;
	while (str[i] != '\0')
	{
		if (!in_charset(str[i], charset) && !state)
		{
			all_words++;
			state = 1;
		}
		else if (in_charset(str[i], charset))
			state = 0;
		i++;
	}
	return (all_words);
}

int	check_copy(char **arr, char *str, int len, int j)
{
	char	*temp;
	int		i;

	temp = (char *)malloc(len + 1);
	if (temp == NULL)
		return (0);
	i = 0;
	while (i < len)
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = '\0';
	arr[j] = temp;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		word_len;
	int		i;
	int		j;

	arr = (char **)malloc(sizeof(char *) * (count_words(str, charset) + 1));
	i = -1;
	word_len = 0;
	j = 0;
	while (str[++i])
	{
		if (!in_charset(str[i], charset))
			word_len++;
		else if (word_len > 0)
		{
			j += check_copy(arr, &str[i - word_len], word_len, j);
			word_len = 0;
		}
	}
	if (word_len > 0)
		j += check_copy(arr, &str[i - word_len], word_len, j);
	arr[j] = NULL;
	return (arr);
}

int	main(void)
{
	return (0);
}
