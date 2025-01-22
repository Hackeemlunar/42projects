/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_uns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:02:10 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/22 17:22:22 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_fdata	*handle_uns(t_modinfo *info, va_list args)
{
	long	nbr;
	t_fdata	*data;

	nbr = va_arg(args, long);
	data = create_number_data(info, nbr, 10);
	apply_precision(info, data);
	apply_plus_space_flag(info, data);
	apply_minus_flag(info, data);
	return (data);
}
