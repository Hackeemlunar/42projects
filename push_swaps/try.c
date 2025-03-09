#include "push_swap.h"

static void perform_operations(int *temp, t_stack *a, t_stack *b, int n)
{
	index_stack(a->arr, temp, n);
	radix_sort(a, b, n);
	// sort(a, b);
}

static int build_stack_a(t_arena *arena, char **argv, int argc, t_stack *a)
{
	int i;

	i = -1;
	while (++i < (argc - 1))
	{
		if (has_error(argv[i + 1]) || has_overflow(argv[i + 1]))
			return (write(2, "Error\n", 6), arena_destroy(arena), 0);
		a->arr[i] = ft_atoi(argv[i + 1]);
	}
	return (1);
}

/* --- Main function --- */
int main(int argc, char **argv)
{
	int *sorted_copy;
	t_stack a;
	t_stack b;
	t_arena *arena;

	if (argc < 2)
		return (0);
	arena = arena_create((argc - 1) * sizeof(int) * 10);
	if (!arena)
		return (write(2, "Error\n", 6), 1);
	initialize_stacks(arena, &a, &b, (argc - 1));
	if (!(build_stack_a(arena, argv, argc, &a)))
		return (1);
	sorted_copy = (int *)arena_alloc(arena, (argc - 1) * sizeof(int) + 1);
	if (!sorted_copy)
		return (write(2, "Error\n", 6), arena_destroy(arena), 1);
	ft_memcpy(sorted_copy, a.arr, (argc - 1) * sizeof(int));
	merge_sort(sorted_copy, (argc - 1));
	if (has_duplicates(sorted_copy, (argc - 1)))
		return (write(2, "Error\n", 6), arena_destroy(arena), 1);
	if (is_sorted(&a))
		return (0);
	perform_operations(sorted_copy, &a, &b, (argc - 1));
	return (arena_destroy(arena), 0);
}
