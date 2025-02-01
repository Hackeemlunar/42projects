/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:03:33 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/30 17:28:21 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct s_context
{
	int					fd;
	int					err;
	int					nl;
	size_t				buf_cap;
	size_t				buf_pos;
	size_t				buf_pos_prv;
	size_t				stash_len;
	size_t				stash_st;
	char				stash[BUFFER_SIZE];
	char				*buffer;
	struct s_context	*next;
}				t_context;

char	*get_next_line(int fd);
void	*ft_memcpy(char *dst, const char *src, size_t n);
char	*handle_eof_err(t_context **head, t_context *ctx, ssize_t read);
void	expand_buffer(t_context *ctx);
int		handle_stash(t_context *ctx, char **line);
void	cleanup_context(t_context **head, int fd);

#endif