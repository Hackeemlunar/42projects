/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:06:42 by hmensah-          #+#    #+#             */
/*   Updated: 2025/02/21 22:25:35 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	extract_path_dir(t_cmdline *cmd, char **dirs)
{
	int		i;
	char	*cmd_with_path;
	char	*temp;

	i = -1;
	while (dirs[++i] != NULL)
	{
		temp = ft_strjoin(dirs[i], "/");
		cmd_with_path = ft_strjoin(temp, cmd->cmd);
		free(temp);
		if (access(cmd_with_path, F_OK) == 0)
		{
			free(cmd->cmd);
			cmd->cmd = cmd_with_path;
		}
		else
		{
			free(cmd_with_path);
		}
		free(dirs[i]);
	}
}

void	extract_path(t_cmdline *cmd, char **env)
{
	char *path;
	char **dirs;
	int i;

	i = -1;
	while (env[++i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = env[i] + 5;
			break;
		}
	}
	dirs = ft_split(path, ':');
	extract_path_dir(cmd, dirs);
	dirs = NULL;
}

void setup_cmd(t_cmdline *cmd, int fd, char *full_cmd, int is_input)
{
	ft_memset(cmd, 0, sizeof(t_cmdline));
	cmd->cmd_args = parse_cmd(full_cmd);
	if (!cmd->cmd_args)
		return;
	cmd->cmd = cmd->cmd_args[0];
	if (is_input)
		cmd->in_fd = fd;
	else
		cmd->out_fd = fd;
}

int main(int argc, char **argv, char **env)
{
	t_cmdline cmd;
	int fd[2];
	int in_fd;
	int out_fd;
	pid_t pid;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex <inputf> <cmd1> <cmd2> <outputf>\n", 2);
		return 1;
	}

	in_fd = open(argv[1], O_RDONLY);
	out_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pipe(fd);

	setup_cmd(&cmd, in_fd, argv[2], 1);
	extract_path(&cmd, env);
	// First command (input side)
	if ((pid = fork()) == 0)
	{
		dup2(cmd.in_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		execve(cmd.cmd, cmd.cmd_args, NULL);
		exit(0);
	}
	close(fd[1]);

	waitpid(pid, NULL, 0);

	// Second command (output side)
	setup_cmd(&cmd, out_fd, argv[3], 0);
	extract_path(&cmd, env);
	if ((pid = fork()) == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(cmd.out_fd, STDOUT_FILENO);
		close(fd[1]);
		execve(cmd.cmd, cmd.cmd_args, NULL);
		exit(0);
	}
	close(fd[0]);
	waitpid(pid, NULL, 0);

	// Cleanup
	close(in_fd);
	close(out_fd);

	return 0;
}