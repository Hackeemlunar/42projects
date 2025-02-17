#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
   We define a Stack structure to hold our array and its current size.
   The allowed operations (sa, pb, ra, etc.) will be implemented as functions
   that both modify the stacks and print the operation name.
*/
typedef struct s_stack {
    int *arr;
    int size;
}   Stack;

/* --- Operation functions --- */

/* swap the first two elements of stack s and print "sa" or "sb" */
void swap(Stack *s, char op)
{
    if (s->size > 1)
    {
        int tmp = s->arr[0];
        s->arr[0] = s->arr[1];
        s->arr[1] = tmp;
        if (op == 'a')
            printf("sa\n");
        else if (op == 'b')
            printf("sb\n");
    }
}

/* push the top element from source stack (src) to destination stack (dest).
   When op == 'a', this is a "pa" (push a) operation,
   when op == 'b', this is a "pb" (push b) operation.
*/
void push_ab(Stack *src, Stack *dest, char op)
{
    if (src->size > 0)
    {
        int tmp = src->arr[0];
        // Remove the first element from src:
        for (int i = 0; i < src->size - 1; i++)
            src->arr[i] = src->arr[i + 1];
        src->size--;
        // Insert tmp at the beginning of dest:
        for (int i = dest->size; i > 0; i--)
            dest->arr[i] = dest->arr[i - 1];
        dest->arr[0] = tmp;
        dest->size++;
        if (op == 'a')
            printf("pa\n");
        else if (op == 'b')
            printf("pb\n");
    }
}

/* rotate: shift up all elements of stack s (first element becomes last) */
void rotate(Stack *s, char op)
{
    if (s->size > 0)
    {
        int tmp = s->arr[0];
        for (int i = 0; i < s->size - 1; i++)
            s->arr[i] = s->arr[i + 1];
        s->arr[s->size - 1] = tmp;
        if (op == 'a')
            printf("ra\n");
        else if (op == 'b')
            printf("rb\n");
    }
}

/* reverse rotate: shift down all elements (last becomes first) */
void rev_rotate(Stack *s, char op)
{
    if (s->size > 0)
    {
        int tmp = s->arr[s->size - 1];
        for (int i = s->size - 1; i > 0; i--)
            s->arr[i] = s->arr[i - 1];
        s->arr[0] = tmp;
        if (op == 'a')
            printf("rra\n");
        else if (op == 'b')
            printf("rrb\n");
    }
}

/* --- Utility functions --- */

/* Comparison function used by qsort */
int cmp_int(const void *a, const void *b)
{
    int int_a = *(int *)a;
    int int_b = *(int *)b;
    return (int_a - int_b);
}

/* Replace each number by its index (its rank when sorted).
   This mapping ensures that the numbers are in the range 0 .. n-1,
   which is very useful for the radix sort.
*/
void index_stack(int *arr, int n)
{
    int *copy = malloc(n * sizeof(int));
    if (!copy)
        exit(EXIT_FAILURE);
    memcpy(copy, arr, n * sizeof(int));
    qsort(copy, n, sizeof(int), cmp_int);
    for (int i = 0; i < n; i++)
    {
        // Find the index (rank) of arr[i] in sorted copy.
        for (int j = 0; j < n; j++)
        {
            if (arr[i] == copy[j])
            {
                arr[i] = j;
                break;
            }
        }
    }
    free(copy);
}

/* Check for duplicate numbers. Returns 1 if a duplicate is found. */
int has_duplicates(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] == arr[j])
                return 1;
    return 0;
}

/* --- Main function --- */
int main(int argc, char **argv)
{
    if (argc < 2)
        return 0; // No numbers provided

    int n = argc - 1;
    int i;

    /* Allocate memory for stacks.
       Note: For push_swap, stack 'a' starts with n elements and stack 'b' is empty.
    */
    Stack a;
    Stack b;
    a.arr = malloc(n * sizeof(int));
    b.arr = malloc(n * sizeof(int));  // Maximum possible size is n.
    if (!a.arr || !b.arr)
        exit(EXIT_FAILURE);
    a.size = n;
    b.size = 0;

    /* Parse input numbers */
    for (i = 0; i < n; i++)
        a.arr[i] = atoi(argv[i + 1]);

    /* Check for duplicates */
    if (has_duplicates(a.arr, n))
    {
        fprintf(stderr, "Error: duplicate numbers detected\n");
        free(a.arr);
        free(b.arr);
        return 1;
    }

    /* Replace numbers by their index (ranking) */
    index_stack(a.arr, n);

    /*
      Now use a radix sort algorithm.
      For each bit (from LSB to MSB), we:
        - Go through all numbers in stack a.
        - If the current bit is 0, push the number to stack b ("pb").
        - Otherwise, rotate stack a ("ra").
      Then we push everything back from b to a ("pa").


    */
    int max_bits = 0;
    while (((n - 1) >> max_bits) != 0)
        max_bits++;

    for (int i_bit = 0; i_bit < max_bits; i_bit++)
    {
        int count = a.size; // Process the current size of a.
        for (i = 0; i < count; i++)
        {
            if (((a.arr[0] >> i_bit) & 1) == 1)
                rotate(&a, 'a');  // "ra"
            else
                push_ab(&a, &b, 'b');  // "pb"
        }
        while (b.size > 0)
            push_ab(&b, &a, 'a');  // "pa"
    }

    /* Clean up memory */
    free(a.arr);
    free(b.arr);
    return 0;
}
