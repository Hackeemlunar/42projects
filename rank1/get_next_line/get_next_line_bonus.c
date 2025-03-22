/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:02:47 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/30 22:08:39 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	fill_line(t_context *ctx, char *line)
{
	size_t	remainder;

	remainder = ctx->buf_pos - ctx->buf_pos_prv;
	if (ctx->stash_len > 0)
		ft_memcpy(line, ctx->stash, ctx->stash_len);
	ft_memcpy(line + ctx->stash_len, ctx->buffer, ctx->buf_pos_prv);
	line[ctx->stash_len + ctx->buf_pos_prv] = '\0';
	if (remainder)
	{
		ft_memcpy(ctx->stash, ctx->buffer + ctx->buf_pos_prv, remainder);
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
		expand_buffer(ctx);
}

void	create_context(t_context *ctx)
{
	ctx->err = 0;
	ctx->nl = 0;
	ctx->buf_cap = BUFFER_SIZE;
	ctx->buf_pos = 0;
	ctx->buf_pos_prv = 0;
	ctx->stash_len = 0;
	ctx->stash_st = 0;
	ctx->buffer = malloc(ctx->buf_cap + 1);
	if (!ctx->buffer)
		ctx->err = 1;
	else
		ctx->buffer[0] = '\0';
}

static t_context	*get_or_create_context(t_context **head, int fd)
{
	t_context	*ctx;

	ctx = *head;
	while (ctx && ctx->fd != fd)
		ctx = ctx->next;
	if (!ctx)
	{
		ctx = malloc(sizeof(t_context));
		if (!ctx)
			return (NULL);
		ctx->fd = fd;
		ctx->next = *head;
		*head = ctx;
		create_context(ctx);
		if (ctx->err)
		{
			cleanup_context(head, fd);
			return (NULL);
		}
	}
	return (ctx);
}

char	*get_next_line(int fd)
{
	static t_context	*head = NULL;
	t_context			*ctx;
	ssize_t				byt_read;
	char				*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	ctx = get_or_create_context(&head, fd);
	if (!ctx)
		return (NULL);
	while (!ctx->err && !ctx->nl)
	{
		if (ctx->stash_len && handle_stash(ctx, &line))
			return (ctx->nl = 0, line);
		byt_read = read(fd, ctx->buffer + ctx->buf_pos, BUFFER_SIZE);
		if (byt_read <= 0)
			return (line = handle_eof_err(&head, ctx, byt_read), line);
		handle_line(ctx, byt_read, &line);
		if (line)
			return (ctx->nl = 0, line);
	}
	if (ctx->err)
		return (cleanup_context(&head, fd), NULL);
	return (line);
}
