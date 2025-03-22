/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:31:52 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/22 20:22:45 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "../libft/libft.h"

typedef struct s_stack
{
	int	*arr;
	int	size;
}			t_stack;

typedef enum e_rot_type
{
	FORWARD_FORWARD,
	FORWARD_REVERSE,
	REVERSE_FORWARD,
	REVERSE_REVERSE
}		t_rot_type;

typedef struct s_rotation
{
	int			rb;
	int			rrb;
	int			ra;
	int			rra;
	int			total;
	t_rot_type	rot_type;
}			t_rotation;

void		sa(t_stack *a);
void		sb(t_stack *b);
void		ss(t_stack *a, t_stack *b);
void		pa(t_stack *a, t_stack *b);
void		pb(t_stack *b, t_stack *a);
void		ra(t_stack *a);
void		rb(t_stack *b);
void		rr(t_stack *a, t_stack *b);
void		rra(t_stack *a);
void		rrb(t_stack *b);
void		rrr(t_stack *a, t_stack *b);
void		merge_sort(int *arr, int len);
void		index_stack(int *arr, int *copy, int n);
int			has_duplicates(int *sorted, int n);
int			is_sorted(t_stack *a);
int			has_error(char *str);
int			has_overflow(char *str);
void		sort_3(t_stack *a);
void		initialize_stacks(t_arena *arena, t_stack *a, t_stack *b, int n);
void		sort(t_stack *a, t_stack *b);
int			min(int *arr, int n);
int			find_target_position(t_stack *dst, int value);
void		exec_rot_transfer(t_stack *src, t_stack *dst, t_rotation cost);
void		align_and_insert(t_stack *a, t_stack *b);
t_rotation	calc_cost_transfer(t_stack *src, t_stack *dst, int src_index);
#endif