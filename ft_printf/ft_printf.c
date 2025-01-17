/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:07:17 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/17 18:55:13 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_fdata	*fstring[256];
	int		cnt;
	int		i;
	int		j;

	cnt = 0;
	i = 0;
	j = 0;
	va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			fstring[j++] = process(&format[i++], va_arg(args, void *));
			continue ;
		}
		i++;
	}
	fstring[j] = NULL;
	va_end(args);
	print_string(format, fstring, &cnt);
	free_fstrings(fstring);
	return (cnt);
}

t_fdata	*process(const char *specs, void *arg)
{
	t_modinfo	*info;
	t_fdata		*data;

	info = ft_calloc(1, sizeof(t_modinfo *));
	if (!info)
		return (NULL);
	parse_format(specs, info);
	data = generate_data(arg, info);
	apply_precision(info, data);
	apply_width_and_flags(info, data);
	printf("aa: %s\n", data->fstring);
	return (data);
}

void	print_string(const char *format, t_fdata *arr[], int *cnt)
{
	int			i;
	int			print_status;
	char		*specifiers;

	i = -1;
	print_status = 1;
	specifiers = ft_strdup("cspdiuxX%");
	while (*format)
	{
		if (*format == '%' && arr[++i])
		{
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
	free(specifiers);
}

void	free_fstrings(t_fdata *arr[])
{
	while (*arr)
	{
		free(*arr);
		arr++;
	}
}

// void	printstruct(t_modinfo *info)
// {
// 	printf("    Flags: %s\n", info->flags);
// 	printf("    width: %d\n", info->width);
// 	printf("   length: %s\n", info->length);
// 	printf("   Specif: %c\n", info->specifier);
// 	printf("precision: %d\n", info->precision);
// }
