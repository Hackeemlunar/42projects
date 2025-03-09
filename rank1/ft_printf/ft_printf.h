/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 20:14:43 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/20 19:20:59 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdbool.h>
# include "libft/libft.h"

// ******* Data Structures *****************

typedef struct s_formated_data
{
	int		count;
	char	*fstring;
}				t_fdata;

typedef struct s_modifiers_info
{
	char	flags[5];
	int		width;
	int		precision;
	char	specifier;
	int		flags_count;
}				t_modinfo;

int		ft_printf(const char *format, ...);
void	parse_format(const char *fmt, t_modinfo *modinfo);
void	apply_precision(t_modinfo *modinfo, t_fdata *fdata);
void	apply_prefix(const char *str, t_modinfo *info, t_fdata *fdata);
void	ft_putstr_pf(t_fdata *data);
void	apply_minus_flag(t_modinfo *info, t_fdata *data);
t_fdata	*process_specifier(t_modinfo *modinfo, va_list args);
t_fdata	*handle_char(t_modinfo *modinfo, va_list args);
t_fdata	*handle_string(t_modinfo *modinfo, va_list args);
t_fdata	*handle_pointer(t_modinfo *modinfo, va_list args);
t_fdata	*handle_num_int(t_modinfo *modinfo, va_list args);
t_fdata	*handle_num_long(t_modinfo *modinfo, va_list args);
t_fdata	*handle_uns(t_modinfo *modinfo, va_list args);
t_fdata	*handle_hex(t_modinfo *modinfo, va_list args);
t_fdata	*handle_percent(t_modinfo *info);
t_fdata	*create_number_data(t_modinfo *modinfo, long nbr, int base);
char	*ft_itoa_base(long nbr, int base, int uppercase);
void	apply_left_justify(char *fstring, int width, t_fdata *fdata);
void	apply_r_justify(char *fstring, int width, char pad, t_fdata *fdata);
void	apply_r_justify(char *fstring, int width, char pad, t_fdata *fdata);
void	handle_string_size(char *fstring, int size, t_fdata *data);
void	handle_int_size(char *fstring, char pad, int size, t_fdata *data);
void	apply_plus_space_flag(t_modinfo *info, t_fdata *data);

#endif
