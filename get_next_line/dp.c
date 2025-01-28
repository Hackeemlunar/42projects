/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dp.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:18:56 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/28 23:24:41 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

typedef struct s_context
{
    size_t buf_cap;
    size_t buf_pos;
    size_t buf_pos_prv;
    size_t nl_err;
    size_t stash_len;
    size_t stash_st;
    char stash[BUFFER_SIZE];
    char *buffer;
} t_context;

void *ft_strncpy(char *dst, const char *src, size_t n)
{
    char		*d;
    const char	*s;

	d = dst;
	s = src;
    while (n > 0 && *s) {
        *d++ = *s++;
        n--;
    }
    while (n > 0) {
        *d++ = '\0';
        n--;
    }
    return dst;
}

void	create_context(t_context *ctx)
{
	char	*buffer;

	if (!ctx->buf_cap)
		ctx->buf_cap = BUFFER_SIZE;
	buffer =  malloc(ctx->buf_cap + 1);
	if (!buffer)
		return ;
	buffer[0] = '\0';
	ctx->buffer = buffer;
}
char	*handle_eof_err(t_context *ctx, ssize_t byt_read)
{
    char *line;

	if (byt_read < 0)
    {
        if (ctx->buffer)
			free(ctx->buffer);
        ctx = NULL;
        return NULL;
    }
    line = malloc(ctx->stash_len + ctx->buf_pos + 1);
    if (!line)
        return NULL;
    if (ctx->stash_len)
        ft_strncpy(line, ctx->stash, ctx->stash_len);
    if (ctx->buf_pos)
        ft_strncpy(line + ctx->stash_len, ctx->buffer, ctx->buf_pos);
    line[ctx->stash_len + ctx->buf_pos] = '\0';
    if (ctx->buffer)
		free(ctx->buffer);
	ctx = NULL;
    return line;
}

char	*get_next_line(int fd)
{
	static t_context	ctx;
	ssize_t				byt_read;
	char				*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > LONG_MAX)
        return NULL;
	create_context(&ctx);
	while (1)
    {
        byt_read = read(fd, ctx.buffer + ctx.buf_pos, BUFFER_SIZE);
        if (byt_read <= 0)
			return (handle_eof_err(&ctx, byt_read));
        else if (ctx.nl_err)
			return (line);
		handle_line(&ctx, byt_read, &line);
    }
	return (line);
}


int main(void) {
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
   
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	close(fd);
	return (0);
}

// int main(void) {
//     int fd;
//     int i;
//     char *line;

//     i = 1;
//     fd = open("test.txt", O_RDONLY);
//     if (fd < 0) {
//         perror("open");
//         return (i);
//     }
//     while ((line = get_next_line(fd)) != NULL) {
//         printf("%s", line);
//         free(line);
//     }
//     close(fd);
//     return (0);
// }