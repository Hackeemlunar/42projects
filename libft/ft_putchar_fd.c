#include "libft.h"

void ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}

// int main(void)
// {
//     char *a = "Hello World!";
//     int i = 0;
//     while (a[i])
//     {
//         ft_putchar_fd(a[i], 1);
//         i++;
//     }
//     ft_putchar_fd('\n', 1);
//     return 0;
// }
