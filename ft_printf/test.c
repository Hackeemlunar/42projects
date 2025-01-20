#include "ft_printf.h"

int main()
{
    long k = 9223372;
    int a = ft_printf("Hello, %.120d\n", k);
    int b = printf("Hello, %.120d\n", k);

    printf("ft_printf: %d\n", a);
    printf("printf: %d\n", b);

    return 0;
}
