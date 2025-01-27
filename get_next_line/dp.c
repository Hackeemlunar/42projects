
#include "get_next_line.h"

static t_context *get_context(int fd, t_context **contexts)
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
    if (!ctx->buffer) {
        free(ctx);
        return NULL;
    }
    ctx->buf_size = BUFFER_SIZE;
    ctx->buf_pos = 0;
    ctx->buf_end = 0;
    ctx->next = *contexts;
    *contexts = ctx;
    return ctx;
}

static void remove_context(int fd, t_context **contexts)
{
    t_context *ctx = *contexts;
    t_context *prev = NULL;

    while (ctx) {
        if (ctx->fd == fd) {
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

static size_t calculate_line_length(t_context *ctx, char **newline)
{
    size_t line_len = 0;
    *newline = NULL;
    while (ctx->buf_pos + line_len < ctx->buf_end) {
        if (ctx->buffer[ctx->buf_pos + line_len] == '\n') {
            line_len++;
            *newline = &ctx->buffer[ctx->buf_pos + line_len - 1];
            break;
        }
        line_len++;
    }
    if (!*newline && ctx->buf_pos < ctx->buf_end)
        line_len = ctx->buf_end - ctx->buf_pos;
    return line_len;
}

static char *allocate_and_extract_line(t_context *ctx, size_t line_len)
{
    char *line;
    size_t i;

    if (line_len == 0) {
        return NULL;
    }
    line = malloc(line_len + 1);
    if (line == NULL) {
        return NULL;
    }
    i = 0;
    while (i < line_len) {
        line[i] = ctx->buffer[ctx->buf_pos + i];
        i++;
    }
    line[line_len] = '\0';
    ctx->buf_pos += line_len;
    if (ctx->buf_pos >= ctx->buf_end) {
        ctx->buf_pos = 0;
        ctx->buf_end = 0;
    }
    return line;
}


static char *extract_line(t_context *ctx)
{
    char *newline;
    size_t line_len;

    line_len = calculate_line_length(ctx, &newline);
    return allocate_and_extract_line(ctx, line_len);
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
    return new_ptr;
}


static int expand_buffer_if_needed(t_context *ctx)
{
    size_t available = ctx->buf_size - ctx->buf_end;
    if (available < BUFFER_SIZE)
    {
        size_t required_size = ctx->buf_end + BUFFER_SIZE;
        size_t new_size = ctx->buf_size;
        while (new_size < required_size)
            new_size *= 2;
        char *new_buf = ft_realloc(ctx->buffer, ctx->buf_size, new_size);
        if (!new_buf)
            return 0;
        ctx->buffer = new_buf;
        ctx->buf_size = new_size;
    }
    return 1;
}

static char *read_and_handle_line(int fd, t_context *ctx)
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
    return extract_line(ctx);
}

static char *read_until_line(int fd, t_context *ctx, t_context **contexts)
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
            return line;
        }
    }
}

char *get_next_line(int fd)
{
    static t_context *contexts = NULL;
    t_context *ctx;

    if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
        return NULL;
    ctx = get_context(fd, &contexts);
    if (!ctx)
        return NULL;
    return read_until_line(fd, ctx, &contexts);
}

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