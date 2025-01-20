/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_width_flags.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:51:36 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/20 17:03:05 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	append_first(char *fstring, char first, t_fdata *fdata)
{
	char	*new_string;

	new_string = (char *)ft_calloc(fdata->count + 1, sizeof(char));
	if (!new_string)
		return ;
	new_string[0] = first;
	ft_memcpy(new_string + 1, fstring, fdata->count);
	free(fstring);
	fdata->fstring = new_string;
	fdata->count++;
}

static void	apply_flags(char *str, t_modinfo *modinfo, t_fdata *fdata)
{
	if (ft_strchr(modinfo->flags, '+') && (*str != '-' || *str != '+'))
		append_first(str, '+', fdata);
	else if (ft_strchr(modinfo->flags, ' ') && (*str != '-' || *str != ' '))
		append_first(str, ' ', fdata);
}

void	apply_width_and_flags(t_modinfo *modinfo, t_fdata *fdata)
{
	char	*fstring;
	int		width;
	char	pad;

	if (!modinfo || !fdata || !fdata->fstring)
		return ;
	fstring = fdata->fstring;
	width = modinfo->width;
	if (width <= fdata->count)
		return ;
	pad = ' ';
	if (ft_strchr(modinfo->flags, '0') && !ft_strchr(modinfo->flags, '-'))
		pad = '0';
	apply_flags(fstring, modinfo, fdata);
	fstring = fdata->fstring;
	if (ft_strchr(modinfo->flags, '-'))
		apply_left_justify(fstring, width, fdata);
	else
		apply_r_justify(fstring, width, pad, fdata);
}
