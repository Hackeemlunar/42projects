/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_util1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:13:22 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/16 21:51:28 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_3(t_stack *a)
{
	if (a->arr[0] > a->arr[1] && a->arr[0] > a->arr[2])
		ra(a);
	else if (a->arr[1] > a->arr[0] && a->arr[1] > a->arr[2])
		rra(a);
	if (a->arr[0] > a->arr[1])
		sa(a);
}

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

void	calculate_min_cost(t_rotation *cost, int *oper)
{
	if (cost->rb > cost->ra)
		oper[0] = cost->rb;
	else
		oper[0] = cost->ra;
	oper[1] = cost->rb + cost->rra;
	oper[2] = cost->rrb + cost->ra;
	if (cost->rrb > cost->rra)
		oper[3] = cost->rrb;
	else
		oper[3] = cost->rra;
	cost->total = oper[0];
	cost->rot_type = FORWARD_FORWARD;
	if (oper[1] < cost->total)
	{
		cost->total = oper[1];
		cost->rot_type = FORWARD_REVERSE;
	}
	if (oper[2] < cost->total)
	{
		cost->total = oper[2];
		cost->rot_type = REVERSE_FORWARD;
	}
}

t_rotation	calc_cost_transfer(t_stack *src, t_stack *dst, int src_index)
{
	t_rotation	cost;
	int			value;
	int			target_pos;
	int			oper[4];

	value = src->arr[src_index];
	target_pos = find_target_position(dst, value);
	cost.rb = src_index;
	cost.rrb = src->size - src_index;
	cost.ra = target_pos;
	cost.rra = dst->size - target_pos;
	calculate_min_cost(&cost, oper);
	if (oper[3] < cost.total)
	{
		cost.total = oper[3];
		cost.rot_type = REVERSE_REVERSE;
	}
	return (cost);
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
