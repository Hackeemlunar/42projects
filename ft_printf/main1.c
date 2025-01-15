#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>

char* twos_complement_to_hex_str(int64_t num) {
    const char* hex_digits = "0123456789ABCDEF";
    uint64_t result = (uint64_t)num;
    char* hex_str = (char*)malloc(17 * sizeof(char));
    if (hex_str != NULL) {
        int i = 15;
        while (i >= 0) {
            hex_str[i] = hex_digits[result & 0xF];
            result >>= 4;
            --i;
        }
        hex_str[16] = '\0';

        // Remove leading zeros
        i = 0;
        while (hex_str[i] == '0' && i < 15) {
            ++i;
        }
        return hex_str + i;
    }
    return hex_str;
}

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
    int         i;

    // Directly assign the maximum value for a 64-bit unsigned integer
    mask = UINT64_MAX;

    // Calculate the two's complement
    num = ~num + 1;
    num &= mask;

    // Convert the two's complement number to the desired base
    str = convert_b(num, base, ofst, len);

    // Remove leading zeros
    i = 0;
    while (str[i] == '0' && i < *len - 1)
    {
        ++i;
    }
    return str + i;
}

t_fdata	*convert_numm(int64_t num, int base, char offset)
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


int main() {
    int64_t num = 9999999999999999;
    t_fdata *hex_str = convert_numm(num, 16, 'A');
    if (hex_str != NULL) {
        printf("The two's complement of %ld in hexadecimal is: %s\n", num, hex_str->fstring);
        printf("The two's complement of %ld in hexadecimal is: %X\n", num, num);
        free(hex_str);
    }
    return 0;
}