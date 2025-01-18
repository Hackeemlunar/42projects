/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 22:33:50 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/17 18:19:30 by hmensah-         ###   ########.fr       */
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
	if (ft_strchr("cspdiuxX", *ptr))
		info->specifier = *ptr;
}

static t_fdata	*generate_string(void *arg, char c)
{
	t_fdata	*data;

	data = (t_fdata *)malloc(sizeof(t_fdata));
	if (!data)
		return (NULL);
	if (c == 'c')
	{
		data->fstring = (char *)malloc(2 * sizeof(char));
		data->fstring[0] = (char)arg;
		data->count = 1;
	}
	else if (c == 's')
	{
		data->fstring = ft_strdup((char *)arg);
		data->count = ft_strlen(data->fstring);
	}
	return (data);
}

static t_fdata	*generate_num_data(void *arg, t_modinfo *info)
{
	int		isneg;
	int		num;
	t_fdata	*data;

	num = (int64_t)arg;
	if ((int64_t)arg < 0 || num < 0)
		isneg = 1;
	else
		isneg = 0;
	data = NULL;
	if (info->specifier == 'i')
		data = convert_num(num, 10, 'a', isneg);
	else if (info->specifier == 'd')
		data = convert_num((int64_t)arg, 10, 'a', isneg);
	else if (info->specifier == 'u')
		data = convert_num((uint64_t)arg, 10, 'a', 0);
	else if (info->specifier == 'x')
		data = convert_num((uint64_t)arg, 16, 'a', 0);
	else if (info->specifier == 'X')
		data = convert_num((uint64_t)arg, 16, 'A', 0);
	return (data);
}

static t_fdata	*generate_p_string(void *arg)
{
	t_fdata	*data;
	char	*str;

	data = NULL;
	data = convert_num((uint64_t)arg, 16, 'a', 0);
	str = data->fstring;
	data->fstring = ft_strjoin("0x", str);
	data->count += 2;
	free(str);
	return (data);
}

t_fdata	*generate_data(void *arg, t_modinfo *info)
{
	t_fdata	*data;

	data = NULL;
	if (info->specifier == 'c' || info->specifier == 's')
		data = generate_string(arg, info->specifier);
	else if (info->specifier == 'p')
		data = generate_p_string(arg);
	else if (info->specifier == 'i' || info->specifier == 'd'
		|| info->specifier == 'u' || info->specifier == 'x'
		|| info->specifier == 'X')
		data = generate_num_data(arg, info);
	return (data);
}
