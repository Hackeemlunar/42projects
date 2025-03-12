/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:32:11 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/12 23:42:39 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// void radix_sort(t_stack *a, t_stack *b, int n)
// {
// 	int max_bits;
// 	int i_bit;
// 	int count;
// 	int i;

// 	max_bits = 0;
// 	while (((n - 1) >> max_bits) != 0)
// 		max_bits++;
// 	i_bit = 0;
// 	while (i_bit < max_bits)
// 	{
// 		count = a->size;
// 		i = 0;
// 		while (i < count  && !is_sorted(a))
// 		{
// 			if (((a->arr[0] >> i_bit) & 1) == 1)
//                 ra(a);
// 			else
// 			{
//                 pb(b, a);
//                 if (b->size > 1 && b->arr[0] > b->arr[1])
//                 sb(b);
//             }
// 			i++;
// 		}
// 		while (b->size > 0)
// 			pa(a, b);
// 		i_bit++;
// 	}
// }

int sorted_tail_length(t_stack *a)
{
	int i = a->size - 1;
	int count = 1;
	
	while (i > 0 && a->arr[i] > a->arr[i - 1])
	{
		count++;
		i--;
	}
	return count;
}
int sorted_tail_check(t_stack *a)
{
	int sorted_tail;
	int i;

	sorted_tail = 1;  // at least one element at bottom is sorted
	i = a->size - 1;
	while (i > 0 && a->arr[i - 1] < a->arr[i])
	{
		sorted_tail++;
		i--;
	}
	return sorted_tail;
}
// Optimized Radix Sort
void radix_sort(t_stack *a, t_stack *b, int n)
{
	int max_bits = 0;
	int i_bit;
	int i, size, sorted_tail;

	// Find number of bits required
	while ((n - 1) >> max_bits)
		max_bits++;

	i_bit = 0;
	while (i_bit < max_bits)
	{
		size = a->size;
		sorted_tail = sorted_tail_check(a);

		// Limit loop to ignore already sorted bottom elements
		size = a->size - sorted_tail;

		for (i = 0; i < size; i++)
		{
			if (((a->arr[0] >> i_bit) & 1) == 1)
				ra(a);   // Keep number in 'a' if bit is 1
			else
				pb(b, a);  // Push number to 'b' if bit is 0
		}

		// Move everything back from 'b' to 'a'
		while (b->size > 0)
			pa(a, b);

		// Early sorted check (skip remaining bits if sorted)
		if (is_sorted(a))
			break;

		i_bit++;
	}
}

// int find_max_position(t_stack *b)
// {
// 	int max = b->arr[0];
// 	int pos = 0;
// 	for (int i = 1; i < b->size; i++)
// 	{
// 		if (b->arr[i] > max)
// 		{
// 			max = b->arr[i];
// 			pos = i;
// 		}
// 	}
// 	return pos;
// }

// Chunk-based sorting implementation
// void chunk_sort(t_stack *a, t_stack *b, int chunk_count)
// {
// 	int chunk_size = a->size / chunk_count;
// 	int min_idx, max_idx;
// 	int pushed;

// 	for (int chunk = 1; chunk <= chunk_count; chunk++)
// 	{
// 		min_idx = (chunk - 1) * chunk_size;
// 		max_idx = chunk * chunk_size - 1;
// 		if (chunk == chunk_count)
// 			max_idx = a->size - 1;

// 		pushed = 0;
// 		while (pushed < (max_idx - min_idx + 1))
// 		{
// 			if (a->arr[0] >= min_idx && a->arr[0] <= max_idx)
// 			{
// 				pb(b, a);
// 				pushed++;
// 			}
// 			else
// 			{
// 				ra(a);
// 			}
// 		}
// 	}

// 	// Move elements back to 'a' smartly
// 	while (b->size > 0)
// 	{
// 		int max_pos = find_max_position(b);
// 		if (max_pos <= b->size / 2)
// 		{
// 			while (max_pos-- > 0)
// 				rb(b);
// 		}
// 		else
// 		{
// 			max_pos = b->size - max_pos;
// 			while (max_pos-- > 0)
// 				rrb(b);
// 		}
// 		pa(a, b);
// 	}
// }


