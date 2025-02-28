// Example usage of the arena
#include "libft/libft.h"

int main() {
    t_arena *arena = arena_create(1024); // Create an arena with 1024 bytes

    int *numbers = (int *)arena_alloc(arena, 10 * sizeof(int)); // Allocate space for 10 integers
    if (numbers) {
        for (int i = 0; i < 10; i++) {
            numbers[i] = i;
        }
    }

    char *message = (char *)arena_alloc(arena, 50 * sizeof(char)); // Allocate space for a string
    if (message) {
        strcpy(message, "Hello, Arena!");
    }

    // Use the allocated memory
    if (numbers) {
        for (int i = 0; i < 10; i++) {
            printf("%d ", numbers[i]);
        }
        printf("\n");
    }

    if (message) {
        printf("%s\n", message);
    }

    arena_destroy(arena); // Clean up the arena
    return 0;
}