/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:07:17 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/18 18:16:54 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

// void	printstruct(t_modinfo *info)
// {
// 	printf("    Flags: %s\n", info->flags);
// 	printf("    width: %d\n", info->width);
// 	printf("   Specif: %c\n", info->specifier);
// 	printf("precision: %d\n", info->precision);
// }

t_fdata	*process(const char *specs, void *arg)
{
	t_modinfo	*info;
	t_fdata		*data;
	info = (t_modinfo *)ft_calloc(1, sizeof(t_modinfo));
	if (!info)
		return (NULL);
	parse_format(specs, info);
	data = generate_data(arg, info);
	apply_precision(info, data);
	apply_width_and_flags(info, data);
	free(info);
	return (data);
}

void	print_string(const char *format, t_fdata *arr[], int *cnt)
{
	int			i;
	int			print_status;
	char		*specifiers;

	i = -1;
	print_status = 1;
	specifiers = "cspdiuxX%";
	while (*format)
	{
		if (*format == '%' && arr[++i])
		{
			if (*(format + 1) == '%')
			{
				ft_putstr_fd(arr[i]->fstring, 1);
				*cnt += arr[i]->count;
				format += 2;
				continue ;
			}
			ft_putstr_fd(arr[i]->fstring, 1);
			*cnt += arr[i]->count;
			print_status = 0;
		}
		else if (print_status)
		{
			ft_putchar_fd(*format, 1);
			*cnt += 1;
		}
		else if (ft_strchr(specifiers, *format))
			print_status = 1;
		format++;
	}
}

void	free_fstrings(t_fdata *arr[])
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]->fstring);
		free(arr[i]);
		i++;
	}
	arr = NULL;
}

static int	process_flag(const char **format, t_fdata **fstring, int *j)
{
	t_fdata	*data;

	if ((*format)[0] == '%' && (*format)[1] == '%')
	{
		data = (t_fdata *)ft_calloc(1, sizeof(t_fdata));
		data->fstring = (char *)ft_calloc(2, sizeof(char));
		data->fstring[0] = '%';
		data->count = 1;
		fstring[(*j)++] = data;
		(*format) += 2;
		return (1);
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	t_fdata		*fstring[256];
	const char	*ptr;
	int			cnt;
	int			j;

	cnt = 0;
	j = 0;
	ptr = format;
	va_start(args, format);
	while (*format != '\0')
	{
		if (process_flag(&format, fstring, &j))
			continue ;
		else if (*format == '%')
			fstring[j++] = process(format + 1, va_arg(args, void *));
		format++;
	}
	fstring[j] = NULL;
	va_end(args);
	print_string(ptr, fstring, &cnt);
	free_fstrings(fstring);
	return (cnt);
}
