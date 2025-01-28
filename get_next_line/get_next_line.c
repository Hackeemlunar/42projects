/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:11:28 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/24 22:43:59 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
    static t_context *contexts = NULL;
    t_context *ctx;

    if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
        return NULL;
    ctx = get_context(fd, &contexts);
    if (!ctx)
        return NULL;
    return (read_until_line(fd, ctx, &contexts));
}

char *read_until_line(int fd, t_context *ctx, t_context **contexts)
{
    char *line;

    while (1)
    {
        if (!expand_buffer_if_needed(ctx))
        {
            remove_context(fd, contexts);
            return NULL;
        }
        line = read_and_handle_line(fd, ctx);
        if (line || (ctx->buf_pos == 0 && ctx->buf_end == 0))
        {
            if (!line)
                remove_context(fd, contexts);
            return (line);
        }
    }
}

char *read_and_handle_line(int fd, t_context *ctx)
{
    ssize_t bytes_read;
    char    *current_buf;
    char    *line;

    current_buf = ctx->buffer + ctx->buf_end;
    bytes_read = read(fd, current_buf, BUFFER_SIZE);
    if (bytes_read < 0)
        return NULL;
    if (bytes_read == 0)
    {
        line = extract_line(ctx);
        if (!line && ctx->buf_pos < ctx->buf_end)
            line = extract_line(ctx);
        return line;
    }
    ctx->buf_end += bytes_read;
    return (extract_line(ctx));
}

char *extract_line(t_context *ctx)
{
    char *newline;
    size_t line_len;

    line_len = calculate_line_length(ctx, &newline);
    return (allocate_and_extract_line(ctx, line_len));
}

size_t calculate_line_length(t_context *ctx, char **newline)
{
    size_t line_len;

    *newline = NULL;
    line_len = 0;
    while (ctx->buf_pos + line_len < ctx->buf_end)
    {
        if (ctx->buffer[ctx->buf_pos + line_len] == '\n') {
            line_len++;
            *newline = &ctx->buffer[ctx->buf_pos + line_len - 1];
            break;
        }
        line_len++;
    }
    if (!*newline && ctx->buf_pos < ctx->buf_end)
        line_len = ctx->buf_end - ctx->buf_pos;
    return (line_len);
}

char *allocate_and_extract_line(t_context *ctx, size_t line_len)
{
    char *line;
    size_t i;

    if (line_len == 0)
        return NULL;
    line = malloc(line_len + 1);
    if (line == NULL)
        return NULL;
    i = 0;
    while (i < line_len)
    {
        line[i] = ctx->buffer[ctx->buf_pos + i];
        i++;
    }
    line[line_len] = '\0';
    ctx->buf_pos += line_len;
    if (ctx->buf_pos >= ctx->buf_end)
    {
        ctx->buf_pos = 0;
        ctx->buf_end = 0;
    }
    return (line);
}

int expand_buffer_if_needed(t_context *ctx)
{
    size_t  available;
    size_t  required_size;
    size_t  new_size;
    char    *new_buf;

    available = ctx->buf_size - ctx->buf_end;
    if (available < BUFFER_SIZE)
    {
        required_size = ctx->buf_end + BUFFER_SIZE;
        new_size = ctx->buf_size;
        while (new_size < required_size)
            new_size *= 2;
        new_buf = ft_realloc(ctx->buffer, ctx->buf_end, new_size);
        if (!new_buf)
            return 0;
        ctx->buffer = new_buf;
        ctx->buf_size = new_size;
    }
    return (1);
}
