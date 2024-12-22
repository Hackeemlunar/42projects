#include "libft.h"

void ft_putstr_fd(char *s, int fd)
{
    int i;

    i = 0;
    while (s[i])
    {
        ft_putchar_fd(s[i], fd);
        i++;
    }
}

// int main(void)
// {
//     ft_putstr_fd("Hello World!", 1);
//     ft_putstr_fd("\n", 1);
//     return 0;
// }
