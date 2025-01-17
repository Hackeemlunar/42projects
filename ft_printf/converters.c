/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:02:42 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/17 13:48:53 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

static void	convert_b(uint64_t n, uint64_t base, t_fdata *data, char ofs)
{
	char	*sym;

	if (ofs == 'A')
		sym = "0123456789ABCDEF";
	else
		sym = "0123456789abcdef";
	if (n < base)
		data->fstring[data->count++] = sym[n];
	else
	{
		convert_b(n / base, base, data, ofs);
		convert_b(n % base, base, data, ofs);
	}
}

t_fdata	*convert_num(int64_t num, int base, char offset, int isneg)
{
	t_fdata	*data;
	char	*str;

	data = ft_calloc(1, sizeof(t_fdata *));
	if (!data)
		return (NULL);
	str = ft_calloc(21, sizeof(char));
	if (!str)
	{
		free(data);
		return (NULL);
	}
	data->count = 0;
	data->fstring = str;
	if (num < 0 && base == 10)
		num = -num;
	convert_b(num, base, data, offset);
	if (isneg && base == 10)
	{
		data->fstring = ft_strjoin("-", str);
		data->count += 1;
		free(str);
	}
	return (data);
}
