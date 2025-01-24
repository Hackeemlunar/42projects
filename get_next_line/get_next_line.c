#include "libft.h"
#include "get_next_line.h"

char *get_next_line(int fd)
{
    static char	*line;
    char		*buffer;
    char		*temp;
    int			read_bytes;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);
    read_bytes = read(fd, buffer, BUFFER_SIZE);
    while (read_bytes > 0)
    {
        buffer[read_bytes] = '\0';
        if (!line)
            line = ft_strdup(buffer);
        else
        {
            temp = ft_strjoin(line, buffer);
            free(line);
            line = temp;
        }
        if (ft_strchr(buffer, '\n'))
            break ;
        read_bytes = read(fd, buffer, BUFFER_SIZE);
    }
    free(buffer);
    return (line);
}