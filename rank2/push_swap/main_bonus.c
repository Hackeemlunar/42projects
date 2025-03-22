/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:11:51 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/19 17:35:17 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

static void	do_instn(char *line, t_stack *a, t_stack *b)
{
	if (ft_strncmp(line, "sa", 2) == 0)
		sa(a);
	else if (ft_strncmp(line, "sb", 2) == 0)
		sb(b);
	else if (ft_strncmp(line, "ss", 2) == 0)
		ss(a, b);
	else if (ft_strncmp(line, "pa", 2) == 0)
		pa(a, b);
	else if (ft_strncmp(line, "pb", 2) == 0)
		pb(b, a);
	else if (ft_strncmp(line, "rra", 3) == 0)
		rra(a);
	else if (ft_strncmp(line, "rrb", 3) == 0)
		rrb(b);
	else if (ft_strncmp(line, "rrr", 3) == 0)
		rrr(a, b);
	else if (ft_strncmp(line, "ra", 2) == 0)
		ra(a);
	else if (ft_strncmp(line, "rb", 2) == 0)
		rb(b);
	else if (ft_strncmp(line, "rr", 2) == 0)
		rr(a, b);
}

static int	validate_oper(char *line)
{
	size_t	len;

	len = ft_strlen(line) - 1;
	if (ft_strncmp(line, "sa", len) == 0 || ft_strncmp(line, "sb", len) == 0
		|| ft_strncmp(line, "ss", len) == 0
		|| ft_strncmp(line, "pa", len) == 0
		|| ft_strncmp(line, "pb", len) == 0
		|| ft_strncmp(line, "rra", len) == 0
		|| ft_strncmp(line, "rrb", len) == 0
		|| ft_strncmp(line, "rrr", len) == 0
		|| ft_strncmp(line, "ra", len) == 0
		|| ft_strncmp(line, "rb", len) == 0
		|| ft_strncmp(line, "rr", len) == 0)
		return (1);
	return (0);
}

static void	perform_operations(t_arena *arena, t_stack *a, t_stack *b)
{
	char	*line;

	line = get_next_line(0);
	while (line)
	{
		if (!validate_oper(line))
		{
			write(2, "Error\n", 6);
			free(line);
			arena_destroy(arena);
			exit(1);
		}
		do_instn(line, a, b);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	if (is_sorted(a) && b->size == 0)
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
}

int	main(int argc, char **argv)
{
	int		i;
	int		*sorted_copy;
	t_stack	a;
	t_stack	b;
	t_arena	*arena;

	if (argc < 2)
		return (0);
	arena = arena_create((argc - 1) * sizeof(int) * 10);
	if (!arena)
		return (write(2, "Error\n", 6), 1);
	initialize_stacks(arena, &a, &b, (argc - 1));
	i = -1;
	while (++i < (argc - 1))
	{
		if (has_error(argv[i + 1]) || has_overflow(argv[i + 1]))
			return (write(2, "Error\n", 6), arena_destroy(arena), 1);
		a.arr[i] = ft_atoi(argv[i + 1]);
	}
	sorted_copy = (int *)arena_alloc(arena, (argc - 1) * sizeof(int) + 1);
	ft_memcpy(sorted_copy, a.arr, (argc - 1) * sizeof(int));
	merge_sort(sorted_copy, (argc - 1));
	if (has_duplicates(sorted_copy, (argc - 1)))
		return (write(2, "Error\n", 6), arena_destroy(arena), 1);
	return (perform_operations(arena, &a, &b), arena_destroy(arena), 0);
}
