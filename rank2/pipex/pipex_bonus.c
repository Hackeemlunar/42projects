/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:06:18 by hmensah-          #+#    #+#             */
/*   Updated: 2025/02/27 18:46:17 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	safe_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

static void	setup_cmd(t_cmdline *cmd, int fd, char *full_cmd, int is_input)
{
	ft_memset(cmd, 0, sizeof(t_cmdline));
	cmd->cmd_args = parse_cmd(full_cmd);
	if (!cmd->cmd_args)
	{
		ft_putstr_fd("Command parsing failed\n", 2);
		cleanup_cmd(cmd);
		exit(EXIT_FAILURE);
	}
	cmd->cmd = cmd->cmd_args[0];
	if (is_input)
		cmd->in_fd = fd;
	else
		cmd->out_fd = fd;
}

int	execute_pipeline(t_cmdline *cmds, char **argv, char **env, int num_cmds)
{
	int	pipes[2];
	int	in_out_fd[2];
	int	heredoc;
	int	i;

	heredoc = get_heredoc_fd_setup(in_out_fd, argv, num_cmds);
	i = -1;
	while (++i < num_cmds)
	{
		if (i < num_cmds - 1)
			safe_pipe(pipes);
		setup_cmd(&cmds[i], in_out_fd[0], argv[i + 2 + heredoc], 1);
		extract_path(&cmds[i], env);
		if (i == num_cmds - 1)
			run_command(&cmds[i], cmds[i].in_fd, in_out_fd[1], env);
		else
			run_command(&cmds[i], cmds[i].in_fd, pipes[1], env);
		cleanup_cmd(&cmds[i]);
		if (i > 0)
			close(in_out_fd[0]);
		if (i < num_cmds - 1)
		{
			close(pipes[1]);
			in_out_fd[0] = pipes[0];
		}
	}
	return (close(in_out_fd[1]), close(in_out_fd[0]), 0);
}

int	main(int argc, char **argv, char **env)
{
	t_cmdline	cmds[20];
	int			num_cmds;

	if (argc > 5 && check_heredoc(argv[1]))
	{
		num_cmds = argc - 4;
		write_until_limiter(argv[2]);
	}
	else if (argc > 4 && !check_heredoc(argv[1]))
		num_cmds = argc - 3;
	else
	{
		ft_putendl_fd("Usg: ./pipex infile cmd1 . cmdn outfile", 2);
		ft_putendl_fd("Usg: ./pipex here_doc LIMITER cmd1 . cmdn outfile", 2);
		return (1);
	}
	execute_pipeline(cmds, argv, env, num_cmds);
	return (0);
}
