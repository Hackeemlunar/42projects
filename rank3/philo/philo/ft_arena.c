/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arena.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:15:28 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/20 20:30:34 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

t_arena	*arena_create(size_t size)
{
	t_arena	*arena;

#ifdef USING_THREAD_SANITIZER
	arena = (t_arena *)malloc(sizeof(t_arena));
	if (!arena)
		return (NULL);
	arena->buffer = NULL;  // We won't use this when TSan is active
	arena->size = size;
	arena->used = 0;
	return (arena);
#else
	arena = (t_arena *)malloc(sizeof(t_arena));
	if (!arena)
		return (NULL);
	arena->buffer = (char *)malloc(size);
	if (!arena->buffer)
	{
		free(arena);
		return (NULL);
	}
	arena->size = size;
	arena->used = 0;
	return (arena);
#endif
}

void	*arena_alloc(t_arena *arena, size_t size)
{
#ifdef USING_THREAD_SANITIZER
	// When using ThreadSanitizer, bypass the arena and use standard malloc
	void *ptr = malloc(size);
	// Keep track for cleanup (even though we can't truly free until arena destruction)
	arena->used += size;
	return ptr;
#else
	void	*ptr;
	size_t	alignment = 16;
	size_t	padding = 0;

	// Calculate padding needed for alignment
	if (arena->used % alignment != 0)
		padding = alignment - (arena->used % alignment);

	// Check if we have enough space
	if (arena->used + padding + size > arena->size)
		return (NULL);

	// Apply padding to ensure aligned memory
	arena->used += padding;
	ptr = arena->buffer + arena->used;
	arena->used += size;
	return (ptr);
#endif
}

void	arena_reset(t_arena *arena)
{
	// Cannot truly reset when using ThreadSanitizer without leaking memory
#ifndef USING_THREAD_SANITIZER
	arena->used = 0;
#endif
}

void	arena_destroy(t_arena *arena)
{
	if (arena)
	{
#ifdef USING_THREAD_SANITIZER
		// We can't free individual allocations, but we don't need to free the buffer
		free(arena);
#else
		free(arena->buffer);
		free(arena);
#endif
	}
}
