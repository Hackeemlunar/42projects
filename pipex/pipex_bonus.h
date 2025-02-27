/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:05:55 by hmensah-          #+#    #+#             */
/*   Updated: 2025/02/27 17:40:27 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft/libft.h"

typedef struct s_cmdline
{
	char	*cmd;
	char	**cmd_args;
	int		in_fd;
	int		out_fd;
}	t_cmdline;

char	**parse_cmd(char const *s);
void run_command(t_cmdline *cmd, int in_fd, int out_fd, char **env);
int check_heredoc(char *heredoc);
int get_heredoc_fd_setup(int *in_out_fd, char **argv, int num_cmds);
void cleanup_cmd(t_cmdline *cmds);
void write_until_limiter(char *limiter);
void extract_path(t_cmdline *cmd, char **env);
void setup_fd(int *fd, char *file, int flags, mode_t mode);

#endif
