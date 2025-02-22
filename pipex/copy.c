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

static void	setup_fds(int *pipe_fd, int *in_out_fd, char **argv)
{
	in_out_fd[0] = open(argv[1], O_RDONLY);
	if (in_out_fd[0] < 0)
	{
		perror("open input file");
		exit(EXIT_FAILURE);
	}
	in_out_fd[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (in_out_fd[1] < 0)
	{
		perror("open output file");
		exit(EXIT_FAILURE);
	}
	if (pipe(pipe_fd) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

static void	cleanup_cmd(t_cmdline *cmds, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (cmds[i].cmd)
			free(cmds[i].cmd);
		if (cmds[i].cmd_args)
			free(cmds[i].cmd_args);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_cmdline	cmd[2];
	int			pipe_fd[2];
	int			in_out_fd[2];

	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex <inputf> <cmd1> <cmd2> <outputf>\n", 2);
		return (1);
	}
	setup_fds(pipe_fd, in_out_fd, argv);
	setup_cmd(&cmd[0], in_out_fd[0], argv[2], 1);
	extract_path(&cmd[0], env);
	run_command(&cmd[0], cmd[0].in_fd, pipe_fd[1], env);
	close(pipe_fd[1]);
	setup_cmd(&cmd[1], in_out_fd[1], argv[3], 0);
	extract_path(&cmd[1], env);
	run_command(&cmd[1], pipe_fd[0], cmd[1].out_fd, env);
	close(pipe_fd[0]);
	close(in_out_fd[0]);
	close(in_out_fd[1]);
	cleanup_cmd(cmd, 2);
	return (0);
}