// void partition(t_stack *a, t_stack *b, int pivot, int high)
// {
//     int j = 0;

//     while (j < high)
//     {
//         if (a->arr[0] <= pivot)
//         {
//             pb(b, a);
//             // Removed rb rotation to save operations
//         }
//         else
//         {
//             if (a->arr[a->size - 1] <= pivot)
//                 rra(a);
//             else
//                 ra(a);
//         }
//         j++;
//     }
// }

// void sort_3(t_stack *s)
// {
// 	int top;
// 	int mid;
// 	int bot;

// 	top = s->arr[0];
// 	mid = s->arr[1];
// 	bot = s->arr[2];
// 	if (top > mid && mid < bot && bot > top)
// 		sa(s);
// 	else if (top > mid && mid > bot && bot < top)
// 	{
// 		sa(s);
// 		rra(s);
// 	}
// 	else if (top > mid && mid < bot && bot < top)
// 		ra(s);
// 	else if (top < mid && mid > bot && bot > top)
// 	{
// 		sa(s);
// 		ra(s);
// 	}
// 	else if (top < mid && mid > bot && bot < top)
// 		rra(s);
// }

// void sort_5(t_stack *a, t_stack *b, int *sorted)
// {
// 	int i;

// 	i = 0;
// 	while (a->size > 3)
// 	{
// 		if (a->arr[0] == sorted[i])
// 		{
// 			pb(b, a);
// 			i++;
// 		}
// 		else if (a->arr[a->size - 1] == sorted[i])
// 			rra(a);
// 		else
// 			ra(a);
// 	}
// 	sort_3(a);
// 	pa(a, b);
// 	pa(a, b);
// }

// int find_smallest(t_stack *a)
// {
//     int i = 0;
//     int smallest = a->arr[0];
//     int index = 0;

//     while (i < a->size)
//     {
//         if (a->arr[i] < smallest)
//         {
//             smallest = a->arr[i];
//             index = i;
//         }
//         i++;
//     }
//     return (index);
// }

// void sort_10(t_stack *a, t_stack *b, int *sorted)
// {
// 	int i = 0;
// 	int smallest = 0;

// 	while (a->size > 5)
// 	{
// 		if (a->arr[0] == sorted[i])
// 		{
// 			pb(b, a);
// 			i++;
// 		}
// 		else if (a->arr[a->size - 1] == sorted[i])
// 			rra(a);
// 		else
// 		{
// 			smallest = find_smallest(a);
// 			if (smallest < a->size / 1.5)
// 				ra(a);
// 			else
// 				rra(a);
// 		}
// 	}

// 	sort_5(a, b, sorted + 5); // Sort the remaining 5 elements

// 	// Push elements back from B to A
// 	while (b->size > 0)
// 		pa(a, b);
// }

// void sort(t_stack *a, t_stack *b, int *sorted)
// {
//     int i = 0;
//     int smallest_pos;

//     if (a->size > 0)
//         smallest_pos = find_smallest(a);

//     while (a->size > 3)
//     {
//         if (a->arr[0] == sorted[i])
//         {
//             pb(b, a);
//             i++;
//             if (a->size > 0)
//                 smallest_pos = find_smallest(a); // Update after removal
//         }
//         else
//         {
//             if (smallest_pos < a->size / 2)
//             {
//                 ra(a);
//                 smallest_pos = (smallest_pos == 0) ? a->size - 1 : smallest_pos - 1;
//             }
//             else
//             {
//                 rra(a);
//                 smallest_pos = (smallest_pos == a->size - 1) ? 0 : smallest_pos + 1;
//             }
//         }
//     }

//     sort_3(a); // Assuming sort_3 is defined elsewhere

//     while (b->size > 0)
//         pa(a, b);
// }

// int find_max_position(t_stack *b)
// {
// 	int max = b->arr[0];
// 	int pos = 0;
// 	for (int i = 1; i < b->size; i++)
// 	{
// 		if (b->arr[i] > max)
// 		{
// 			max = b->arr[i];
// 			pos = i;
// 		}
// 	}
// 	return pos;
// }

