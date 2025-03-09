#include "push_swap.h"

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
