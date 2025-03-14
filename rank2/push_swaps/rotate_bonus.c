/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:40:42 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/14 16:45:31 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	rotate(t_stack *s)
{
	int	temp;
	int	i;

	if (s->size > 0)
	{
		temp = s->arr[0];
		i = 0;
		while (i < s->size - 1)
		{
			s->arr[i] = s->arr[i + 1];
			i++;
		}
		s->arr[s->size - 1] = temp;
	}
}

void	ra(t_stack *a)
{
	rotate(a);
}

void	rb(t_stack *b)
{
	rotate(b);
}

void	rr(t_stack *a, t_stack *b)
{
	rotate(a);
	rotate(b);
}
