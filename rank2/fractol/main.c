#include "libft/libft.h"

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        printf("atoi: %d\n", ft_atoi(argv[1]));
        printf("atol: %ld\n", ft_atol(argv[1]));
        printf("atod: %f\n", ft_atod(argv[1]));
    }
    return (0);
}