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

static void	set_length_spec(const char *ptr, t_modinfo *info);

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
	set_length_spec(ptr, info);
}

static void	set_length_spec(const char *ptr, t_modinfo *info)
{
	if (ft_strchr("hljztL", *ptr))
	{
		info->length[0] = *ptr++;
		if ((*ptr == 'h' || *ptr == 'l') && info->length[0] == *ptr)
			info->length[1] = *ptr++;
	}
	if (ft_strchr("diouxXfFeEgGaAcspn%", *ptr))
		info->specifier = *ptr++;
}
