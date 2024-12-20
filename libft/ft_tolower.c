#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ft_tolower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return ('a' + (c - 'A'));
    return (c);
}

// int main(void)
// {
//     int a = '4';
//     printf("       num: %c\n", a);
//     printf("ft_tolower: %c\n", ft_tolower(a));
//     printf("   tolower: %c\n", ft_tolower(a));
//     return 0;
// }