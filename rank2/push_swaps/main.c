/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:32:21 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/12 22:24:12 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void perform_operations(int *temp, t_stack *a, t_stack *b, int n)
{
	index_stack(a->arr, temp, n);
	sort(a, b);
}

static size_t count_words(char **s, char c, int argc)
{
	size_t count;
	int in_word;
	int i;

	if (argc > 2)
		return (argc - 1);
	count = 0;
	in_word = 0;
	i = 0;
	while ((s[1][i]))
	{
		if ((s[1][i]) != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if ((s[1][i]) == c)
			in_word = 0;
		i++;
	}
	return (count);
}

static int build_stack_a(t_arena *arena, char **argv, int argc, t_stack *a)
{
	int i;
	int j;
	int in_word;

	i = -1;
	in_word = 0;
	j = 0;
	if (argc == 2)
	{
		while (argv[1][++i])
		{
			if (argv[1][i] != ' ' && in_word == 0)
			{
				in_word = 1;
				if (has_error(&argv[1][i]) || has_overflow(&argv[1][i]))
					return (write(2, "Error\n", 6), arena_destroy(arena), 0);
				a->arr[j++] = ft_atoi(&argv[1][i]);
			}
			else if (argv[1][i] == ' ')
				in_word = 0;
		}
	}
	else
	{
		while (++i < (argc - 1))
		{
			if (has_error(argv[i + 1]) || has_overflow(argv[i + 1]))
				return (write(2, "Error\n", 6), arena_destroy(arena), 0);
			a->arr[i] = ft_atoi(argv[i + 1]);
		}
	}
	return (1);
}

/* --- Main function --- */
int main(int argc, char **argv)
{
	int *sorted_copy;
	t_stack a;
	t_stack b;
	t_arena *arena;

	if (argc == 1 || count_words(argv, ' ', argc) < 2)
		return (1);
	arena = arena_create(1024 * 1024);
	if (!arena)
		return (write(2, "Error\n", 6), 1);
	initialize_stacks(arena, &a, &b, count_words(argv, ' ', argc));
	if (!(build_stack_a(arena, argv, argc, &a)))
		return (1);
	sorted_copy = (int *)arena_alloc(arena, (a.size) * sizeof(int) + 1);
	if (!sorted_copy)
		return (write(2, "Error\n", 6), arena_destroy(arena), 1);
	ft_memcpy(sorted_copy, a.arr, (a.size) * sizeof(int));
	merge_sort(sorted_copy, a.size);
	if (has_duplicates(sorted_copy, (a.size)))
		return (write(2, "Error\n", 6), arena_destroy(arena), 1);
	if (is_sorted(&a))
		return (0);
	perform_operations(sorted_copy, &a, &b, (a.size));
	return (arena_destroy(arena), 0);
}
