/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:11:55 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/24 18:13:19 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_context *get_context(int fd, t_context **contexts)
{
    t_context *ctx;

    ctx = *contexts;
    while (ctx)
    {
        if (ctx->fd == fd)
            return ctx;
        ctx = ctx->next;
    }
    ctx = malloc(sizeof(t_context));
    if (!ctx)
        return NULL;
    ctx->fd = fd;
    ctx->buffer = malloc(BUFFER_SIZE);
    if (!ctx->buffer)
    {
        free(ctx);
        return NULL;
    }
    ctx->buf_size = BUFFER_SIZE;
    ctx->buf_pos = 0;
    ctx->buf_end = 0;
    ctx->next = *contexts;
    *contexts = ctx;
    return (ctx);
}

void remove_context(int fd, t_context **contexts)
{
    t_context *ctx;
    t_context *prev;

    ctx = *contexts;
    prev = NULL;
    while (ctx)
    {
        if (ctx->fd == fd)
        {
            if (prev)
                prev->next = ctx->next;
            else
                *contexts = ctx->next;
            free(ctx->buffer);
            free(ctx);
            return;
        }
        prev = ctx;
        ctx = ctx->next;
    }
}

void *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
    char *new_ptr;
    char *old_ptr;
    size_t i;

    new_ptr = malloc(new_size);
    if (new_ptr == NULL)
        return NULL;
    if (ptr == NULL)
        return new_ptr;
    old_ptr = (char *)ptr;
    i = 0;
    while (i < old_size && i < new_size)
    {
        new_ptr[i] = old_ptr[i];
        i++;
    }
    free(ptr);
    return (new_ptr);
}
