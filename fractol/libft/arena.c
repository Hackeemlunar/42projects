#include "libft.h"

t_arena	*arena_create(size_t size)
{
	t_arena	*arena;

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
}

void	*arena_alloc(t_arena *arena, size_t size)
{
	void	*ptr;

	if (arena->used + size > arena->size)
		return (NULL);
	ptr = arena->buffer + arena->used;
	arena->used += size;
	return (ptr);
}

void	arena_reset(t_arena *arena)
{
	arena->used = 0;
}

void	arena_destroy(t_arena *arena)
{
	if (arena)
	{
		free(arena->buffer);
		free(arena);
	}
}