// // Helper to find nearest element in chunk from top or bottom
// int find_nearest_in_chunk(t_stack *a, int min_idx, int max_idx)
// {
// 	int top = 0;
// 	int bottom = a->size - 1;
// 	while (top <= bottom)
// 	{
// 		if (a->arr[top] >= min_idx && a->arr[top] <= max_idx)
// 			return top;
// 		if (a->arr[bottom] >= min_idx && a->arr[bottom] <= max_idx)
// 			return bottom;
// 		top++;
// 		bottom--;
// 	}
// 	return -1;
// }

// // Indexing helper functions
// int	find_index(int *arr, int n, int value)
// {
// 	int index = 0;
// 	for (int i = 0; i < n; i++)
// 		if (arr[i] < value)
// 			index++;
// 	return index;
// }

// // Corrected Chunk-based sorting implementation
// void chunk_sort(t_stack *a, t_stack *b, int chunk_count)
// {
// 	// normalize_stack(a);
// 	int chunk_size = a->size / chunk_count;
// 	int min_idx, max_idx, pos;

// 	for (int chunk = 1; chunk <= chunk_count; chunk++)
// 	{
// 		min_idx = (chunk - 1) * chunk_size;
// 		max_idx = chunk * chunk_size - 1;
// 		if (chunk == chunk_count)
// 			max_idx = a->size - 1;

// 		int elements_in_chunk = max_idx - min_idx + 1;

// 		while (elements_in_chunk > 0)
// 		{
// 			pos = find_nearest_in_chunk(a, min_idx, max_idx);
// 			if (pos == -1)
// 				break;
// 			if (pos <= a->size / 2)
// 			{
// 				while (pos-- > 0)
// 					ra(a);
// 			}
// 			else
// 			{
// 				pos = a->size - pos;
// 				while (pos-- > 0)
// 					rra(a);
// 			}
// 			pb(b, a);
// 			elements_in_chunk--;
// 		}
// 	}

// 	// Final step correction: Ensure the largest elements are sorted when pushed back
// 	while (b->size > 0)
// 	{
// 		int max_pos = find_max_position(b);
// 		if (max_pos <= b->size / 2)
// 			while (max_pos-- > 0)
// 				rb(b);
// 		else
// 		{
// 			max_pos = b->size - max_pos;
// 			while (max_pos-- > 0)
// 				rrb(b);
// 		}
// 		pa(a, b);
// 	}
// }

/*            working well       */

// int find_max_position(t_stack *b) {
//     int max = b->arr[0];
//     int pos = 0;
//     for (int i = 1; i < b->size; i++) {
//         if (b->arr[i] > max) {
//             max = b->arr[i];
//             pos = i;
//         }
//     }
//     return pos;
// }

// int find_nearest_in_chunk(t_stack *a, int min_val, int max_val) {
//     int top = 0;
//     int bottom = a->size - 1;
//     while (top <= bottom) {
//         if (a->arr[top] >= min_val && a->arr[top] <= max_val)
//             return top;
//         if (a->arr[bottom] >= min_val && a->arr[bottom] <= max_val)
//             return bottom;
//         top++;
//         bottom--;
//     }
//     return -1;
// }

// int find_index(int *arr, int n, int value) {
//     int index = 0;
//     for (int i = 0; i < n; i++)
//         if (arr[i] < value)
//             index++;
//     return index;
// }

// void chunk_sort(t_stack *a, t_stack *b, int chunk_count)
// {
//     int chunk_size = a->size / chunk_count;
//     int remaining = a->size % chunk_count;

//     for (int chunk = 0; chunk < chunk_count; chunk++) {
//         int min_val = chunk * chunk_size;
//         int max_val = (chunk + 1) * chunk_size - 1;
//         if (chunk == chunk_count - 1)
//             max_val += remaining;

//         int elements_in_chunk = max_val - min_val + 1;
//         while (elements_in_chunk > 0) {
//             int pos = find_nearest_in_chunk(a, min_val, max_val);
//             if (pos == -1) break;

