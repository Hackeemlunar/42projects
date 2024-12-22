#include "libft.h"

char *ft_strdup(const char *s1)
{
    size_t len;
    char *res;

    len = ft_strlen(s1);
    res = (char *)malloc(len + 1);
    if (!res)
        return (NULL);
    res[len] = '\0';
    return ((char *)ft_memcpy(res, s1, len));
}

