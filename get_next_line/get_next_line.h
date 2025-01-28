/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:11:07 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/28 16:05:18 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_context
{
	int					fd;
	char				*buffer;
	size_t				buf_size;
	size_t				buf_pos;
	size_t				buf_end;
	struct s_context	*next;
}				t_context;

char		*get_next_line(int fd);
t_context	*get_context(int fd, t_context **contexts);
void		remove_context(int fd, t_context **contexts);
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
size_t		calculate_line_length(t_context *ctx, char **newline);
char		*allocate_and_extract_line(t_context *ctx, size_t line_len);
char		*extract_line(t_context *ctx);
int			expand_buffer_if_needed(t_context *ctx);
char		*read_and_handle_line(int fd, t_context *ctx);
char		*read_until_line(int fd, t_context *ctx, t_context **contexts);

#endif