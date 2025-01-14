#include "libft/libft.h"
#include "ft_printf.h"

char *convert_b(uint64_t num, int base, char ofst, int *len)
{
    char *str;
    int i;

    str = ft_calloc(65, sizeof(char));
    i = 0;

    if (num == 0)
        str[i++] = '0';

    while (num != 0) {
        if (num % base < 10)
            str[i] = (num % base) + '0';
        else
            str[i] = (num % base) + ofst - 10;
        i++;
        num /= base;
    }
    *len = i;
    str[i] = '\0';
    return str;
}

t_fdata *convert_num(int64_t num, int base, char offset)
{
   
}
