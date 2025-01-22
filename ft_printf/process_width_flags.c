/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_width_flags.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:51:36 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/22 23:15:57 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	all_are_zeroes(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '0')
			return (0);
		i++;
	}
	return (1);
}

void	add_prefix(const char *pref, t_fdata *data)
{
	char	*str;
	int		wid;

	wid = data->count + 2;
	str = malloc(wid + 1);
	ft_strcpy(str, pref);
	ft_strcpy(str + 2, data->fstring);
	str[wid] = '\0';
	free(data->fstring);
	data->fstring = str;
	data->count = wid;
}

void	pad(t_modinfo *info, t_fdata *data, int width)
{
	char	*str;

	str = malloc(width + 1);
	if (ft_strchr(info->flags, '-'))
	{
		ft_strcpy(str, data->fstring);
		ft_memset(str + data->count, ' ', width - data->count);
	}
	else if (ft_strchr(info->flags, '0') && info->precision < 0)
	{
		str[0] = data->fstring[0];
		str[1] = data->fstring[1];
		ft_memset(str + 2, '0', width - data->count);
		ft_strcpy(str + 2 + (width - data->count), data->fstring + 2);
	}
	else
	{
		ft_memset(str, ' ', width - data->count);
		ft_strcpy(str + (width - data->count), data->fstring);
	}
	str[width] = '\0';
	free(data->fstring);
	data->fstring = str;
	data->count = width;
}

void	apply_prefix(const char *pref, t_modinfo *info, t_fdata *data)
{
	int		all_zeroes;
	int		pref_added;

	pref_added = 0;
	all_zeroes = all_are_zeroes(data->fstring);
	if (!all_zeroes)
	{
		add_prefix(pref, data);
		pref_added = 1;
	}
	if (info->width > data->count)
		pad(info, data, info->width);
}
