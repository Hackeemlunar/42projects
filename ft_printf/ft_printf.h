/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 20:14:43 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/15 20:14:34 by hmensah-         ###   ########.fr       */
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
	char	length[3];
	char	specifier;
}				t_modinfo;

int			ft_printf(const char *format, ...);
char		*process(const char *first, void *arr, int *count);
void		print_string(const char *format, char *arr[]);
void		free_fstrings(char *arr[]);
void		parse_format(const char *format, t_modinfo *info);
int			generate_data(void *arg, t_modinfo *info, t_fdata *data);
t_fdata		*convert_num(int64_t num, int base, char offset, int isneg);

#endif
