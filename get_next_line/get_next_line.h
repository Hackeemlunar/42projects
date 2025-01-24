/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:11:07 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/24 18:59:01 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_line
{
	char			*temp;
	struct s_line	*next;
	int				temp_len;
}				t_line;

typedef struct s_line_data
{
	char	*final_string;
	t_line	*templn;
	int		total_len;
}				t_ldata;

char	*get_next_line(int fd);

#endif