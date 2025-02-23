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

// static void	setup_fds(int *pipe_fd, int *in_out_fd, char **argv)
// {
// 	in_out_fd[0] = open(argv[1], O_RDONLY);
// 	if (in_out_fd[0] < 0)
// 	{
// 		perror("open input file");
// 		exit(EXIT_FAILURE);
// 	}
// 	in_out_fd[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (in_out_fd[1] < 0)
// 	{
// 		perror("open output file");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (pipe(pipe_fd) < 0)
// 	{
// 		perror("pipe");
// 		exit(EXIT_FAILURE);
// 	}
// }

// static void	cleanup_cmd(t_cmdline *cmds, int count)
// {
// 	int		i;
// 	char	**full_cmds;

// 	i = 0;
// 	while (i < count)
// 	{
// 		if (cmds[i].cmd_args)
// 		{
// 			full_cmds = cmds[i].cmd_args;
// 			while (*full_cmds)
// 			{
// 				free(*full_cmds);
// 				full_cmds++;
// 			}
// 			free(cmds[i].cmd_args);
// 			cmds[i].cmd_args = NULL;
// 		}
// 		i++;
// 	}
// }

int check_heredoc(char **argv)
{
	if (ft_strncmp("here_doc", argv[1], 8) == 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_cmdline	cmd[2];
	int			pipe_fd[2];
	int			in_out_fd[2];
	char		*str;

	if (check_heredoc(argv))
	{
		str = get_next_line(0);
		while (ft_strncmp(str, argv[2], ft_strlen(str) - 1))
		{
			ft_printf("%s\n", str);
			str = get_next_line(0);
		}
	}
	
	return (0);
}