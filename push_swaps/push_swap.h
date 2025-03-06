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
} Stack;

typedef struct s_move_cost
{
	int cost_a;    // Cost to rotate A (positive for ra, negative for rra)
	int cost_b;    // Cost to rotate B (positive for rb, negative for rrb)
	int total;     // Total cost (taking into account possible combined rotations)
	int index_b;   // The index of the candidate element in stack B.
} t_move_cost;

void	sa(Stack *a);
void	sb(Stack *b);
void	ss(Stack *a, Stack *b);
void	pa(Stack *a, Stack *b);
void	pb(Stack *b, Stack *a);
void	ra(Stack *a);
void	rb(Stack *b);
void	rr(Stack *a, Stack *b);
void	rra(Stack *a);
void	rrb(Stack *b);
void	rrr(Stack *a, Stack *b);
void	index_stack(int *arr, int n);
void	merge_sort(int *arr, int len);
void	sort(Stack *a, Stack *b);
void	initialize_stacks(Stack *a, Stack *b, int n);
void	sort_and_cleanup(Stack *a, Stack *b, int n);
int		has_duplicates(int *arr, int n);
int		is_sorted_asc(Stack *a);
int		is_sorted_desc(Stack *a);
int		has_error(char *str);
int		has_overflow(char *str);
void radix_sort(Stack *a, Stack *b);
void insertion_sort(Stack *a, Stack *b);
# endif