/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:47:01 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/09 20:49:45 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	initialize_stacks(t_arena *arena, t_stack *a, t_stack *b, int n)
{
	a->arr = (int *)arena_alloc(arena, n * sizeof(int));
	b->arr = (int *)arena_alloc(arena, n * sizeof(int));
	if (!a->arr || !b->arr)
	{
		arena_destroy(arena);
		exit(EXIT_FAILURE);
	}
	a->size = n;
	b->size = 0;
}