//             if (pos <= a->size / 2) {
//                 for (int i = 0; i < pos; i++)
//                     ra(a);
//             } else {
//                 pos = a->size - pos;
//                 for (int i = 0; i < pos; i++)
//                     rra(a);
//             }
//             pb(b, a);
//             elements_in_chunk--;
//         }
//     }

//     // Optimized final phase with smart rotations
//     while (b->size > 0) {
//         int max_pos = find_max_position(b);
//         if (max_pos <= b->size / 2) {
//             for (int i = 0; i < max_pos; i++)
//                 rb(b);
//         } else {
//             int rotations = b->size - max_pos;
//             for (int i = 0; i < rotations; i++)
//                 rrb(b);
//         }
//         pa(a, b);
//     }
// }

// int is_sorted(t_stack *s) {
//     for (int i = 0; i < s->size - 1; i++)
//         if (s->arr[i] > s->arr[i + 1])
//             return 0;
//     return 1;
// }

/*      535 operations for 100    */
// int find_max(t_stack *s) {
//     int max = s->arr[0];
//     for (int i = 1; i < s->size; i++)
//         if (s->arr[i] > max)
//             max = s->arr[i];
//     return max;
// }

// int find_min(t_stack *s) {
//     int min = s->arr[0];
//     for (int i = 1; i < s->size; i++)
//         if (s->arr[i] < min)
//             min = s->arr[i];
//     return min;
// }

// // Cost calculation functions
// typedef struct s_rotation {
//     int ra;
//     int rra;
//     int rb;
//     int rrb;
//     int total;
// } t_rotation;

// int find_target_position(t_stack *b, int value) {
//     int max = find_max(b);
//     int min = find_min(b);
    
//     if (value > max) return 0;
//     if (value < min) {
//         int max_pos = 0;
//         while (b->arr[max_pos] != max) max_pos++;
//         return (max_pos + 1) % b->size;
//     }
    
//     int pos = 0;
//     while (pos < b->size - 1 && !(b->arr[pos] > value && value > b->arr[(pos + 1) % b->size]))
//         pos++;
//     return (pos + 1) % b->size;
// }

// t_rotation calculate_cost(t_stack *a, t_stack *b, int a_pos) {
//     t_rotation cost = {0};
//     int value = a->arr[a_pos];
//     int target_pos = find_target_position(b, value);
    
//     // Calculate A rotations
//     cost.ra = a_pos;
//     cost.rra = a->size - a_pos;
    
//     // Calculate B rotations
//     cost.rb = target_pos;
//     cost.rrb = b->size - target_pos;
    
//     // Calculate total cost with optimizations
//     cost.total = INT_MAX;
//     if (cost.ra + cost.rb - (cost.ra > 0 && cost.rb > 0 ? 1 : 0) < cost.total)
//         cost.total = cost.ra + cost.rb - (cost.ra > 0 && cost.rb > 0 ? 1 : 0);
//     if (cost.ra + cost.rrb < cost.total)
//         cost.total = cost.ra + cost.rrb;
//     if (cost.rra + cost.rb < cost.total)
//         cost.total = cost.rra + cost.rb;
//     if (cost.rra + cost.rrb - (cost.rra > 0 && cost.rrb > 0 ? 1 : 0) < cost.total)
//         cost.total = cost.rra + cost.rrb - (cost.rra > 0 && cost.rrb > 0 ? 1 : 0);
    
//     return cost;
// }

// // Rotation execution
// void execute_rotations(t_stack *a, t_stack *b, t_rotation cost) {
//     int common_rotations = 0;
    
