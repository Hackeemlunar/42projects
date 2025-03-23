/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:05:42 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/23 21:05:57 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\f' || c == '\r'
		|| c == '\v' || c == '\t');
}

static int	get_number(const char *str, int sign)
{
	long	res;
	int		counter;

	res = 0;
	counter = 0;
	while (str[counter] >= '0' && str[counter] <= '9')
	{
		if (res > (LONG_MAX - (str[counter] - '0')) / 10)
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
		res = (res * 10) + (str[counter] - '0');
		counter++;
	}
	return ((int)(sign * res));
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		counter;

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
	return (get_number(&str[counter], sign));
}
