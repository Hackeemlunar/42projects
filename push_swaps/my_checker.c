#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft/libft.h"

typedef struct s_stack
{
	int *arr;
	int size;
} Stack;

void merge_sort(int *arr, int len);

/* --- Operation functions --- */
void swap(Stack *s)
{
	if (s->size > 1)
	{
		int tmp = s->arr[0];
		s->arr[0] = s->arr[1];
		s->arr[1] = tmp;
	}
}

void sa(Stack *a)
{
	swap(a);
}

void sb(Stack *b)
{
	swap(b);
}

void ss(Stack *a, Stack *b)
{
	swap(a);
	swap(b);
}

void push(Stack *dest, Stack *src)
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

void pa(Stack *a, Stack *b)
{
	push(a, b);
}

void pb(Stack *b, Stack *a)
{
	push(b, a);
}

void rotate(Stack *s)
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

void ra(Stack *a)
{
	rotate(a);
}

void rb(Stack *b)
{
	rotate(b);
}

void rr(Stack *a, Stack *b)
{
	rotate(a);
	rotate(b);
}

void rev_rotate(Stack *s)
{
	int i;
	int temp;

	temp = 0;
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

void rra(Stack *a)
{
	rev_rotate(a);
}

void rrb(Stack *b)
{
	rev_rotate(b);
}

void rrr(Stack *a, Stack *b)
{
	rev_rotate(a);
	rev_rotate(b);
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

int is_sorted(Stack *a)
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

void initialize_stacks(t_arena *arena, Stack *a, Stack *b, int n)
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

static void perform_operations(Stack *a, Stack *b, int n)
{
	char *line;

	line = get_next_line(0);
	while (ft_strncmp(line, "exit", 4) != 0)
	{
		if (ft_strncmp(line, "sa", 2) == 0)
			sa(a);
		else if (ft_strncmp(line, "sb", 2) == 0)
			sb(b);
		else if (ft_strncmp(line, "ss", 2) == 0)
			ss(a, b);
		else if (ft_strncmp(line, "pa", 2) == 0)
			pa(a, b);
		else if (ft_strncmp(line, "pb", 2) == 0)
			pb(b, a);
		else if (ft_strncmp(line, "rra", 3) == 0)
			rra(a);
		else if (ft_strncmp(line, "rrb", 3) == 0)
			rrb(b);
		else if (ft_strncmp(line, "rrr", 3) == 0)
			rrr(a, b);
		else if (ft_strncmp(line, "ra", 2) == 0)
			ra(a);
		else if (ft_strncmp(line, "rb", 2) == 0)
			rb(b);
		else if (ft_strncmp(line, "rr", 2) == 0)
			rr(a, b);
		else
			return (ft_putstr_fd("Error\n", 2));
		free(line);
		line = get_next_line(0);
	}
	free(line);
	if (is_sorted(a) && b->size == 0)
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
}

int main(int argc, char **argv)
{
	int i;
	int *sorted_copy;
	Stack a;
	Stack b;
	t_arena *arena;

	if (argc < 2)
		return (0);
	arena = arena_create((argc - 1) * sizeof(int) * 10);
	if (!arena)
		return (write(2, "Error\n", 6), 1);
	initialize_stacks(arena, &a, &b, (argc - 1));
	i = 0;
	while (i < (argc - 1))
	{
		if (has_error(argv[i + 1]) || has_overflow(argv[i + 1]))
			return (write(2, "Error\n", 6), arena_destroy(arena), 1);
		a.arr[i] = ft_atoi(argv[i + 1]);
		i++;
	}
	sorted_copy = (int *)arena_alloc(arena, (argc - 1) * sizeof(int) + 1);
	ft_memcpy(sorted_copy, a.arr, (argc - 1) * sizeof(int));
	merge_sort(sorted_copy, (argc - 1));
	if (has_duplicates(sorted_copy, (argc - 1)))
		return (write(2, "Error\n", 6), arena_destroy(arena), 1);
	perform_operations(&a, &b, (argc - 1));
	return (arena_destroy(arena), 0);
}
