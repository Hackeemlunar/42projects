/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:03:58 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/30 17:35:54 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_memcpy(char *dst, const char *src, size_t n)
{
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	if (n == 0)
		return (dst);
	while (n--)
		*d++ = *s++;
	return (dst);
}

void	cleanup_context(t_context **head, int fd)
{
	t_context	*prev;
	t_context	*curr;

	prev = NULL;
	curr = *head;
	while (curr && curr->fd != fd)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return ;
	if (prev)
		prev->next = curr->next;
	else
		*head = curr->next;
	if (curr->buffer)
		free(curr->buffer);
	free(curr);
}

char	*handle_eof_err(t_context **head_ref, t_context *ctx, ssize_t byt_read)
{
	char	*line;

	if (byt_read < 0 || (ctx->stash_len + ctx->buf_pos == 0))
		return (cleanup_context(head_ref, ctx->fd), NULL);
	line = malloc(ctx->stash_len + ctx->buf_pos + 1);
	if (!line)
		return (cleanup_context(head_ref, ctx->fd), NULL);
	ft_memcpy(line, ctx->stash, ctx->stash_len);
	ft_memcpy(line + ctx->stash_len, ctx->buffer, ctx->buf_pos);
	line[ctx->stash_len + ctx->buf_pos] = '\0';
	if (byt_read < 0)
		cleanup_context(head_ref, ctx->fd);
	else
	{
		ctx->stash_len = 0;
		ctx->buf_pos = 0;
		ctx->buf_pos_prv = 0;
		ctx->nl = 0;
	}
	return (line);
}

void	expand_buffer(t_context *ctx)
{
	char	*new_buffer;

	ctx->buf_cap *= 2;
	new_buffer = malloc(ctx->buf_cap + 1);
	if (!new_buffer)
	{
		ctx->err = 1;
		return ;
	}
	ft_memcpy(new_buffer, ctx->buffer, ctx->buf_pos);
	new_buffer[ctx->buf_pos] = '\0';
	if (ctx->buffer)
		free(ctx->buffer);
	ctx->buffer = new_buffer;
}

int	handle_stash(t_context *ctx, char **line)
{
	size_t	i;

	i = 0;
	while (i < ctx->stash_len)
	{
		if (ctx->stash[i] == '\n')
		{
			i++;
			ctx->nl = 1;
			*line = malloc(i + 1);
			if (!*line)
				return (0);
			ft_memcpy(*line, ctx->stash, i);
			(*line)[i] = '\0';
			ft_memcpy(ctx->stash, ctx->stash + i, ctx->stash_len - i);
			ctx->stash_len -= i;
			return (1);
		}
		i++;
	}
	return (0);
}
