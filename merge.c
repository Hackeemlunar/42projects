#include <stdio.h>

void merge(int *arr, int left, int mid, int right)
{
	int L[mid - left + 1];
	int R[right - mid];
	int i;
	int j;
	int k;

	i = -1;
	j = -1;
	k = left;
	while (++i < (mid - left + 1))
		L[i] = arr[left + i];
	while (++j < (right - mid))
		R[j] = arr[mid + 1 + j];
	i = 0;
	j = 0;
	while ((i < (mid - left + 1)) && (j < (right - mid)))
		if (L[i] < R[j])
			arr[k++] = L[i++];
		else
			arr[k++] = R[j++];
	while (i < (mid - left + 1))
		arr[k++] = L[i++];
	while (j < (right - mid))
		arr[k++] = R[j++];
}

void merge_sort(int *arr, int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = left + (right - left) / 2;
		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}

int main() {
    int arr[100];
    int arr_size = 100;

	int i = 101;
	int j = 0;
	while (--i > 0)
		arr[j++] = i;
    printf("Unsorted array: \n");
    for (int i = 0; i < arr_size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    merge_sort(arr, 0, arr_size - 1);

    printf("Sorted array: \n");
    for (int i = 0; i < arr_size; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}