//     // Find optimal rotation combination
//     if (cost.ra + cost.rb - (cost.ra > 0 && cost.rb > 0 ? 1 : 0) == cost.total) {
//         common_rotations = (cost.ra < cost.rb) ? cost.ra : cost.rb;
//         for (int i = 0; i < common_rotations; i++) rr(a, b);
//         for (int i = common_rotations; i < cost.ra; i++) ra(a);
//         for (int i = common_rotations; i < cost.rb; i++) rb(b);
//     }
//     else if (cost.ra + cost.rrb == cost.total) {
//         for (int i = 0; i < cost.ra; i++) ra(a);
//         for (int i = 0; i < cost.rrb; i++) rrb(b);
//     }
//     else if (cost.rra + cost.rb == cost.total) {
//         for (int i = 0; i < cost.rra; i++) rra(a);
//         for (int i = 0; i < cost.rb; i++) rb(b);
//     }
//     else {
//         common_rotations = (cost.rra < cost.rrb) ? cost.rra : cost.rrb;
//         for (int i = 0; i < common_rotations; i++) rrr(a, b);
//         for (int i = common_rotations; i < cost.rra; i++) rra(a);
//         for (int i = common_rotations; i < cost.rrb; i++) rrb(b);
//     }
// }

// // Main algorithm
// void turk_sort(t_stack *a, t_stack *b) {
//     // Initial push of two elements
//     pb(b, a);
//     pb(b, a);
    
//     // Main sorting phase
//     while (a->size > 3 && !is_sorted(a)) {
//         t_rotation min_cost = {.total = INT_MAX};
//         int best_index = 0;
        
//         // Find element with minimal rotation cost
//         for (int i = 0; i < a->size; i++) {
//             t_rotation current = calculate_cost(a, b, i);
//             if (current.total < min_cost.total) {
//                 min_cost = current;
//                 best_index = i;
//             }
//         }
        
//         // Execute rotations and push
//         execute_rotations(a, b, min_cost);
//         pb(b, a);
//     }
    
//     // Sort last 3 elements in A
//     if (a->size == 3) {
//         if (a->arr[0] > a->arr[1] && a->arr[0] < a->arr[2]) sa(a);
//         else if (a->arr[0] > a->arr[1] && a->arr[1] > a->arr[2]) { sa(a); rra(a); }
//         else if (a->arr[0] > a->arr[2] && a->arr[2] > a->arr[1]) ra(a);
//         else if (a->arr[2] > a->arr[0] && a->arr[0] > a->arr[1]) sa(a);
//         else if (a->arr[1] > a->arr[2] && a->arr[2] > a->arr[0]) rra(a);
//     }
    
//     // Push back to A with optimizations
//     while (b->size > 0) {
//         int value = b->arr[0];
//         int target_pos = 0;
        
//         // Find correct position in A
//         while (target_pos < a->size && a->arr[target_pos] < value)
//             target_pos++;
            
//         // Rotate A to correct position
//         if (target_pos <= a->size / 2) {
//             for (int i = 0; i < target_pos; i++) ra(a);
//         } else {
//             for (int i = 0; i < a->size - target_pos; i++) rra(a);
//         }
        
//         pa(a, b);
//     }
    
//     // Final rotation to minimum element
//     int min_pos = 0;
//     for (int i = 0; i < a->size; i++)
//         if (a->arr[i] < a->arr[min_pos])
//             min_pos = i;
            
//     if (min_pos <= a->size / 2)
//         for (int i = 0; i < min_pos; i++) ra(a);
//     else
//         for (int i = 0; i < a->size - min_pos; i++) rra(a);
// }


void sort_large_stack(t_stack *a, t_stack *b, int *sorted, int n)
{
    // Adjusted pivots for better partitioning
    // int pivot1 = sorted[n / 12];
    // int pivot2 = sorted[n / 10];
    // int pivot3 = sorted[n / 8];
    // int pivot4 = sorted[n / 6];
    // int pivot5 = sorted[n / 4];
    // int pivot6 = sorted[n / 2];

    // partition(a, b, pivot1, n);
    // partition(a, b, pivot2, n);
	// partition(a, b, pivot3, n);
	// partition(a, b, pivot4, n / 6);
	// partition(a, b, pivot5, n);
	// partition(a, b, pivot6, n / 2);

    // while (b->size > 0)
    //     pa(a, b);

    // sort(a, b, sorted);
	(void)sorted;
    (void)n;
	// radix_sort(a, b, n);
    // chunk_sort(a, b, 20);
    turk_sort(a,b);
}
