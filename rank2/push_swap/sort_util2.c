/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_util2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:14:11 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/16 21:52:07 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_common_forward(t_stack *src, t_stack *dst, t_rotation cost)
{
	int	common;
	int	i;

	common = cost.rb;
	if (cost.ra < common)
		common = cost.ra;
	i = 0;
	while (i < common)
	{
		rr(dst, src);
		i++;
	}
	i = 0;
	while (i < cost.rb - common)
	{
		rb(src);
		i++;
	}
	i = 0;
	while (i < cost.ra - common)
	{
		ra(dst);
		i++;
	}
}

void	rotate_forward_reverse(t_stack *src, t_stack *dst, t_rotation cost)
{
	int	i;

	i = 0;
	while (i < cost.rb)
	{
		rb(src);
		i++;
	}
	i = 0;
	while (i < cost.rra)
	{
		rra(dst);
		i++;
	}
}

void	rotate_reverse_forward(t_stack *src, t_stack *dst, t_rotation cost)
{
	int	i;

	i = 0;
	while (i < cost.rrb)
	{
		rrb(src);
		i++;
	}
	i = 0;
	while (i < cost.ra)
	{
		ra(dst);
		i++;
	}
}

void	rotate_common_reverse(t_stack *src, t_stack *dst, t_rotation cost)
{
	int	common;
	int	i;

	common = cost.rrb;
	if (cost.rra < common)
		common = cost.rra;
	i = 0;
	while (i < common)
	{
		rrr(dst, src);
		i++;
	}
	i = 0;
	while (i < cost.rrb - common)
	{
		rrb(src);
		i++;
	}
	i = 0;
	while (i < cost.rra - common)
	{
		rra(dst);
		i++;
	}
}

void	exec_rot_transfer(t_stack *src, t_stack *dst, t_rotation cost)
{
	if (cost.rot_type == FORWARD_FORWARD)
	{
		rotate_common_forward(src, dst, cost);
	}
	else if (cost.rot_type == FORWARD_REVERSE)
	{
		rotate_forward_reverse(src, dst, cost);
	}
	else if (cost.rot_type == REVERSE_FORWARD)
	{
		rotate_reverse_forward(src, dst, cost);
	}
	else if (cost.rot_type == REVERSE_REVERSE)
	{
		rotate_common_reverse(src, dst, cost);
	}
}
