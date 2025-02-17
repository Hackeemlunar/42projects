#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_stack {
	int *arr;
	int size;
} Stack;

/* --- Operation functions --- */
void swap(Stack *s) {
	if (s->size > 1) {
		int tmp = s->arr[0];
		s->arr[0] = s->arr[1];
		s->arr[1] = tmp;
	}
}

void sa(Stack *a) {
	swap(a);
	printf("sa\n");
}

void sb(Stack *b) {
	swap(b);
	printf("sb\n");
}

void ss(Stack *a, Stack *b)
{
	swap(a);
	swap(b);
	printf("ss\n");
}

void	push(Stack *dest, Stack *src)
{
	if (src->size > 0) {
		int tmp = src->arr[0];
		for (int i = 0; i < src->size - 1; i++)
			src->arr[i] = src->arr[i + 1];
		src->size--;
		for (int i = dest->size; i > 0; i--)
			dest->arr[i] = dest->arr[i - 1];
		dest->arr[0] = tmp;
		dest->size++;
	}
}

void pa(Stack *a, Stack *b) {
	push(a, b);
	printf("pa\n");
}

void pb(Stack *b, Stack *a) {
	push(b, a);
	printf("pb\n");
}

void rotate(Stack *s) {
	if (s->size > 0) {
		int tmp = s->arr[0];
		for (int i = 0; i < s->size - 1; i++)
			s->arr[i] = s->arr[i + 1];
		s->arr[s->size - 1] = tmp;
	}
}

void ra(Stack *a) {
	rotate(a);
	printf("ra\n");
}

void rb(Stack *b) {
	rotate(b);
	printf("rb\n");
}

void rr(Stack *a, Stack *b) {
	rotate(a);
	rotate(b);
	printf("rr\n");
}

void rev_rotate(Stack *s) {
	if (s->size > 0) {
		int tmp = s->arr[s->size - 1];
		for (int i = s->size - 1; i > 0; i--)
			s->arr[i] = s->arr[i - 1];
		s->arr[0] = tmp;
	}
}

void rra(Stack *a) {
	rev_rotate(a);
	printf("rra\n");
}

void rrb(Stack *b) {
	rev_rotate(b);
	printf("rrb\n");
}

void rrr(Stack *a, Stack *b) {
	rev_rotate(a);
	rev_rotate(b);
	printf("rrr\n");
}

/* --- Utility functions --- */
int cmp_int(const void *a, const void *b) {
	return (*(int *)a - *(int *)b);
}

void index_stack(int *arr, int n) {
	int *copy = malloc(n * sizeof(int));
	memcpy(copy, arr, n * sizeof(int));
	qsort(copy, n, sizeof(int), cmp_int);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i] == copy[j]) {
				arr[i] = j;
				break;
			}
		}
	}
	free(copy);
}

int has_duplicates(int *arr, int n) {
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (arr[i] == arr[j])
				return 1;
	return 0;
}

/* --- Sorting Algorithm --- */
void sort_small_stack(Stack *a, Stack *b) {
	while (a->size > 1) {
		if (a->arr[0] > a->arr[1]) {
			sa(a);
		}
		pb(b, a);
	}
	while (b->size > 0) {
		pa(a, b);
	}
}

void radix_sort(Stack *a, Stack *b, int n) {
	int max_bits = 0;
	while (((n - 1) >> max_bits) != 0)
		max_bits++;

	for (int i_bit = 0; i_bit < max_bits; i_bit++) {
		int count = a->size;
		for (int i = 0; i < count; i++) {
			if (((a->arr[0] >> i_bit) & 1) == 1) {
				ra(a); // "ra"
			} else {
				pb(b, a); // "pb"
			}
		}
		while (b->size > 0) {
			pa(a, b); // "pa"
		}
	}
}

/* --- Main function --- */
int main(int argc, char **argv) {
	if (argc < 2)
		return 0;

	int n = argc - 1;
	Stack a, b;
	a.arr = malloc(n * sizeof(int));
	b.arr = malloc(n * sizeof(int));
	if (!a.arr || !b.arr)
		exit(EXIT_FAILURE);

	a.size = n;
	b.size = 0;

	/* Parse input numbers */
	for (int i = 0; i < n; i++)
		a.arr[i] = atoi(argv[i + 1]);

	/* Check for duplicates */
	if (has_duplicates(a.arr, n)) {
		fprintf(stderr, "Error: duplicate numbers detected\n");
		free(a.arr);
		free(b.arr);
		return 1;
	}

	/* Replace numbers by their index (ranking) */
	index_stack(a.arr, n);

	/* Use optimized sorting strategy */
	if (n <= 5)
		sort_small_stack(&a, &b);
	else
		radix_sort(&a, &b, n);

	/* Clean up memory */
	free(a.arr);
	free(b.arr);
	return 0;
}