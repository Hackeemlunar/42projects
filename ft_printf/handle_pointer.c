/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:40:24 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/20 14:40:31 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_fdata	*handle_pointer(t_modinfo *modinfo, va_list args)
{
	t_fdata	*data;
	long	ptr;
	char	*ptr_str;

	ptr = va_arg(args, long);
	ptr_str = ft_itoa_base(ptr, 16, 0);
	if (!ptr_str)
		return (NULL);
	if (modinfo->precision == 0 && ptr == 0)
		ptr_str[0] = '\0';
	data = (t_fdata *)malloc(sizeof(t_fdata));
	if (!data)
	{
		free(ptr_str);
		return (NULL);
	}
	data->fstring = ptr_str;
	data->count = ft_strlen(ptr_str);
	apply_prefix(&ptr_str, "0x", data);
	apply_width_and_flags(modinfo, data);
	return (data);
}
