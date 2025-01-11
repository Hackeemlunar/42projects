#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdbool.h>

int ft_printf(const char *, ...);


// ******* Data Structures *****************

typedef struct  s_formated_data
{
	int     count;
	char*   fstring;
}               t_fdata;
typedef struct  s_modifiers_info
{
	bool	flag;
	bool	width;
	bool	precision;
	bool	modifiers;
}               t_modinfo;

t_fdata* new_fdata();
t_modinfo* new_modinfo();

#endif
