/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:48:07 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/10 20:36:32 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	index_stack(int *arr, int *copy, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			if (arr[i] == copy[j])
			{
				arr[i] = j;
				break ;
			}
			j++;
		}
		i++;
	}
	i = -1;
	while (++i < n)
		copy[i] = i;
}

int	has_duplicates(int *sorted, int n)
{
	int	i;

	i = 0;
	while (i < n - 1)
	{
		if (sorted[i] == sorted[i + 1])
			return (1);
		i++;
	}
	return (0);
}

int	is_sorted(t_stack *a)
{
	int	i;

	i = 0;
	while (i < a->size - 1)
	{
		if (a->arr[i] > a->arr[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int	has_error(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '-' && i == 0)
		{
			i++;
			continue ;
		}
		else if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	has_overflow(char *str)
{
	long	n;

	n = ft_atol(str);
	if (n > 2147483647 || n < -2147483648)
		return (1);
	return (0);
}
