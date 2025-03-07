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

int find_insert_position(t_stack *a, int value)
{
    int i = 0;
    while (i < a->size - 1)
    {
        if (a->arr[i] < value && a->arr[i + 1] > value)
            return i + 1; // Insert between a[i] and a[i+1]
        i++;
    }
    return 0; // If no suitable position, insert at the top
}

int compute_rotate_cost(t_stack *a, int pos)
{
    if (pos <= a->size / 2)
        return pos; // `ra` is cheaper
    return pos - a->size; // `rra` is cheaper
}

int find_sorted_position(t_stack *a)
{
    int i = 0;
    int min_index = 0;
    int min_value = a->arr[0];

    while (i < a->size)
    {
        if (a->arr[i] < min_value)
        {
            min_value = a->arr[i];
            min_index = i;
        }
        i++;
    }
    return min_index; // Rotate `a` so the smallest value is at the top
}


void move_b_to_a(t_stack *a, t_stack *b)
{
    while (b->size > 0)
    {
        int pos = find_insert_position(a, b->arr[0]);  // Find where b[0] belongs in a
        int rotate_cost = compute_rotate_cost(a, pos); // Calculate cheapest rotation

        // Perform the cheapest rotation to bring insert position to the top
        if (rotate_cost > 0)
            while (rotate_cost-- > 0)
                ra(a);
        else
            while (rotate_cost++ < 0)
                rra(a);

        // Push the element to 'a'
        pa(a, b);

        // Look ahead at the next element in 'b' (if available)
        if (b->size > 0)
        {
            int next_pos = find_insert_position(a, b->arr[0]);
            int next_rotate_cost = compute_rotate_cost(a, next_pos);

            // If the next element is already close to its position, delay rotation
            if (abs(next_rotate_cost) > (a->size / 2))
            {
                // If next rotate is far, rotate 'a' back to sorted state
                int sorted_pos = find_sorted_position(a);
                int sort_cost = compute_rotate_cost(a, sorted_pos);
                if (sort_cost > 0)
                    while (sort_cost-- > 0)
                        ra(a);
                else
                    while (sort_cost++ < 0)
                        rra(a);
            }
        }
    }
}

void sort_a(t_stack *a, t_stack *b, int n)
{
    int i = 0;
    while (i < n && a->size > 0)
    {
        // Step 1: Sort 'a' before pushing to 'b'
        if (a->size > 1 && a->arr[0] > a->arr[1])
            sa(a);
        
        if (a->size > 1 && a->arr[0] > a->arr[a->size - 1])
            rra(a);
        else
            pb(a, b);

        // Step 2: Keep 'b' in descending order
        if (b->size > 1)
        {
            if (b->arr[0] < b->arr[1])
                sb(b);
            if (b->arr[0] < b->arr[b->size - 1])
                rb(b);
        }
    }
}

