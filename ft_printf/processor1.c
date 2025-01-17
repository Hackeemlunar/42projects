/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:51:36 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/17 13:56:25 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

static void	apply_left_justify(char *fstring, int width, t_fdata *fdata)
{
	char	*new_string;
	int		padding;

	new_string = malloc(width + 1);
	if (!new_string)
		return ;
	padding = width - fdata->count;
	memcpy(new_string, fstring, fdata->count);
	memset(new_string + fdata->count, ' ', padding);
	new_string[width] = '\0';
	free(fstring);
	fdata->fstring = new_string;
	fdata->count = width;
}

static void	apply_r_justify(char *fstring, int width, char pad, t_fdata *fdata)
{
	char	*new_string;
	int		padding;

	new_string = malloc(width + 1);
	if (!new_string)
		return ;
	padding = width - fdata->count;
	memset(new_string, pad, padding);
	memcpy(new_string + padding, fstring, fdata->count);
	new_string[width] = '\0';
	free(fstring);
	fdata->fstring = new_string;
	fdata->count = width;
}

static void	apply_prefix(char **fstring, const char *prefix, t_fdata *fdata)
{
	char	*new_string;

	new_string = malloc(fdata->count + strlen(prefix) + 1);
	if (!new_string)
		return ;
	strcpy(new_string, prefix);
	strcat(new_string, *fstring);
	free(*fstring);
	*fstring = new_string;
	fdata->fstring = new_string;
	fdata->count += strlen(prefix);
}

static void	apply_flags(char *fstring, t_modinfo *modinfo, t_fdata *fdata)
{
	char	*new_string;

	if (strchr(modinfo->flags, '+') && *fstring != '-')
	{
		new_string = malloc(fdata->count + 2);
		if (!new_string)
			return ;
		new_string[0] = '+';
		memcpy(new_string + 1, fstring, fdata->count);
		new_string[fdata->count + 1] = '\0';
		free(fstring);
		fdata->fstring = new_string;
		fdata->count++;
	}
	else if (strchr(modinfo->flags, ' ') && *fstring != '-')
	{
		new_string = malloc(fdata->count + 2);
		if (!new_string)
			return ;
		new_string[0] = ' ';
		memcpy(new_string + 1, fstring, fdata->count);
		new_string[fdata->count + 1] = '\0';
		free(fstring);
		fdata->fstring = new_string;
		fdata->count++;
	}
	if (strchr(modinfo->flags, '#'))
	{
		if (modinfo->specifier == 'x')
			apply_prefix(&fstring, "0x", fdata);
		else if (modinfo->specifier == 'X')
			apply_prefix(&fstring, "0X", fdata);
	}
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
	if (strchr(modinfo->flags, '0') && !strchr(modinfo->flags, '-'))
		pad = '0';
	apply_flags(fstring, modinfo, fdata);
	fstring = fdata->fstring;
	if (strchr(modinfo->flags, '-'))
		apply_left_justify(fstring, width, fdata);
	else
		apply_r_justify(fstring, width, pad, fdata);
}
