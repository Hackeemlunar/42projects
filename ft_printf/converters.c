/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:02:42 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/14 21:51:56 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

char	*convert_b(uint64_t num, int base, char ofst, int *len)
{
	char	*str;
	int		i;

	str = ft_calloc(65, sizeof(char));
	i = 0;
	if (!str)
		return (NULL);
	if (num == 0)
		str[i++] = '0';
	while (num != 0)
	{
		if (num % base < 10)
			str[i] = (num % base) + '0';
		else
			str[i] = ((num % base) - 10) + ofst;
		i++;
		num /= base;
	}
	*len = i;
	str[i] = '\0';
	return (ft_strrev(str), str);
}

static char	*convert_2_com(uint64_t num, int base, char ofst, int *len)
{
	char		*str;
	uint64_t	mask;

	mask = (1ULL << (sizeof(uint64_t) * 8)) - 1;
	num = ~num + 1;
	num &= mask;
	str = convert_b(num, base, ofst, len);
	return (str);
}

t_fdata	*convert_num(int64_t num, int base, char offset)
{
	int		is_neg;
	t_fdata	*data;

	data = ft_calloc(1, sizeof(t_fdata *));
	if (!data)
		return (NULL);
	is_neg = 0;
	if (num < 0)
	{
		is_neg = 1;
		num = -num;
	}
	if (is_neg && base == 16)
		data->fstring = convert_2_com(num, base, offset, &data->count);
	else
		data->fstring = convert_b(num, base, offset, &data->count);
	return (data);
}
