/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:07:17 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/20 14:41:37 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	reset_modinfo(t_modinfo *modinfo)
{
	ft_memset(modinfo, 0, sizeof(t_modinfo));
}

static void	print_n_free(t_fdata *data, int *cnt)
{
	ft_putstr_pf(data);
	*cnt += data->count;
	free(data->fstring);
	free(data);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	t_fdata		*data;
	t_modinfo	*info;
	int			cnt;
	int			i;

	cnt = 0;
	i = -1;
	info = (t_modinfo *)malloc(sizeof(t_modinfo));
	va_start(args, format);
	while (format[++i] != '\0')
	{
		if (format[i] == '%')
		{
			parse_format(format + i + 1, info);
			data = process_specifier(info, args);
			i += info->flags_count;
			reset_modinfo(info);
			print_n_free(data, &cnt);
		}
		else
		{
			ft_putchar_fd(format[i], 1);
			cnt++;
		}
	}
	free(info);
	va_end(args);
	return (cnt);
}
