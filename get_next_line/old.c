/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:54:23 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/28 18:27:28 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
typedef struct s_context
{
    size_t buf_cap;
    size_t buf_pos;
    size_t buf_pos_prv;
    size_t nl_pos;
    size_t stash_len;
    size_t stash_st;
    char *stash;
    char *buffer;
} t_context;

#define BUFFER_SIZE 10

void *ft_strncpy(char *dst, const char *src, size_t n)
{
    char *d = dst;
    const char *s = src;

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

void free_context(t_context *ctx)
{
    if (!ctx)
        return;
    if (ctx->stash)
        free(ctx->stash);
    if (ctx->buffer)
        free(ctx->buffer);
    free(ctx);
}

t_context *create_context(void)
{
    t_context *ctx;

    ctx = malloc(sizeof(t_context));
    if (!ctx)
        return NULL;
    ctx->buf_cap = BUFFER_SIZE;
    ctx->stash = malloc(ctx->buf_cap + 1);
    if (!ctx->stash)
    {
        free(ctx);
        return NULL;
    }
    ctx->stash[0] = '\0';
    ctx->buffer = malloc(ctx->buf_cap);
    if (!ctx->buffer)
    {
        free(ctx->stash);
        free(ctx);
        return NULL;
    }
    return ctx;
}

char *handle_eof(t_context *ctx)
{
    char *line;

    if (!ctx || (!ctx->stash_len && !ctx->buf_pos))
        return NULL;
    line = malloc(ctx->stash_len + ctx->buf_pos + 1);
    if (!line)
        return NULL;
    if (ctx->stash_len)
        ft_strncpy(line, ctx->stash, ctx->stash_len);
    if (ctx->buf_pos)
        ft_strncpy(line + ctx->stash_len, ctx->buffer, ctx->buf_pos);
    line[ctx->stash_len + ctx->buf_pos] = '\0';
    free_context(ctx);
    return line;
}

int expand_buffer(t_context *ctx)
{
    char *new_buffer;

    ctx->buf_cap *= 2;
    new_buffer = malloc(ctx->buf_cap);
    if (!new_buffer)
        return 0;
    ft_strncpy(new_buffer, ctx->buffer, ctx->buf_pos);
    free(ctx->buffer);
    ctx->buffer = new_buffer;
    return 1;
}

size_t check_stash(t_context *ctx)
{
    if (!ctx || !ctx->stash)
        return 0;
    while (ctx->nl_pos < ctx->stash_len)
    {
        if (ctx->stash[ctx->nl_pos] == '\n')
            return 1;
        ctx->nl_pos++;
    }
    ctx->stash_st = 1;
    return 0;
}

void copy_to_stash(t_context *ctx)
{
    ctx->stash_len = 0;
    if (ctx->buf_pos_prv < ctx->buf_pos)
    {
        ft_strncpy(ctx->stash, ctx->buffer + ctx->buf_pos_prv,
            ctx->buf_pos - ctx->buf_pos_prv);
        ctx->stash_len = ctx->buf_pos - ctx->buf_pos_prv;
        ctx->stash[ctx->stash_len] = '\0';
    }
    else
    {
        ctx->stash_len = 0;
        ctx->stash[0] = '\0';
    }
    ctx->buf_pos_prv = 0;
    ctx->buf_pos = 0;
    ctx->nl_pos = 0;
    ctx->stash_st = 0;
}

size_t process_newline(t_context *ctx, char **line)
{
    *line = malloc(ctx->nl_pos + 2);
    if (!*line)
        return 0;
    ft_strncpy(*line, ctx->stash, ctx->nl_pos + 1);
    (*line)[ctx->nl_pos + 1] = '\0';
    ft_strncpy(ctx->stash, ctx->stash + ctx->nl_pos + 1,
        ctx->stash_len - ctx->nl_pos - 1);
    ctx->stash_len -= ctx->nl_pos + 1;
    ctx->nl_pos = 0;
    return 1;
}

size_t find_nl(t_context *ctx, ssize_t bytes_read, char **line)
{
    ctx->buf_pos += bytes_read;
    if (!ctx->stash_st && check_stash(ctx))
        return process_newline(ctx, line);
    while (ctx->buf_pos_prv < ctx->buf_pos)
    {
        if (ctx->buffer[ctx->buf_pos_prv] == '\n')
        {
            *line = malloc(ctx->stash_len + ctx->buf_pos_prv + 2);
            if (!*line)
                return 0;
            ft_strncpy(*line, ctx->stash, ctx->stash_len);
            ft_strncpy(*line + ctx->stash_len, ctx->buffer,
                ctx->buf_pos_prv + 1);
            (*line)[ctx->stash_len + ctx->buf_pos_prv + 1] = '\0';
            ctx->buf_pos_prv++;
            copy_to_stash(ctx);
            return 1;
        }
        ctx->buf_pos_prv++;
    }
    if (ctx->buf_pos == ctx->buf_cap && !expand_buffer(ctx))
        return 0;
    return 0;
}

char *get_next_line(int fd)
{
    static t_context *ctx;
    ssize_t bytes_read;
    char *line;

    line = NULL;
    if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > LONG_MAX)
        return NULL;
    if (!ctx)
        ctx = create_context();
    if (!ctx)
        return NULL;
    while (1)
    {
        bytes_read = read(fd, ctx->buffer + ctx->buf_pos, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            free_context(ctx);
            ctx = NULL;
            return NULL;
        }
        if (bytes_read == 0)
        {
            line = handle_eof(ctx);
            ctx = NULL;
            return line;
        }
        if (find_nl(ctx, bytes_read, &line))
            break;
    }
    return line;
}

int main(void) {
    int fd;
    int i;
    char *line;

    i = 1;
    fd = open("test.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
    }
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
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