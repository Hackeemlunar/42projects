/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:02:47 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/29 19:02:50 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void create_context(t_context *ctx) {
    ctx->err = 0;
    ctx->nl = 0;
    if (!ctx->buffer) {
        ctx->buf_cap = BUFFER_SIZE;
        ctx->buffer = malloc(ctx->buf_cap + 1);
        if (!ctx->buffer) {
            ctx->err = 1;
            return;
        }
        ctx->buffer[0] = '\0';
    }
    ctx->buf_pos = 0;
    ctx->buf_pos_prv = 0;
    ctx->stash_len = 0;
    ctx->stash_st = 0;
}

void	fill_line(t_context *ctx, char *line)
{
	size_t	remainder;

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
}

void	handle_line(t_context *ctx, ssize_t byt_read, char **line)
{
	ctx->buf_pos += byt_read;
	while (ctx->buf_pos_prv < ctx->buf_pos)
	{
		if (ctx->buffer[ctx->buf_pos_prv] == '\n')
		{
			ctx->buf_pos_prv++;
			ctx->nl = 1;
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

char *get_next_line(int fd) {
    static t_context *contexts = NULL; // Static linked list head (function-scoped)
    t_context *ctx = contexts;
    t_context **prev_next = &contexts; // Pointer to the "next" pointer of the previous node
    ssize_t byt_read;
    char *line = NULL;

    // Validate FD and BUFFER_SIZE
    if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > LONG_MAX)
        return (NULL);

    // Search for existing context for this FD
    while (ctx && ctx->fd != fd) {
        prev_next = &ctx->next;
        ctx = ctx->next;
    }

    // Create new context if none exists
    if (!ctx) {
        ctx = malloc(sizeof(t_context));
        if (!ctx) return (NULL);
        ctx->fd = fd;
        ctx->next = contexts;
        contexts = ctx; // Add to the front of the list
        create_context(ctx); // Initialize buffer and state
        if (ctx->err) {
            cleanup_context(&contexts, fd);
            return (NULL);
        }
    }

    // Main logic (unchanged)
    while (!ctx->err && !ctx->nl) {
        if (ctx->stash_len) {
            handle_stash(ctx, &line);
            if (line) return (line);
        }
        byt_read = read(fd, ctx->buffer + ctx->buf_pos, BUFFER_SIZE);
        if (byt_read <= 0) {
            line = handle_eof_err(ctx, byt_read);
            cleanup_context(&contexts, fd); // Cleanup on EOF/error
            return (line);
        }
        handle_line(ctx, byt_read, &line);
    }
    if (ctx->err) {
        cleanup_context(&contexts, fd);
        return (NULL);
    }
    return (line);
}