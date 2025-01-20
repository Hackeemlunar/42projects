/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_nums.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:30:23 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/20 19:38:50 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_fdata	*create_number_data(t_modinfo *info, long nbr, int base)
{
	t_fdata	*data;
	char	*nbr_str;

	nbr_str = ft_itoa_base(nbr, base, 0);
	if (!nbr_str)
		return (NULL);
	if (info->precision == 0 && nbr == 0)
		nbr_str[0] = '\0';
	data = (t_fdata *)malloc(sizeof(t_fdata));
	if (!data)
	{
		free(nbr_str);
		return (NULL);
	}
	data->fstring = nbr_str;
	data->count = ft_strlen(nbr_str);
	apply_precision(info, data);
	apply_width_and_flags(info, data);
	if (info->precision <= 0 && info->width <= 0)
		handle_int_prec(nbr_str, info->precision, data, info);
	return (data);
}

t_fdata	*handle_num_int(t_modinfo *modinfo, va_list args)
{
	int	nbr;

	nbr = va_arg(args, int);
	return (create_number_data(modinfo, nbr, 10));
}

t_fdata	*handle_num_long(t_modinfo *modinfo, va_list args)
{
	long	nbr;

	nbr = va_arg(args, int);
	return (create_number_data(modinfo, nbr, 10));
}

static void	apply_hex(t_fdata *data, t_modinfo *info, int upc, char *str)
{
	data->fstring = str;
	data->count = ft_strlen(str);
	if (ft_strchr(info->flags, '#'))
	{
		if (upc)
			apply_prefix(&str, "0X", data);
		else
			apply_prefix(&str, "0x", data);
	}
	apply_precision(info, data);
	apply_width_and_flags(info, data);
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
	apply_hex(data, modinfo, uppercase, nbr_str);
	return (data);
}
