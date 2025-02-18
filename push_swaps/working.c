#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft/libft.h"

typedef struct s_stack
{
	int *arr;
	int size;
} Stack;

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
	ft_printf("sa\n");
}

void sb(Stack *b)
{
	swap(b);
	ft_printf("sb\n");
}

void ss(Stack *a, Stack *b)
{
	swap(a);
	swap(b);
	ft_printf("ss\n");
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
	ft_printf("pa\n");
}

void pb(Stack *b, Stack *a)
{
	push(b, a);
	ft_printf("pb\n");
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
	ft_printf("ra\n");
}

void rb(Stack *b)
{
	rotate(b);
	ft_printf("rb\n");
}

void rr(Stack *a, Stack *b)
{
	rotate(a);
	rotate(b);
	ft_printf("rr\n");
}

void rev_rotate(Stack *s)
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

void rra(Stack *a)
{
	rev_rotate(a);
	ft_printf("rra\n");
}

void rrb(Stack *b)
{
	rev_rotate(b);
	ft_printf("rrb\n");
}

void rrr(Stack *a, Stack *b)
{
	rev_rotate(a);
	rev_rotate(b);
	ft_printf("rrr\n");
}

/* --- Utility functions --- */
int cmp_int(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

void index_stack(int *arr, int n)
{
	int *copy;
	int i;
	int j;

	copy = malloc(n * sizeof(int));
	ft_memcpy(copy, arr, n * sizeof(int));
	qsort(copy, n, sizeof(int), cmp_int);
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
	free(copy);
}

int has_duplicates(int *arr, int n)
{
	int i;
	int j;

	i = 0;
	while (i < n)
	{
		j = i + 1;
		while (j < n)
		{
			if (arr[i] == arr[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_sorted(Stack *a)
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

/* --- Sorting Algorithm --- */
void sort_small_stack(Stack *a, Stack *b)
{
	while (a->size > 1)
	{
		if (a->arr[0] > a->arr[1])
			sa(a);
		if (is_sorted(a) && b->size == 0)
			return ;
		pb(b, a);
	}
	while (b->size > 0)
		pa(a, b);
}

void radix_sort(Stack *a, Stack *b, int n)
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
	int n;

	n = ft_atoi(str);
	if (n > 2147483647 || n < -2147483648)
		return (1);
	return (0);
}

void initialize_stacks(Stack *a, Stack *b, int n)
{
	a->arr = malloc(n * sizeof(int));
	b->arr = malloc(n * sizeof(int));
	if (!a->arr)
		exit(EXIT_FAILURE);
	if (!b->arr)
	{
		free(a->arr);
		exit(EXIT_FAILURE);
	}
	a->size = n;
	b->size = 0;
}

void sort_and_cleanup(Stack *a, Stack *b, int n)
{
	index_stack(a->arr, n);
	if (n <= 5)
		sort_small_stack(a, b);
	else
		radix_sort(a, b, n);
	free(a->arr);
	free(b->arr);
}

/* --- Main function --- */
int main(int argc, char **argv)
{
	int		n;
	int		i;
	Stack	a;
	Stack	b;

	if (argc < 2)
		return 0;
	n = argc - 1;
	initialize_stacks(&a, &b, n);
	i = 0;
	while (i < n)
	{
		if (has_error(argv[i + 1]) || has_overflow(argv[i + 1]))
			return (write(2, "Error\n", 6), free(a.arr), free(b.arr), 1);
		a.arr[i] = ft_atoi(argv[i + 1]);
		i++;
	}
	if (has_duplicates(a.arr, n))
		return (write(2, "Error\n", 6), free(a.arr), free(b.arr), 1);
	sort_and_cleanup(&a, &b, n);
	return 0;
}