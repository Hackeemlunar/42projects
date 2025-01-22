/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_width_flags.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:51:36 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/22 18:46:07 by hmensah-         ###   ########.fr       */
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

void	apply_prefix(const char *prefix, t_modinfo *info, t_fdata *fdata)
{
	char	*str;
	int		total_w;
	int		all_zeroes;

	all_zeroes = all_are_zeroes(fdata->fstring);
	if (info->width > fdata->count + 2)
		total_w = info->width;
	else
		total_w = fdata->count + 2;
	str = ft_calloc(total_w + 1, sizeof(char));
	if (!str)
		return ;
	if (ft_strchr(info->flags, '-'))
	{
		ft_strcpy(str, prefix);
		ft_strlcpy(str + 2, fdata->fstring, fdata->count + 1);
		ft_memset(str + 2 + fdata->count, ' ', total_w - fdata->count - 2);
	}
	else if (ft_strchr(info->flags, '0') && (!all_zeroes))
	{
		ft_strcpy(str, prefix);
		ft_memset(str + 2, '0', total_w - fdata->count - 2);
		ft_strcpy(str + 2 + (total_w - fdata->count - 2), fdata->fstring);
	}
	else
	{
		if (all_zeroes)
		{
			ft_strcpy(str + total_w - fdata->count - 2, fdata->fstring);
			total_w -= 2;
		}
		else
		{
			ft_memset(str, ' ', total_w - fdata->count - 2);
			ft_strcpy(str + (total_w - fdata->count - 2), prefix);
			ft_strcpy(str + total_w - fdata->count, fdata->fstring);
		}
	}
	free(fdata->fstring);
	fdata->fstring = str;
	fdata->count = total_w;
}
