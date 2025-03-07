// #include "push_swap.h"

typedef struct s_stack
{
	int *arr;
	int size;
} t_stack;

void radix_sort(t_stack *a, t_stack *b)
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

void process_b(t_stack *a, t_stack *b)
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

void sort_a(t_stack *a, t_stack *b, int n) {
    while (a->size > 0) {
        if (a->size > 1 && a->arr[a->size - 1] > a->arr[a->size - 2]) {
            sa(a);
        }

        if (a->size > 1 && a->arr[a->size - 1] > a->arr[0]) {
            rra(a);
        } else {
            pb(a, b);
        }

        if (b->size > 1) {
            if (b->arr[b->size - 1] < b->arr[b->size - 2]) {
                if(b->arr[b->size -1] < b->arr[0]){
                    rb(b);
                } else{
                    sb(b);
                }
            }
        }

        if (b->size > 1 && b->arr[b->size - 1] < b->arr[0]) {
            rrb(b);
        }
    }
}