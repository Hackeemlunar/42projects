/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:54:23 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/30 17:30:33 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>

#define BUFFER_SIZE 10

typedef struct s_context {
    int fd;
    int err;
    int nl;
    size_t buf_cap;
    size_t buf_pos;
    size_t buf_pos_prv;
    size_t stash_len;
    size_t stash_st;
    char stash[BUFFER_SIZE];
    char *buffer;
    struct s_context *next;
} t_context;

void *ft_memcpy(char *dst, const char *src, size_t n)
{
    char *d = dst;
    const char *s = src;
    while (n--)
        *d++ = *s++;
    return dst;
}

void cleanup_context(t_context **head, int fd)
{
    t_context *prev = NULL;
    t_context *curr = *head;

    while (curr && curr->fd != fd) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) return;

    if (prev)
        prev->next = curr->next;
    else
        *head = curr->next;

    if (curr->buffer)
        free(curr->buffer);
    free(curr);
}

char *handle_eof_err(t_context **head_ref, t_context *ctx, ssize_t byt_read) {
    char *line;

    if (byt_read < 0 || (ctx->stash_len + ctx->buf_pos == 0)) {
        cleanup_context(head_ref, ctx->fd);
        return (NULL);
    }

    line = malloc(ctx->stash_len + ctx->buf_pos + 1);
    if (!line) {
        cleanup_context(head_ref, ctx->fd);
        return (NULL);
    }

    if (ctx->stash_len)
        ft_memcpy(line, ctx->stash, ctx->stash_len);
    if (ctx->buf_pos)
        ft_memcpy(line + ctx->stash_len, ctx->buffer, ctx->buf_pos);
    line[ctx->stash_len + ctx->buf_pos] = '\0';

    if (byt_read < 0) {
        cleanup_context(head_ref, ctx->fd);
    } else {
        ctx->stash_len = 0;
        ctx->buf_pos = 0;
        ctx->buf_pos_prv = 0;
        ctx->nl = 0;
    }

    return (line);
}

void expand_buffer(t_context *ctx) {
    char *new_buffer;

    ctx->buf_cap *= 2;
    new_buffer = malloc(ctx->buf_cap + 1);
    if (!new_buffer) {
        ctx->err = 1;
        return;
    }

    ft_memcpy(new_buffer, ctx->buffer, ctx->buf_pos);
    new_buffer[ctx->buf_pos] = '\0';

    if (ctx->buffer)
        free(ctx->buffer);
    ctx->buffer = new_buffer;
}

void handle_stash(t_context *ctx, char **line) {
    size_t i = 0;

    while (i < ctx->stash_len) {
        if (ctx->stash[i] == '\n') {
            i++;
            ctx->nl = 1;
            *line = malloc(i + 1);
            if (!*line)
                return;
            ft_memcpy(*line, ctx->stash, i);
            (*line)[i] = '\0';
            ft_memcpy(ctx->stash, ctx->stash + i, ctx->stash_len - i);
            ctx->stash_len -= i;
            return;
        }
        i++;
    }
}

void create_context(t_context *ctx) {
    ctx->err = 0;
    ctx->nl = 0;
    ctx->buf_cap = BUFFER_SIZE;
    ctx->buf_pos = 0;
    ctx->buf_pos_prv = 0;
    ctx->stash_len = 0;
    ctx->stash_st = 0;
    ctx->buffer = malloc(ctx->buf_cap + 1);
    if (!ctx->buffer) {
        ctx->err = 1;
        return;
    }
    ctx->buffer[0] = '\0';
}

void fill_line(t_context *ctx, char *line) {
    size_t remainder = ctx->buf_pos - ctx->buf_pos_prv;

    if (ctx->stash_len > 0)
        ft_memcpy(line, ctx->stash, ctx->stash_len);
    ft_memcpy(line + ctx->stash_len, ctx->buffer, ctx->buf_pos_prv);
    line[ctx->stash_len + ctx->buf_pos_prv] = '\0';

    if (remainder) {
        ft_memcpy(ctx->stash, ctx->buffer + ctx->buf_pos_prv, remainder);
        ctx->stash_len = remainder;
    } else {
        ctx->stash_len = 0;
    }

    ctx->buf_pos_prv = 0;
    ctx->buf_pos = 0;
}

void handle_line(t_context *ctx, ssize_t byt_read, char **line) {
    ctx->buf_pos += byt_read;

    while (ctx->buf_pos_prv < ctx->buf_pos) {
        if (ctx->buffer[ctx->buf_pos_prv] == '\n') {
            ctx->buf_pos_prv++;
            ctx->nl = 1;
            *line = malloc(ctx->stash_len + ctx->buf_pos_prv + 1);
            if (!*line)
                return;
            fill_line(ctx, *line);
            return;
        }
        ctx->buf_pos_prv++;
    }

    if (ctx->buf_pos == ctx->buf_cap)
        expand_buffer(ctx);
}

char *get_next_line(int fd) {
    static t_context *contexts = NULL;
    t_context *ctx = contexts;
    ssize_t byt_read;
    char *line = NULL;

    if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > LONG_MAX)
        return (NULL);

    while (ctx && ctx->fd != fd)
        ctx = ctx->next;

    if (!ctx) {
        ctx = malloc(sizeof(t_context));
        if (!ctx) return (NULL);
        ctx->fd = fd;
        ctx->next = contexts;
        contexts = ctx;
        create_context(ctx);
        if (ctx->err) {
            cleanup_context(&contexts, fd);
            return (NULL);
        }
    }

    while (!ctx->err && !ctx->nl) {
        if (ctx->stash_len) {
            handle_stash(ctx, &line);
            if (line) {
                ctx->nl = 0;
                return (line);
            }
        }

        byt_read = read(fd, ctx->buffer + ctx->buf_pos, BUFFER_SIZE);
        if (byt_read <= 0) {
            line = handle_eof_err(&contexts, ctx, byt_read);
            return (line);
        }

        handle_line(ctx, byt_read, &line);
        if (line) {
            ctx->nl = 0;
            return (line);
        }
    }

    if (ctx->err) {
        cleanup_context(&contexts, fd);
        return (NULL);
    }

    return (line);
}

int main(void) {
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return (1);
    }

    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}