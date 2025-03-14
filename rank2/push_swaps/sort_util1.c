/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_util1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:13:22 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/14 21:34:16 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	min(int *arr, int n)
{
	int	min;
	int	i;

	min = arr[0];
	i = 1;
	while (i < n)
	{
		if (arr[i] < min)
			min = arr[i];
		i++;
	}
	return (min);
}

void	align_and_insert(t_stack *a, t_stack *b)
{
	t_rotation	min_cost;
	t_rotation	current;
	int			i;

	while (b->size > 0)
	{
		min_cost.total = INT_MAX;
		i = 0;
		while (i < b->size)
		{
			current = calc_cost_transfer(b, a, i);
			if (current.total < min_cost.total)
				min_cost = current;
			i++;
		}
		exec_rot_transfer(b, a, min_cost);
		pa(a, b);
	}
}
