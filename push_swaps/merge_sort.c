#include "push_swap.h"

void merge(int *arr, int *temp, int left, int right)
{
	int	mid;
	int i;
	int j;
	int k;

	i = -1;
	mid = left + (right - left) / 2;
	while (++i < (right - left))
		temp[i] = arr[left + i];
	i = 0;
	j = 0;
	k = left;
	while ((i < (mid - left + 1)) && (j < (right - mid)))
		if (temp[i] < temp[j])
			arr[k++] = temp[i++];
		else
			arr[k++] = R[j++];
	while (i < (mid - left + 1))
		arr[k++] = L[i++];
	while (j < (right - mid))
		arr[k++] = R[j++];
}

void merge_sort1(int *arr, int *temp, int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = left + (right - left) / 2;
		merge_sort1(arr, temp, left, mid);
		merge_sort1(arr, temp, mid + 1, right);
		merge(arr, left, mid, right);
	}
}

void	merge_sort(void *arr, int len)
{
	int		*temp;
	t_arena *arena;

	arena = arena_create(len * 2);
	temp = (int *)arena_alloc(arena, len);
	merge_sort1(arr, temp, 0, len);
	arena_destroy(arena);
}
