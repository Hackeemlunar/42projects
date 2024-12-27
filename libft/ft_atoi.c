/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:00:52 by hmensah-          #+#    #+#             */
/*   Updated: 2024/12/23 16:44:05 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\f' || c == '\r'
		|| c == '\v' || c == '\t');
}

int	ft_atoi(const char *str)
{
	long	res;
	int		sign;
	int		counter;

	res = 0;
	sign = 1;
	counter = 0;
	while (ft_isspace(str[counter]))
		counter++;

	if (str[counter] == '-' || str[counter] == '+')
	{
		if (str[counter] == '-')
			sign = -1;
		counter++;
	}
	while (str[counter] >= '0' && str[counter] <= '9')
	{
		if (res > (LONG_MAX - (str[counter] - '0')) / 10)
		{
			if (sign == 1)
				return -1;
			else
				return 0;
		}
		res = (res * 10) + (str[counter] - '0');
		counter++;
	}
	return ((int)(sign * res));
}

// int main(int argc, char **argv)
// {
//     argc += 0;
//     printf("FT_atoi: %d\n", ft_atoi(argv[1]));
//     printf("   Atoi: %d\n", atoi(argv[1]));
// }
