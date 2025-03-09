#include "push_swap.h"

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