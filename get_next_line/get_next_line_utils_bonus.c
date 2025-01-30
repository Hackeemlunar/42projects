/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:03:58 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/29 19:04:01 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_strncpy(char *dst, const char *src, size_t n)
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
	return (dst);
}

void cleanup_context(t_context **head, int fd) {
    t_context *prev = NULL;
    t_context *curr = *head;

    // Find the context with the matching FD
    while (curr && curr->fd != fd) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) return; // Context not found

    // Remove from the linked list
    if (prev) prev->next = curr->next;
    else *head = curr->next;

    // Free resources
    if (curr->buffer) free(curr->buffer);
    free(curr);
}

char	*handle_eof_err(t_context *ctx, ssize_t byt_read)
{
	char	*line;

	if (byt_read < 0 || (ctx->stash_len + ctx->buf_pos == 0))
	{
		cleanup_context(&ctx, ctx->fd);
		return (NULL);
	}
	line = malloc(ctx->stash_len + ctx->buf_pos + 1);
	if (!line)
		return (NULL);
	if (ctx->stash_len)
		ft_strncpy(line, ctx->stash, ctx->stash_len);
	if (ctx->buf_pos)
		ft_strncpy(line + ctx->stash_len, ctx->buffer, ctx->buf_pos);
	line[ctx->stash_len + ctx->buf_pos] = '\0';
	cleanup_context(&ctx, ctx->fd);
	return (line);
}

void	expland_buffer(t_context *ctx)
{
	char	*new_buffer;

	ctx->buf_cap *= 2;
	new_buffer = malloc(ctx->buf_cap + 1);
	if (!new_buffer)
	{
		ctx->err = 1;
		return ;
	}
	ft_strncpy(new_buffer, ctx->buffer, ctx->buf_pos);
	if (ctx->buffer)
		free(ctx->buffer);
	ctx->buffer = new_buffer;
}

void	handle_stash(t_context *ctx, char **line)
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