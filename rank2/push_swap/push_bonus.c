/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:40:31 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/14 17:39:23 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	push(t_stack *dest, t_stack *src)
{
	int	tmp;
	int	i;

	if (src->size > 0)
	{
		tmp = src->arr[0];
		i = 0;
		while (i < src->size - 1)
		{
			src->arr[i] = src->arr[i + 1];
			i++;
		}
		src->size--;
		i = dest->size;
		while (i > 0)
		{
			dest->arr[i] = dest->arr[i - 1];
			i--;
		}
		dest->arr[0] = tmp;
		dest->size++;
	}
}

void	pa(t_stack *a, t_stack *b)
{
	push(a, b);
}

void	pb(t_stack *b, t_stack *a)
{
	push(b, a);
}
