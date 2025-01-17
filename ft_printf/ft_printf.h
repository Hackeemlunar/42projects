/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 20:14:43 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/17 16:42:16 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdbool.h>

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
}				t_modinfo;

int			ft_printf(const char *format, ...);
t_fdata		*process(const char *first, void *arr);
void		print_string(const char *format, t_fdata *arr[], int *cnt);
void		free_fstrings(t_fdata *arr[]);
void		parse_format(const char *format, t_modinfo *info);
t_fdata		*generate_data(void *arg, t_modinfo *info);
t_fdata		*convert_num(int64_t num, int base, char offset, int isneg);
void		apply_precision(t_modinfo *modinfo, t_fdata *fdata);
void		apply_width_and_flags(t_modinfo *modinfo, t_fdata *fdata);

#endif
