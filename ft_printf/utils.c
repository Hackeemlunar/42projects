/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:44:50 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/20 14:46:09 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char *convert_number(unsigned long n, int base, int is_negative, int upc)
{
	char temp[21];
	char *res;
	int i;
	int j;

	i = 0;
	j = 0;
	while (n > 0)
	{
		if (n % base < 10)
			temp[i++] = n % base + '0';
		else
		{
			if (upc)
				temp[i++] = n % base - 10 + 'A';
			else
				temp[i++] = n % base - 10 + 'a';
		}
		n /= base;
	}
	res = (char *)malloc(i + is_negative + 1);
	if (!res)
		return (NULL);
	if (is_negative)
		res[j++] = '-';
	while (i > 0)
		res[j++] = temp[--i];
	res[j] = '\0';
	return (res);
}

char *ft_itoa_base(long nbr, int base, int uppercase)
{
	unsigned long n;
	int is_negative;

	is_negative = 0;
	if (nbr == 0)
		return (ft_strdup("0"));
	if (nbr < 0 && base == 10)
	{
		is_negative = 1;
		n = -nbr;
	}
	else
	{
		n = nbr;
	}
	return (convert_number(n, base, is_negative, uppercase));
}

void ft_putstr_pf(t_fdata *data)
{
	int i;

	i = 0;
	while (i < data->count)
	{
		write(1, &data->fstring[i], 1);
		i++;
	}
}

void apply_prefix(const char *prefix, t_modinfo *info, t_fdata *fdata)
{
	char *new_string;
	int total_width;

	if (info->width > fdata->count + 2)
		total_width = info->width;
	else
		total_width = fdata->count + 2;
	new_string = malloc(total_width + 1);
	if (!new_string)
		return;
	if (ft_strchr(info->flags, '-'))
	{
		ft_strcpy(new_string, prefix);
		ft_strlcpy(new_string + 2, fdata->fstring, fdata->count + 1);
		ft_memset(new_string + 2 + fdata->count, ' ', total_width - fdata->count - 2);
	}
	else
	{
		ft_memset(new_string, ' ', total_width - fdata->count - 2);
		ft_strcpy(new_string + (total_width - fdata->count - 2), prefix);
		ft_strcpy(new_string + total_width - fdata->count, fdata->fstring);
	}
	new_string[total_width] = '\0';
	free(fdata->fstring);
	fdata->fstring = new_string;
	fdata->count = total_width;
}
