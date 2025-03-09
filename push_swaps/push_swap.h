#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "libft/libft.h"

typedef struct s_stack
{
	int *arr;
	int size;
} t_stack;

typedef struct s_move_cost
{
	int cost_a;    // Cost to rotate A (positive for ra, negative for rra)
	int cost_b;    // Cost to rotate B (positive for rb, negative for rrb)
	int total;     // Total cost (taking into account possible combined rotations)
	int index_b;   // The index of the candidate element in stack B.
} t_move_cost;

void	sa(t_stack *a);
void	sb(t_stack *b);
void	ss(t_stack *a, t_stack *b);
void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *b, t_stack *a);
void	ra(t_stack *a);
void	rb(t_stack *b);
void	rr(t_stack *a, t_stack *b);
void	rra(t_stack *a);
void	rrb(t_stack *b);
void	rrr(t_stack *a, t_stack *b);
void	merge_sort(int *arr, int len);
void	radix_sort(t_stack *a, t_stack *b, int n);
void	index_stack(int *arr, int *copy, int n);
int		has_duplicates(int *sorted, int n);
int		is_sorted(t_stack *a);
int		has_error(char *str);
int		has_overflow(char *str);
void	initialize_stacks(t_arena *arena, t_stack *a, t_stack *b, int n);
# endif