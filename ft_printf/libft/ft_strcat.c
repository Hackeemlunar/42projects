#include "libft.h"

char *ft_strcat(char *dst, const char *src)
{
    int i;
    int j;

    i = 0;
    while (dst[i] != '\0')
        i++;
    j = 0;
    while (src[j] != '\0')
    {
        dst[i] = src[j];
        i++;
        j++;
    }
    dst[i] = '\0';
    return dst;
}