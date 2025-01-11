#include "libft.h"
#include "ft_printf.h"
#include <stdlib.h>

t_fdata* new_fdata()
{
    t_fdata* data;

    data = (t_fdata *)malloc(sizeof(t_fdata));
    if(!data)
        return (NULL);
    data->count = 0;
    data->fstring = NULL;
    return (data);
}

t_modinfo* new_modinfo()
{
    t_modinfo* data;

    data = (t_modinfo *)malloc(sizeof(t_modinfo));
    if(!data)
        return (NULL);
    data->flag = false;
    data->width = false;
    data->precision = false;
    data->modifiers = false;
    return (data);
}