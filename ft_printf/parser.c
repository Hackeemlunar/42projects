/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 22:33:50 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/12 20:47:55 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

void	parse_format(const char *format, t_modinfo *info)
{
	const char	*ptr;

	info->width = -1;
	info->precision = -1;
	ptr = format;
	while (*ptr && ft_strchr("-+ #0", *ptr))
		info->flags[ft_strlen(info->flags)] = *ptr++;
	if (ft_isdigit(*ptr))
		info->width = ft_atoi(ptr);
	while (ft_isdigit(*ptr))
		ptr++;
	if (*ptr == '.')
	{
		ptr++;
		if (ft_isdigit(*ptr))
			info->precision = ft_atoi(ptr);
		else
			info->precision = 0;
		while (ft_isdigit(*ptr))
			ptr++;
	}
	if (ft_strchr("cspdiuxX%", *ptr))
		info->specifier = *ptr++;
}

t_fdata	*generate_string(void *arg, char c)
{
    t_fdata	*data;

    data = ft_calloc(1, sizeof(t_fdata));
    if (c == 'c')
    {
        data->fstring = ft_calloc(2, sizeof(char));
        data->fstring[0] = *(char *)arg;
        data->count = 1;
    }
    else if (c == 's')
    {
        data->fstring = ft_strdup((char *)arg);
        data->count = ft_strlen(data->fstring);
    }
    else if (c == 'p')
    {
        data->fstring = convert_b((uint64_t)arg, 16, 'a', &data->count);
        data->fstring = ft_strjoin("0x", data->fstring);
        data->count += 2;
    }
    else if (c == '%')
    {
        data->fstring = ft_calloc(2, sizeof(char));
        data->fstring[0] = '%';
        data->count = 1;
    }
    return data;
}

static t_fdata	*generate_num_data(void *arg, t_modinfo *info)
{
	if (info->specifier == 'i')
		return convert_num(*(int32_t *)arg, 10, 'a');
	else if (info->specifier == 'd')
		return convert_num(*(int64_t *)arg, 10, 'a');
	else if (info->specifier == 'u')
		return convert_num(*(uint64_t *)arg, 10, 'a');
	else if (info->specifier == 'x')
		return convert_num(*(int64_t *)arg, 16, 'a');
	else if (info->specifier == 'X')
		return convert_num(*(int64_t *)arg, 16, 'A');
	return NULL;
}

int	generate_data(void *arg, t_modinfo *info, t_fdata *data)
{
	if (info->specifier == 'c' || info->specifier == 's' ||
			 info->specifier == 'p' || info->specifier == '%')
		data = generate_string(arg, info->specifier);
	else if (info->specifier == 'i' || info->specifier == 'd' ||
			 info->specifier == 'u' || info->specifier == 'x' ||
			 info->specifier == 'X')
		data = generate_num_data(arg, info);
	else
		data = NULL;
	if (data)
		return (data->count);
	return (0);
}