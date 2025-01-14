/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:07:17 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/12 21:33:21 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	char	*fstring[256];
	int		cnt;
	int		i;
	int		j;

	cnt = 0;
	i = -1;
	j = 0;
	va_start(args, format);
	while (format[++i] != '\0')
	{
		if (format[i] == '%')
			fstring[j++] = process(&format[i + 1], va_arg(args, void *), &cnt);
	}
	fstring[j] = NULL;
	va_end(args);
	print_string(format, fstring);
	free_fstrings(fstring);
	return (cnt);
}

char	*process(const char *specs, void *arg, int *count)
{
	t_modinfo	info;
	t_fdata		data;

	ft_memset(&info, 0, sizeof(t_modinfo));
	ft_memset(&data, 0, sizeof(t_fdata));
	parse_format(specs, &info);
	generate_data(arg, &info, &data);
	*count += data.count;
	return (data.fstring);
}

void	print_string(const char *format, char *arr[])
{
	int			i;
	int			print_status;
	const char	*specifiers;
	char		*temp;

	i = 0;
	print_status = 1;
	temp = ft_strdup("cspdiuxX%");
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

// void	printstruct(t_modinfo *info)
// {
// 	printf("    Flags: %s\n", info->flags);
// 	printf("    width: %d\n", info->width);
// 	printf("   length: %s\n", info->length);
// 	printf("   Specif: %c\n", info->specifier);
// 	printf("precision: %d\n", info->precision);
// }
