/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:32:11 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/09 20:53:00 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		while (i < count && !is_sorted(a))
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

void radix_sort1(t_stack *a, t_stack *b, int n)
{
    int max_bits;
    int i_bit;
    int i;
    int count_ones;
    int count;

    max_bits = 0;
    while (((n - 1) >> max_bits) != 0)
        max_bits++;

    i_bit = 0;
    while (i_bit < max_bits)
    {
        // Count numbers with bit 1 at current position
        count_ones = 0;
        i = 0;
        while (i < a->size)
        {
            if ((a->arr[i] >> i_bit) & 1)
                count_ones++;
            i++;
        }

        // Skip this bit position if all numbers have same bit value
        if (count_ones == 0 || count_ones == a->size)
        {
            i_bit++;
            continue;
        }

        // Choose whether to push 1s or 0s based on which group is smaller
        int push_ones = (count_ones <= a->size - count_ones);

        count = a->size;
        i = 0;
        while (i < count && !is_sorted(a))
        {
            int bit = (a->arr[0] >> i_bit) & 1;
            if ((bit == 1 && push_ones) || (bit == 0 && !push_ones))
                pb(b, a);
            else
                ra(a);
            i++;
        }

        while (b->size > 0)
            pa(a, b);

        i_bit++;
    }
}

void partition(t_stack *a, t_stack *b, int pivot, int high)
{
    int j = 0;

    while (j < high)
    {
        if (a->arr[0] <= pivot)
        {
            pb(b, a);
            // Removed rb rotation to save operations
        }
        else
        {
            if (a->arr[a->size - 1] <= pivot)
                rra(a);
            else
                ra(a);
        }
        j++;
    }
}

void sort_3(t_stack *s)
{
	int top;
	int mid;
	int bot;

	top = s->arr[0];
	mid = s->arr[1];
	bot = s->arr[2];
	if (top > mid && mid < bot && bot > top)
		sa(s);
	else if (top > mid && mid > bot && bot < top)
	{
		sa(s);
		rra(s);
	}
	else if (top > mid && mid < bot && bot < top)
		ra(s);
	else if (top < mid && mid > bot && bot > top)
	{
		sa(s);
		ra(s);
	}
	else if (top < mid && mid > bot && bot < top)
		rra(s);
}

void sort_5(t_stack *a, t_stack *b, int *sorted)
{
	int i;

	i = 0;
	while (a->size > 3)
	{
		if (a->arr[0] == sorted[i])
		{
			pb(b, a);
			i++;
		}
		else if (a->arr[a->size - 1] == sorted[i])
			rra(a);
		else
			ra(a);
	}
	sort_3(a);
	pa(a, b);
	pa(a, b);
}

int find_smallest(t_stack *a)
{
    int i = 0;
    int smallest = a->arr[0];
    int index = 0;

    while (i < a->size)
    {
        if (a->arr[i] < smallest)
        {
            smallest = a->arr[i];
            index = i;
        }
        i++;
    }
    return (index);
}

void sort_10(t_stack *a, t_stack *b, int *sorted)
{
	int i = 0;
	int smallest = 0;

	while (a->size > 5)
	{
		if (a->arr[0] == sorted[i])
		{
			pb(b, a);
			i++;
		}
		else if (a->arr[a->size - 1] == sorted[i])
			rra(a);
		else
		{
			smallest = find_smallest(a);
			if (smallest < a->size / 1.5)
				ra(a);
			else
				rra(a);
		}
	}

	sort_5(a, b, sorted + 5); // Sort the remaining 5 elements

	// Push elements back from B to A
	while (b->size > 0)
		pa(a, b);
}

void sort(t_stack *a, t_stack *b, int *sorted)
{
    int i = 0;
    int smallest_pos;

    if (a->size > 0)
        smallest_pos = find_smallest(a);

    while (a->size > 3)
    {
        if (a->arr[0] == sorted[i])
        {
            pb(b, a);
            i++;
            if (a->size > 0)
                smallest_pos = find_smallest(a); // Update after removal
        }
        else
        {
            if (smallest_pos < a->size / 2)
            {
                ra(a);
                smallest_pos = (smallest_pos == 0) ? a->size - 1 : smallest_pos - 1;
            }
            else
            {
                rra(a);
                smallest_pos = (smallest_pos == a->size - 1) ? 0 : smallest_pos + 1;
            }
        }
    }

    sort_3(a); // Assuming sort_3 is defined elsewhere

    while (b->size > 0)
        pa(a, b);
}

void sort_large_stack(t_stack *a, t_stack *b, int *sorted, int n)
{
    // Adjusted pivots for better partitioning
    // int pivot1 = sorted[n / 12];
    // int pivot2 = sorted[n / 10];
    // int pivot3 = sorted[n / 8];
    int pivot4 = sorted[n / 6];
    // int pivot5 = sorted[n / 4];
    int pivot6 = sorted[n / 2];

    // partition(a, b, pivot1, n);
    // partition(a, b, pivot2, n);
	// partition(a, b, pivot3, n);
	partition(a, b, pivot4, n);
	// partition(a, b, pivot5, n);
	partition(a, b, pivot6, n);

    while (b->size > 0)
        pa(a, b);

    sort(a, b, sorted);
	// (void)sorted;
	// radix_sort(a, b, n);
}
