#include "push_swap.h"

void radix_sort(Stack *a, Stack *b)
{
	int max_bits;
	int i_bit;
	int count;
	int i;
	int n;

	max_bits = 0;
	n = a->size;
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
			{
				ra(a);
				if (b->size == 0 && is_sorted_asc(a))
					return;
			}
			else
				pb(b, a);
			i++;
		}
		while (b->size > 0)
			pa(a, b);
		i_bit++;
	}
}

void process_b(Stack *a, Stack *b)
{
    if (b->size > 1)
    {
        int max_iterations = b->size * 2; // Prevent infinite loops
        int count = 0;

        while (!is_sorted_desc(b) && count < max_iterations)
        {
            if (b->arr[0] < b->arr[1])
                sb(b);
            if (b->arr[0] < b->arr[b->size - 1])
                rb(b); // FIXED: Changed rb(a) to rb(b)
            else if (b->arr[0] > b->arr[b->size - 1])
                rrb(b);
            count++; // Prevent infinite looping
        }
    }
}


void process_a(Stack *a, Stack *b)
{
    while (!is_sorted_asc(a))
    {
        if (a->arr[0] > a->arr[1])
            sa(a);
        if (a->arr[0] > a->arr[a->size - 1])
            rra(a);

        // Collect elements into B first, then sort B
        if (a->arr[0] < a->arr[a->size - 1])
            pb(a, b);
    }

    process_b(a, b); // Call once after pushing elements
}


void insertion_sort(Stack *a, Stack *b)
{
	int *a_n;
	int *b_n;

	a_n = a->arr;
	b_n = b->arr;
	process_a(a, b);
	while (b->size > 0)
	{
		pa(a, b);
		process_a(a, b);
	}
}
