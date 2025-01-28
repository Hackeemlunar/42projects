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
# define BUFFER_SIZE 1
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
    while (n > 0 && *s)
    {
        *d++ = *s++;
        n--;
    }
    while (n > 0)
    {
        *d++ = '\0';
        n--;
    }
    return dst;
}

void create_context(t_context *ctx)
{
    if (!ctx->buffer)
    {
        ctx->buf_cap = BUFFER_SIZE;
        ctx->buffer = malloc(ctx->buf_cap + 1);
        if (!ctx->buffer)
            return ;
        ctx->buffer[0] = '\0';
    }
}

char *handle_eof_err(t_context *ctx, ssize_t byt_read)
{
    char *line;

    if (byt_read < 0)
    {
        free(ctx->buffer);
        ctx->buffer = NULL;
        ctx->buf_cap = 0;
        return NULL;
    }
    if (ctx->stash_len + ctx->buf_pos == 0)
    {
        free(ctx->buffer);
        ctx->buffer = NULL;
        ctx->buf_cap = 0;
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
    free(ctx->buffer);
    ctx->buffer = NULL;
    ctx->buf_cap = 0;
    ctx->stash_len = 0;
    ctx->buf_pos = 0;
    ctx->buf_pos_prv = 0;
    return line;
}

void	expland_buffer(t_context *ctx)
{
    char	*new_buffer;

    ctx->buf_cap *= 2;
    new_buffer = malloc(ctx->buf_cap + 1);
    if (!new_buffer)
    {
        ctx->nl_err = 1;
        return ;
    }
    ft_strncpy(new_buffer, ctx->buffer, ctx->buf_pos);
    if (ctx->buffer)
        free(ctx->buffer);
    ctx->buffer = new_buffer;
}

void	fill_line(t_context *ctx, char *line)
{
    size_t remainder;
    char *buffer;

    remainder = ctx->buf_pos - ctx->buf_pos_prv;
    if (ctx->stash_len)
        ft_strncpy(line, ctx->stash, ctx->stash_len);
    ft_strncpy(line + ctx->stash_len, ctx->buffer, ctx->buf_pos_prv);
    line[ctx->stash_len + ctx->buf_pos_prv] = '\0';
    if (remainder)
    {
        ft_strncpy(ctx->stash, ctx->buffer + ctx->buf_pos_prv, remainder);
        ctx->stash_len = remainder;
    }
    else
        ctx->stash_len = 0;
    ctx->buf_pos_prv = 0;
    ctx->buf_pos = 0;
    buffer = malloc(ctx->buf_cap + 1);
    if (!buffer)
        return ;
    free(ctx->buffer);
    ctx->buffer = buffer;
}

void	handle_line(t_context *ctx, ssize_t byt_read, char **line)
{
    ctx->buf_pos += byt_read;
    while (ctx->buf_pos_prv < ctx->buf_pos)
    {
        if (ctx->buffer[ctx->buf_pos_prv] == '\n')
        {
            ctx->buf_pos_prv++;
            ctx->nl_err = 1;
            *line = malloc(ctx->stash_len + ctx->buf_pos_prv + 1);
            if (!*line)
                return ;
            fill_line(ctx, *line);
            return ;
        }
        ctx->buf_pos_prv++;
    }
    if (ctx->buf_pos == ctx->buf_cap)
        expland_buffer(ctx);
}

void	handle_stash(t_context *ctx, char **line)
{
    size_t i;

    i = 0;
    while (i < ctx->stash_len)
    {
        if (ctx->stash[i] == '\n')
        {
            i++;
            *line = malloc(i + 1);
            if (!*line)
                return ;
            ft_strncpy(*line, ctx->stash, i);
            (*line)[i] = '\0';
            ft_strncpy(ctx->stash, ctx->stash + i, ctx->stash_len - i);
            ctx->stash_len -= i;
            return ;
        }
        i++;
    }
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
    ctx.nl_err = 0;
	while (1)
    {
        if (ctx.stash_len)
        {
            handle_stash(&ctx, &line);
            if (line)
                return line;
        }
        byt_read = read(fd, ctx.buffer + ctx.buf_pos, BUFFER_SIZE);
        if (byt_read <= 0)
			return (handle_eof_err(&ctx, byt_read));
		handle_line(&ctx, byt_read, &line);
        if (ctx.nl_err)
			return (line);
    }
	return (line);
}


// int main(void) {
// 	int fd;
// 	char *line;

// 	fd = open("test.txt", O_RDONLY);
   
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	close(fd);
// 	return (0);
// }

int main(void) {
    int fd;
    int i;
    char *line;

    i = 1;
    fd = open("test.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return (i);
    }
    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}