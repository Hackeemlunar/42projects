#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

char	*ft_itoa_base(long long value, int base, int uppercase);

int main() {
    char    *result;
    long     i;
    // int     i;

    i = -455555666666666666;
    // i = 0;
    result = ft_itoa_base(i, 10, 0); // Convert -255 to base 10
    printf("Base 10: %s\n", result);
    printf("Base 10: %ld\n", i);
    free(result);

    result = ft_itoa_base(i, 16, 0); // Convert -255 to base 16
    printf("Base 16: %s\n", result);
    printf("Base 16: %lx\n", i);
    free(result);

    return 0;
}
