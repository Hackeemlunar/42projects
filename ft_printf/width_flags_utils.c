/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_flags_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:48:58 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/20 15:52:02 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	apply_left_justify(char *fstring, int width, t_fdata *fdata)
{
	char	*new_string;
	int		padding;

	new_string = (char *)ft_calloc(width + 1, sizeof(char));
	if (!new_string)
		return ;
	padding = width - fdata->count;
	ft_memcpy(new_string, fstring, fdata->count);
	ft_memset(new_string + fdata->count, ' ', padding);
	new_string[width] = '\0';
	free(fstring);
	fdata->fstring = new_string;
	fdata->count = width;
}

void	apply_r_justify(char *fstring, int width, char pad, t_fdata *fdata)
{
	char	*new_string;
	int		padding;

	new_string = (char *)ft_calloc(width + 1, sizeof(char));
	if (!new_string)
		return ;
	padding = width - fdata->count;
	ft_memset(new_string, pad, padding);
	ft_memcpy(new_string + padding, fstring, fdata->count);
	free(fstring);
	fdata->fstring = new_string;
	fdata->count = width;
}
