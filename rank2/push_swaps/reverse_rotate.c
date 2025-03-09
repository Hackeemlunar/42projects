/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:32:04 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/09 20:51:43 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rev_rotate(t_stack *s)
{
	int	i;
	int	temp;

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
	ft_putstr_fd("rra\n", 1);
}

void	rrb(t_stack *b)
{
	rev_rotate(b);
	ft_putstr_fd("rrb\n", 1);
}

void	rrr(t_stack *a, t_stack *b)
{
	rev_rotate(a);
	rev_rotate(b);
	ft_putstr_fd("rrr\n", 1);
}
