/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:03:18 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/18 19:48:07 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

static void	handle_string_precision(char *fstring, int precision, t_fdata *data)
{
	int	len;

	len = data->count;
	if (len > precision)
	{
		fstring[precision] = '\0';
		data->count = precision;
	}
}

static void	handle_int_precision(char *fstring, int precision, t_fdata *data)
{
	size_t	padding;
	char	*new_string;

	padding = precision - data->count;
	if (precision > data->count)
	{
		new_string = malloc(precision + 1);
		if (!new_string)
			return ;
		ft_memset(new_string, '0', precision);
		data->count = precision;
		if (*fstring == '-')
		{
			new_string[0] = '-';
			ft_memmove(new_string + padding + 2, fstring + 1, data->count++);
		}
		else
			ft_memmove(new_string + padding, fstring, data->count + 1);
		free(fstring);
		data->fstring = new_string;
	}
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
		handle_string_precision(fstring, precision, fdata);
	else if (specifier == 'd' || specifier == 'i')
		handle_int_precision(fstring, precision, fdata);
}
