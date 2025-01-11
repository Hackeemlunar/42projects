/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:07:17 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/11 23:33:11 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	char	*fstring[256];
	int		count;
	int		i;
	int		j;

	count = 0;
	i = -1;
	j = 0;
	va_start(args, format);
	while (format[++i] != '\0')
	{
		if (format[i] == '%')
			fstring[j++] = process_s(&format[i], va_arg(args, void *), &count);
	}
	fstring[j] = NULL;
	va_end(args);
	print_string(format, fstring);
	free_fstrings(fstring);
	return (count);
}

char	*process_s(const char *specs, void *arg, int *count)
{
	t_modinfo	*info;
	t_fdata		*data;

	parse_format(specs, info);
	generate_data(arg, info, data);
	*count += data->count;
	return (data->fstring);
}

void	print_string(const char *format, char *arr[])
{
	int			i;
	int			print_status;
	const char	*specifiers;
	char		*temp;

	i = 0;
	print_status = 1;
	temp = ft_strdup("diuoxXfeEgGaAcspn%");
	specifiers = temp;
	while (*format)
	{
		if (*format == '%')
		{
			ft_putstr_fd(arr[i++], 1);
			print_status = 0;
		}
		else if (print_status)
			ft_putchar_fd(*format, 1);
		else if (ft_strchr(specifiers, *format))
			print_status = 1;
		format++;
	}
	free(temp);
}

void	free_fstrings(char *arr[])
{
	while (*arr)
	{
		free(*arr);
		arr++;
	}
}
