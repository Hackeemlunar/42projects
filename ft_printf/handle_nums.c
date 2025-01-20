#include "ft_printf.h"

static t_fdata	*create_number_data(t_modinfo *modinfo, long nbr, int base)
{
    t_fdata	*data;
    char	*nbr_str;

    nbr_str = ft_itoa_base(nbr, base, 0);
    if (!nbr_str)
        return (NULL);
    if (modinfo->precision == 0 && nbr == 0)
        nbr_str[0] = '\0';
    data = (t_fdata *)malloc(sizeof(t_fdata));
    if (!data)
    {
        free(nbr_str);
        return (NULL);
    }
    data->fstring = nbr_str;
    data->count = ft_strlen(nbr_str);
    apply_precision(modinfo, data);
    apply_width_and_flags(modinfo, data);
    return (data);
}

t_fdata	*handle_num_int(t_modinfo *modinfo, va_list args)
{
    int	nbr;

    nbr = va_arg(args, int);
    return create_number_data(modinfo, nbr, 10);
}

t_fdata	*handle_num_long(t_modinfo *modinfo, va_list args)
{
    long	nbr;

    nbr = va_arg(args, int);
    return create_number_data(modinfo, nbr, 10);
}

t_fdata	*handle_hex(t_modinfo *modinfo, va_list args)
{
    t_fdata	*data;
    long	nbr;
    char	*nbr_str;
    int		uppercase;

    uppercase = modinfo->specifier == 'X';
    nbr = va_arg(args, long);
    nbr_str = ft_itoa_base(nbr, 16, uppercase);
    if (!nbr_str)
        return (NULL);
    if (modinfo->precision == 0 && nbr == 0)
        nbr_str[0] = '\0';
    data = (t_fdata *)malloc(sizeof(t_fdata));
    if (!data)
    {
        free(nbr_str);
        return (NULL);
    }
    data->fstring = nbr_str;
    data->count = ft_strlen(nbr_str);
    if (ft_strchr(modinfo->flags, '#'))
        if (uppercase)
            apply_prefix(&nbr_str, "0X", data);
        else
            apply_prefix(&nbr_str, "0x", data);
    apply_precision(modinfo, data);
    apply_width_and_flags(modinfo, data);
    return (data);
}