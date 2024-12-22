/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:09:25 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/22 16:28:26 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	temp[11];
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = (char *) malloc(12);
	if (!res)
		return (NULL);
	if (n < 0)
	{
		res[j++] = '-';
		n = -(n);
	}
	while (n > 0)
	{
		temp[i++] = (n % 10) + '0';
		n /= 10;
	}
	while (i > 0)
		res[j++] = temp[--i];
	res[j] = '\0';
	return (res);
}

int	main(void)
{
	printf("Numchar: %s\n", ft_itoa(0));
	return (0);
}
