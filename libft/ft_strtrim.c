#include "libft.h"

char *ft_strtrim(char const *s1, char const *set)
{
    size_t start;
    size_t end;
    char *trimmed_str;

    if (!s1 || !set)
        return (NULL);

    start = 0;
    while (s1[start] && ft_strchr(set, s1[start]))
        start++;
    
    end = ft_strlen(s1);
    while (end > start && ft_strchr(set, s1[end - 1]))
        end--;

    trimmed_str = (char *)malloc(sizeof(char) * (end - start + 1));
    if (!trimmed_str)
        return (NULL);

    ft_strlcpy(trimmed_str, &s1[start], end - start + 1);
    return (trimmed_str);
}

// int main(void)
// {
//     // Example test for *ft_strtrim
//     return 0;
// }
