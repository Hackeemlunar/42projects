/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:32:11 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/14 21:49:33 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * find_target_position(dst, value):
 * Given a destination stack (dst), find the position where `value`
 * should be inserted. If no element in dst is smaller than value,
 * we choose the position after the largest element.
 */
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

/*
 * calculate_cost_transfer(src, dst, src_index):
 * Computes the cost to transfer an element from src (B) at index `src_index`
 * into dst (A) in its proper sorted position.
 * We calculate:
 *   - cost for rotating src (B) to bring the element to the top
 *   - cost for rotating dst (A) so that its insertion point is at the top
 * Then, we consider four strategies:
 *   1. Common forward rotations (rr): cost = max(rb, ra)
 *   2. Forward on src and reverse on dst: cost = rb + rra
 *   3. Reverse on src and forward on dst: cost = rrb + ra
 *   4. Common reverse rotations (rrr): cost = max(rrb, rra)
 * and choose the minimal cost.
 */
t_rotation	calc_cost_transfer(t_stack *src, t_stack *dst, int src_index)
{
	t_rotation	cost;
	int			value;
	int			target_pos;
	int			costs[4];

	value = src->arr[src_index];
	target_pos = find_target_position(dst, value);
	cost.rb = src_index;
	cost.rrb = src->size - src_index;
	cost.ra = target_pos;
	cost.rra = dst->size - target_pos;
	costs[0] = cost.ra;
	if (cost.rb > costs[0])
		costs[0] = cost.rb;
	costs[1] = cost.rb + cost.rra;
	costs[2] = cost.rrb + cost.ra;
	costs[3] = cost.rra;
	if (cost.rrb > costs[3])
		costs[3] = cost.rrb;
	cost.total = costs[0];
	return (cost.total = min(costs, 4), cost);
}

void	push_b(t_stack *a, t_stack *b, int *sorted, int n)
{
	while (a->size > 2)
	{
		pb(b, a);
		if (b->size > 1 && b->arr[0] > sorted[n / 2])
			rr(a, b);
	}
}
/*
 * 		Turk_sort:
 * 1. Push all elements from A to B.
 * 2. Seed A with one element from B.
 * 3. While B is not empty, calculate the cost for each element in B to be
 *    inserted into A (using calculate_cost_transfer) and choose the one
 *    with minimal cost.
 * 4. Execute the corresponding rotations (via exec_rotations_transfer)
 * 		and push it into A.
 * 5. Finally, rotate A so that the smallest element is at the top.
 */
void	sort(t_stack *a, t_stack *b, int *sorted, int n)
{
	int	min_pos;
	int	i;

	push_b(a, b, sorted, n);
	align_and_insert(a, b);
	min_pos = 0;
	i = -1;
	while (++i < a->size)
		if (a->arr[i] < a->arr[min_pos])
			min_pos = i;
	if (min_pos <= a->size / 2)
	{
		i = -1;
		while (++i < min_pos)
			ra(a);
	}
	else
	{
		i = -1;
		while (++i < a->size - min_pos)
			rra(a);
	}
}
