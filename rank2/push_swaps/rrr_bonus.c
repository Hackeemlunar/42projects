/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrr_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:40:48 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/14 16:43:35 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	rev_rotate(t_stack *s)
{
	int	i;
	int	temp;

	temp = 0;
	if (s->size > 0)
	{
		temp = s->arr[s->size - 1];
		i = s->size - 1;
		while (i > 0)
		{
			s->arr[i] = s->arr[i - 1];
			i--;
		}
		s->arr[0] = temp;
	}
}

void	rra(t_stack *a)
{
	rev_rotate(a);
}

void	rrb(t_stack *b)
{
	rev_rotate(b);
}

void	rrr(t_stack *a, t_stack *b)
{
	rev_rotate(a);
	rev_rotate(b);
}
