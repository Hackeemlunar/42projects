#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft/libft.h"

typedef struct s_stack
{
	int *arr;
	int size;
}	t_stack;

void merge_sort(int *arr, int len);

void swap(t_stack *s)
{
	if (s->size > 1)
	{
		int tmp = s->arr[0];
		s->arr[0] = s->arr[1];
		s->arr[1] = tmp;
	}
}

void sa(t_stack *a)
{
	swap(a);
	ft_putstr_fd("sa\n", 1);
}

void sb(t_stack *b)
{
	swap(b);
	ft_putstr_fd("sb\n", 1);
}

void ss(t_stack *a, t_stack *b)
{
	swap(a);
	swap(b);
	ft_putstr_fd("ss\n", 1);
}

void push(t_stack *dest, t_stack *src)
{
	int tmp;
	int i;

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

void pa(t_stack *a, t_stack *b)
{
	push(a, b);
	ft_putstr_fd("pa\n", 1);
}

void pb(t_stack *b, t_stack *a)
{
	push(b, a);
	ft_putstr_fd("pb\n", 1);
}

void rotate(t_stack *s)
{
	int temp;
	int i;

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

void ra(t_stack *a)
{
	rotate(a);
	ft_putstr_fd("ra\n", 1);
}

void rb(t_stack *b)
{
	rotate(b);
	ft_putstr_fd("rb\n", 1);
}

void rr(t_stack *a, t_stack *b)
{
	rotate(a);
	rotate(b);
	ft_putstr_fd("rr\n", 1);
}

void rev_rotate(t_stack *s)
{
	int i;
	int temp;

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

void rra(t_stack *a)
{
	rev_rotate(a);
	ft_putstr_fd("rra\n", 1);
}

void rrb(t_stack *b)
{
	rev_rotate(b);
	ft_putstr_fd("rrb\n", 1);
}

void rrr(t_stack *a, t_stack *b)
{
	rev_rotate(a);
	rev_rotate(b);
	ft_putstr_fd("rrr\n", 1);
}

void index_stack(int *arr, int *copy, int n)
{
	int i;
	int j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			if (arr[i] == copy[j])
			{
				arr[i] = j;
				break;
			}
			j++;
		}
		i++;
	}
}

int has_duplicates(int *sorted, int n)
{
	int i;

	i = 0;
	while (i < n - 1)
	{
		if (sorted[i] == sorted[i + 1])
			return (1);
		i++;
	}
	return (0);
}

int is_sorted(t_stack *a)
{
	int i;

	i = 0;
	while (i < a->size - 1)
	{
		if (a->arr[i] > a->arr[i + 1])
			return (0);
		i++;
	}
	return (1);
}

void radix_sort(t_stack *a, t_stack *b, int n)
{
	int max_bits;
	int i_bit;
	int count;
	int i;

	max_bits = 0;
	while (((n - 1) >> max_bits) != 0)
		max_bits++;
	i_bit = 0;
	while (i_bit < max_bits)
	{
		count = a->size;
		i = 0;
		while (i < count)
		{
			if (((a->arr[0] >> i_bit) & 1) == 1)
				ra(a);
			else
				pb(b, a);
			i++;
		}
		while (b->size > 0)
			pa(a, b);
		i_bit++;
	}
}

/* --- Error checking functions --- */
int has_error(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-' && i == 0)
			i++;
		else if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int has_overflow(char *str)
{
	long n;

	n = ft_atol(str);
	if (n > 2147483647 || n < -2147483648)
		return (1);
	return (0);
}

void initialize_stacks(t_arena *arena, t_stack *a, t_stack *b, int n)
{
	a->arr = (int *)arena_alloc(arena, n * sizeof(int));
	b->arr = (int *)arena_alloc(arena, n * sizeof(int));
	if (!a->arr)
	{
		arena_destroy(arena);
		exit(EXIT_FAILURE);
	}
	if (!b->arr)
	{
		arena_destroy(arena);
		exit(EXIT_FAILURE);
	}
	a->size = n;
	b->size = 0;
}

static void perform_operations(int *temp, t_stack *a, t_stack *b, int n)
{
	index_stack(a->arr, temp, n);
	radix_sort(a, b, n);
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
	int		i;
	int		*sorted_copy;
	t_stack	a;
	t_stack	b;
	t_arena	*arena;

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
	perform_operations(sorted_copy, &a, &b, (argc - 1));
	return (arena_destroy(arena), 0);
}
