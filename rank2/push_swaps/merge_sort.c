/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:31:38 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/09 20:31:45 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	merge(int *arr, int *temp, int left, int right)
{
	int	mid;
	int	i;
	int	j;
	int	k;

	i = -1;
	mid = (right - left) / 2;
	while (++i < (right - left))
		temp[i] = arr[left + i];
	i = 0;
	j = mid;
	k = left;
	while (i < mid && j < (right - left))
	{
		if (temp[i] <= temp[j])
			arr[k++] = temp[i++];
		else
			arr[k++] = temp[j++];
	}
	while (i < mid)
		arr[k++] = temp[i++];
	while (j < (right - left))
		arr[k++] = temp[j++];
}

static void	merge_sort1(int *arr, int *temp, int left, int right)
{
	int	mid;

	if (left >= right - 1)
		return ;
	mid = left + (right - left) / 2;
	merge_sort1(arr, temp, left, mid);
	merge_sort1(arr, temp, mid, right);
	merge(arr, temp, left, right);
}

void	merge_sort(int *arr, int len)
{
	int		*temp;
	t_arena	*arena;

	arena = arena_create(len * sizeof(int) * 5);
	temp = (int *)arena_alloc(arena, len * sizeof(int) + 1);
	merge_sort1(arr, temp, 0, len);
	arena_destroy(arena);
}
