/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:39:44 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/14 17:38:04 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	swap(t_stack *s)
{
	int	tmp;

	if (s->size > 1)
	{
		tmp = s->arr[0];
		s->arr[0] = s->arr[1];
		s->arr[1] = tmp;
	}
}

void	sa(t_stack *a)
{
	swap(a);
}

void	sb(t_stack *b)
{
	swap(b);
}

void	ss(t_stack *a, t_stack *b)
{
	swap(a);
	swap(b);
}
