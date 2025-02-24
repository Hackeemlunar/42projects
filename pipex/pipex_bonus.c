/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:06:18 by hmensah-          #+#    #+#             */
/*   Updated: 2025/02/23 17:23:46 by hmensah-         ###   ########.fr       */
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

static void cleanup_cmd(t_cmdline **cmds, int count)
{
	int		i;
	char	**full_cmds;

	i = 0;
	while (i < count)
	{
		if (cmds[i]->cmd_args)
		{
			full_cmds = cmds[i]->cmd_args;
			while (*full_cmds)
			{
				free(*full_cmds);
				full_cmds++;
			}
			free(cmds[i]->cmd_args);
			cmds[i]->cmd_args = NULL;
		}
		i++;
	}
	free(cmds);
}

int check_heredoc(char **argv)
{
	int heredoc_len;

	heredoc_len = 8;
	if (ft_strncmp("here_doc", argv[1], heredoc_len) == 0)
		return (1);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	t_cmdline	**cmd;
	int			n;
	char		*lines;

	if (argc > 5 && check_heredoc(argv))
	{
		cmd = malloc(sizeof(t_cmdline *) * (argc - 4));
	}
	else if(argc > 4)
	{
		cmd = malloc(sizeof(t_cmdline *) * (argc - 4));
	}
	else
	{
		ft_putendl_fd("Usg: ./pipex infile cmd1 .. cmdn outfile", 2);
		ft_putstr_fd("Usg: ./pipex here_doc LIMITER cmdn .. cmd2 outfile", 2);
		return (1);
	}
	free(cmd);
	return (0);
}