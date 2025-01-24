/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:11:28 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/24 21:36:36 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*s_copy;
	int		i;

	i = 0;
	s_copy = (char *)b;
	while (i < (int)len)
	{
		s_copy[i] = c;
		i++;
	}
	return (b);
}

int	check_bytes(t_line *line, int *buf_size)
{
	t_line	new_line;
	int		i;

	i = 0;
	while (line->temp[i] != '\n' && line->temp[i])
		i++;
	if (i < line->temp_len)
	{
		line->temp_len = i;
		line->next = NULL;
		return (0);
	}
	ft_memset(&new_line, 0, sizeof(t_line));
	*buf_size *= 2;
	new_line.temp = malloc(*buf_size + 1);
	if (!new_line.temp)
		return (-1);
	line->next = &new_line;
	return (1);
}

char	*extract_line(t_ldata *line_data)
{
	t_line	*temp_line;
	char	*line;
	int		i;

	temp_line = line_data->templn;
	line = malloc(line_data->total_len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < line_data->total_len)
	{
		if (temp_line->temp && !(*temp_line->temp))
		{
			free(temp_line->temp);
			temp_line = temp_line->next;
		}
		if (temp_line->temp)
			line[i] = *(temp_line->temp);
		temp_line->temp++;
		i++;
	}
	line[line_data->total_len] = '\n';
	line[line_data->total_len + 1] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static t_ldata	ldata;
	t_line			line;
	int				buf_size;
	int				bytes_result;

	if (BUFFER_SIZE < 0 || fd < 0)
		return (NULL);
	buf_size = BUFFER_SIZE;
	ft_memset(&line, 0, sizeof(t_line));
	line.temp = malloc(buf_size + 1);
	if (!line.temp)
		return (NULL);
	line.temp_len = read(fd, line.temp, buf_size);
	ldata.total_len = 0;
	ldata.templn = &line;
	while (line.temp_len > 0)
	{
		printf("%d\n", line.temp_len);
		printf("%s\n", line.temp);
		line.temp[line.temp_len] = '\0';
		bytes_result = check_bytes(&line, &buf_size);
		ldata.total_len += line.temp_len;
		if (bytes_result == 0)
			break ;
		else if (bytes_result == -1)
			return (NULL);
		line = *line.next;
		line.temp_len = read(fd, line.temp, buf_size);
	}
	return (extract_line(&ldata));
}
