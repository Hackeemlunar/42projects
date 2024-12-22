#include "libft.h"

char *ft_strnstr(const char *haystack, const char *needle, size_t len)
{
    size_t needle_len;
    size_t i;

    if (*needle == '\0')
        return (char *)haystack;

    needle_len = ft_strlen(needle);
    i = 0;
    while (i + needle_len <= len && haystack[i] != '\0')
    {
        if (ft_strncmp(&haystack[i], needle, needle_len) == 0)
            return (char *)&haystack[i];
        i++;
    }
    return NULL;
}
