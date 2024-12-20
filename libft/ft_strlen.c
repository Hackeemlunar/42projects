#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t ft_strlen(const char *s)
{
    size_t  i;

    i = 0;
    while (s[i] != '\0')
    {
        i++;
    }
    return  (i);
}

// int main(void)
// {
//     // Example test for ft_strlen
//     return 0;
// }
