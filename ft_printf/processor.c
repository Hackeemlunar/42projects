/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:03:18 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/14 17:45:29 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

void	apply_flags(t_fdata *data, t_modinfo *info)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	*temp;

	i = 0;
	j = 0;
	k = 0;
	len = data->count;
	temp = calloc(len + 1, sizeof(char));
	if (!temp)
		return ;
	if (strchr(info->flags, '-'))
	{
		while (data->fstring[i])
			temp[j++] = data->fstring[i++];
		while (j < info->width)
			temp[j++] = ' ';
	}
	else if (strchr(info->flags, '0') && !strchr(info->flags, '-'))
	{
		while (j < info->width - len)
			temp[j++] = '0';
		while (data->fstring[k])
			temp[j++] = data->fstring[k++];
	}
	else
	{
		while (j < info->width - len)
			temp[j++] = ' ';
		while (data->fstring[k])
			temp[j++] = data->fstring[k++];
	}
	if (strchr(info->flags, '+') || strchr(info->flags, ' '))
	{
		if (data->fstring[0] != '-' && data->fstring[0] != '+')
		{
			if (strchr(info->flags, '+'))
				temp[0] = '+';
			else if (strchr(info->flags, ' '))
				temp[0] = ' ';
		}
	}
	free(data->fstring);
	data->fstring = temp;
}
