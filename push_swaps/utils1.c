#include "push_swap.h"

void initialize_stacks(t_arena *arena, t_stack *a, t_stack *b, int n)
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