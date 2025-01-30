/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:11:07 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/29 18:38:37 by hmensah-         ###   ########.fr       */
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
	int		err;
	int		nl;
	size_t	buf_cap;
	size_t	buf_pos;
	size_t	buf_pos_prv;
	size_t	stash_len;
	size_t	stash_st;
	char	stash[BUFFER_SIZE];
	char	*buffer;
}			t_context;

char		*get_next_line(int fd);
void		cleanup_context(t_context *ctx);
void		*ft_strncpy(char *dst, const char *src, size_t n);
char		*handle_eof_err(t_context *ctx, ssize_t byt_read);
void		expland_buffer(t_context *ctx);
void		handle_stash(t_context *ctx, char **line);

#endif