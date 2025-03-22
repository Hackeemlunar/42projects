/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:32:11 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/18 18:19:43 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_largest_position(t_stack *dst)
{
	int	max_pos;
	int	i;

	max_pos = 0;
	i = 1;
	while (i < dst->size)
	{
		if (dst->arr[i] > dst->arr[max_pos])
			max_pos = i;
		i++;
	}
	return ((max_pos + 1) % dst->size);
}

int	find_target_position(t_stack *dst, int value)
{
	int	closest;
	int	closest_smaller_pos;
	int	i;

	if (dst->size == 0)
		return (0);
	closest = -1;
	closest_smaller_pos = -1;
	i = 0;
	while (i < dst->size)
	{
		if ((dst->arr[i] < value) && (closest == -1 || dst->arr[i] > closest))
		{
			closest = dst->arr[i];
			closest_smaller_pos = i;
		}
		i++;
	}
	if (closest_smaller_pos == -1)
		return (find_largest_position(dst));
	return ((closest_smaller_pos + 1) % dst->size);
}

void	sort(t_stack *a, t_stack *b)
{
	int	min_pos;
	int	i;

	while (a->size > 3)
		pb(b, a);
	sort_3(a);
	align_and_insert(a, b);
	min_pos = 0;
	i = -1;
	while (++i < a->size)
		if (a->arr[i] < a->arr[min_pos])
			min_pos = i;
	i = -1;
	if (min_pos <= a->size / 2)
		while (++i < min_pos)
			ra(a);
	else
		while (++i < a->size - min_pos)
			rra(a);
}
