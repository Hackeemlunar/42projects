/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:25:03 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/15 20:25:40 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "libft/libft.h"
// #include "ft_printf.h"

typedef struct s_formated_data
{
	int		count;
	char	*fstring;
}				t_fdata;

static void	convert_b(uint64_t n, int base, t_fdata *data, char ofs)
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

	data = ft_calloc(1, sizeof(t_fdata));
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

static t_fdata	*generate_p_string(void *arg)
{
	t_fdata	*data;
	char	*arg;

	data = ft_calloc(1, sizeof(t_fdata));
	data = convert_num((uint64_t)arg, 16, 'a', 0);
	data->fstring = ft_strjoin("0x", data->fstring);
	data->count += 2;
	return (data);
}

int main() {
	int64_t num = INT64_MAX;
	t_fdata *hex = generate_p_string(&num);
	if (hex != NULL) {
		printf("The 2's comp of %lld in hexadecimal is: %s len is %d\n", num, hex->fstring, hex->count);
		printf("The 2's comp of %lld in hexadecimal is: %p\n", num, &num);
		free(hex);
	}
	return (0);
}
