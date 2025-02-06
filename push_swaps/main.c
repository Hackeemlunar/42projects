#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_MOVES 12  // Prevents infinite loops
#define QUEUE_SIZE 100000  // Defines the queue limit
typedef struct s_stack {
    int *arr;
    int size;
} t_stack;
typedef struct s_state {
    t_stack a, b;
    char moves[MAX_MOVES * 4];  // Store operations
} t_state;
// Utility function to check if stack a is sorted
int is_sorted(t_stack *a) {
    for (int i = 0; i < a->size - 1; i++) {
        if (a->arr[i] > a->arr[i + 1])
            return 0;
    }
    return 1;
}
// Swap top two elements
void swap(t_stack *stack) {
    if (stack->size < 2) return;
    int temp = stack->arr[0];
    stack->arr[0] = stack->arr[1];
    stack->arr[1] = temp;
}
// Push top element from src to dest
void push(t_stack *src, t_stack *dest) {
    if (src->size == 0) return;
    for (int i = dest->size; i > 0; i--)
        dest->arr[i] = dest->arr[i - 1];
    dest->arr[0] = src->arr[0];
    for (int i = 0; i < src->size - 1; i++)
        src->arr[i] = src->arr[i + 1];
    src->size--;
    dest->size++;
}
// Rotate stack
void rotate(t_stack *stack) {
    if (stack->size < 2) return;
    int first = stack->arr[0];
    for (int i = 0; i < stack->size - 1; i++)
        stack->arr[i] = stack->arr[i + 1];
    stack->arr[stack->size - 1] = first;
}
// Reverse rotate stack
void reverse_rotate(t_stack *stack) {
    if (stack->size < 2) return;
    int last = stack->arr[stack->size - 1];
    for (int i = stack->size - 1; i > 0; i--)
        stack->arr[i] = stack->arr[i - 1];
    stack->arr[0] = last;
}
// Copy stack state with original capacity N
t_state copy_state(t_state state, int N) {
    t_state new_state = state;
    new_state.a.arr = malloc(sizeof(int) * N);
    new_state.b.arr = malloc(sizeof(int) * N);
    memcpy(new_state.a.arr, state.a.arr, sizeof(int) * state.a.size);
    memcpy(new_state.b.arr, state.b.arr, sizeof(int) * state.b.size);
    return new_state;
}
// BFS to find optimal move sequence
void bfs(t_stack *a) {
    int N = a->size; // Original number of elements
    t_state queue[QUEUE_SIZE];
    int front = 0, rear = 0;
    t_state initial_state = {
        .a = *a,
        .b = {malloc(sizeof(int) * N), 0}, // Allocate with capacity N
        .moves = ""
    };
    queue[rear++] = initial_state;
    while (front < rear) {
        t_state current = queue[front++];
        
        if (is_sorted(&current.a) && current.b.size == 0) {
            printf("Optimal moves: %s\n", current.moves);
            // Free memory
            free(current.a.arr);
            free(current.b.arr);
            while (front < rear) {
                free(queue[front].a.arr);
                free(queue[front].b.arr);
                front++;
            }
            return;
        }
        // Generate next states
        t_state next;
        
        // sa (swap a)
        next = copy_state(current, N);
        swap(&next.a);
        strcat(next.moves, "sa ");
        if (rear < QUEUE_SIZE) queue[rear++] = next;
        else free(next.a.arr), free(next.b.arr);
        
        // pb (push a to b)
        next = copy_state(current, N);
        push(&next.a, &next.b);
        strcat(next.moves, "pb ");
        if (rear < QUEUE_SIZE) queue[rear++] = next;
        else free(next.a.arr), free(next.b.arr);
        
        // pa (push b to a)
        next = copy_state(current, N);
        push(&next.b, &next.a);
        strcat(next.moves, "pa ");
        if (rear < QUEUE_SIZE) queue[rear++] = next;
        else free(next.a.arr), free(next.b.arr);
        
        // ra (rotate a)
        next = copy_state(current, N);
        rotate(&next.a);
        strcat(next.moves, "ra ");
        if (rear < QUEUE_SIZE) queue[rear++] = next;
        else free(next.a.arr), free(next.b.arr);
        
        // rra (reverse rotate a)
        next = copy_state(current, N);
        reverse_rotate(&next.a);
        strcat(next.moves, "rra ");
        if (rear < QUEUE_SIZE) queue[rear++] = next;
        else free(next.a.arr), free(next.b.arr);
        
        // Free current state's memory after processing
        free(current.a.arr);
        free(current.b.arr);
    }
}
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: ./push_swap <numbers>\n");
        return 1;
    }
    t_stack a = {malloc(sizeof(int) * (argc - 1)), argc - 1};
    for (int i = 0; i < argc - 1; i++)
        a.arr[i] = atoi(argv[i + 1]);
    bfs(&a);
    free(a.arr);
    return 0;
}
