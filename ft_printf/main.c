# include <stdio.h>
# include <stdarg.h>

int mult(int count, ...) {
    va_list args;
    va_start(args, count);
    va_arg(args, int);
    va_end(args);
}

int main(int argc, char** argv) {
    printf("%-2s: 3\n", "Hello, World!");
    printf("%d\n", 19999.00);
    return 0;
}