/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dp.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:18:56 by hmensah-          #+#    #+#             */
/*   Updated: 2025/01/28 16:21:11 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

typedef struct s_read
{
	char            *buffer;
	size_t          buf_size;
	size_t          buf_pos;
	size_t          buf_end;
	struct s_read *next;
}           t_read;

typedef struct s_context
{
	int             fd;
	char            *stash;
	size_t          total_len;
	struct s_context *next;
}              t_context;

int main(void) {
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
   
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