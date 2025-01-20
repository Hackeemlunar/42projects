/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_precision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:03:18 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/20 19:20:44 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_string_size(char *fstring, int size, t_fdata *data)
{
	int	len;

	len = data->count;
	if (len > size)
	{
		fstring[size] = '\0';
		data->count = size;
	}
}

void	handle_int_size(char *fstring, char pad, int size, t_fdata *data)
{
	size_t	padding;
	char	*new_string;

	if (size > data->count)
	{
		if (*fstring == '-')
			size++;
		padding = size - data->count;
		new_string = (char *)malloc(size + 1);
		if (!new_string)
			return ;
		ft_memset(new_string, pad, size);
		new_string[size] = '\0';
		if (*fstring == '-')
		{
			new_string[0] = '-';
			ft_memmove(new_string + padding + 1, fstring + 1, data->count - 1);
		}
		else
			ft_memmove(new_string + padding, fstring, data->count);
		free(fstring);
		data->fstring = new_string;
		data->count = size;
	}
}

void	handle_int_prec(char *str, int prec, t_fdata *data, t_modinfo *info)
{
	handle_int_size(str, '0', prec, data);
	str = data->fstring;
	if (ft_strchr(info->flags, ' ') && !ft_strchr(info->flags, '+')
		&& *str != '-')
		append_first(str, ' ', data);
	else if (ft_strchr(info->flags, '+') && *str != '-')
		append_first(str, '+', data);
}

void	apply_precision(t_modinfo *modinfo, t_fdata *fdata)
{
	char	specifier;
	int		precision;
	char	*fstring;

	if (modinfo == NULL || fdata == NULL || fdata->fstring == NULL)
		return ;
	specifier = modinfo->specifier;
	precision = modinfo->precision;
	fstring = fdata->fstring;
	if (precision < 0)
		return ;
	if (specifier == 's')
		handle_string_size(fstring, precision, fdata);
	else if (specifier == 'd' || specifier == 'i')
		handle_int_prec(fstring, precision, fdata, modinfo);
}
