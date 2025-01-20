/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_uns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:02:10 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/20 15:05:45 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_fdata	*handle_uns(t_modinfo *modinfo, va_list args)
{
	long	nbr;

	nbr = va_arg(args, long);
	return (create_number_data(modinfo, nbr, 10));
}
