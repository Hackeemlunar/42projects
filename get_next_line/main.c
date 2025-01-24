#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    line = get_next_line(fd);
    printf("%s\n", line);
    free(line);
    close(fd);
    return (0);
}