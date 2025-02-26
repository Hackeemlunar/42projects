/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:06:18 by hmensah-          #+#    #+#             */
/*   Updated: 2025/02/24 20:06:21 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	cleanup_cmd(t_cmdline *cmds, int count)
{
	int		i;
	char	**args;

	if (!cmds)
		return ;
	i = -1;
	while (++i < count)
	{
		if (cmds[i].cmd_args)
		{
			args = cmds[i].cmd_args;
			while (*args)
				free(*args++);
			free(cmds[i].cmd_args);
		}
		free(cmds[i].cmd);
	}
	free(cmds);
}

static void	extract_path_dir(t_cmdline *cmd, char **dirs)
{
	char	*cmd_with_path;
	char	*temp;
	int		i;

	i = -1;
	while (dirs[++i])
	{
		temp = ft_strjoin(dirs[i], "/");
		cmd_with_path = ft_strjoin(temp, cmd->cmd);
		free(temp);
		if (access(cmd_with_path, F_OK) == 0)
		{
			free(cmd->cmd);
			cmd->cmd = cmd_with_path;
			free(cmd->cmd_args[0]);
			cmd->cmd_args[0] = cmd_with_path;
		}
		else
			free(cmd_with_path);
		free(dirs[i]);
	}
}

void	extract_path(t_cmdline *cmd, char **env)
{
	char	*path;
	char	**dirs;
	int		i;

	i = -1;
	path = NULL;
	while (env[++i])
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			path = env[i] + 5;
	if (!path)
		return ;
	dirs = ft_split(path, ':');
	extract_path_dir(cmd, dirs);
	free(dirs);
}

static void	setup_cmd(t_cmdline *cmd, char *full_cmd)
{
	ft_memset(cmd, 0, sizeof(t_cmdline));
	cmd->cmd_args = parse_cmd(full_cmd);
	if (!cmd->cmd_args)
	{
		ft_putstr_fd("Command parsing failed\n", 2);
		exit(EXIT_FAILURE);
	}
	cmd->cmd = ft_strdup(cmd->cmd_args[0]);
}

static void	safe_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(oldfd);
}

static void	exec_cmd(t_cmdline *cmd, char **env)
{
	execve(cmd->cmd, cmd->cmd_args, env);
	perror("execve");
	exit(EXIT_FAILURE);
}

static void	run_command(t_cmdline *cmd, int infd, int outfd, char **env)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		safe_dup2(infd, STDIN_FILENO);
		safe_dup2(outfd, STDOUT_FILENO);
		exec_cmd(cmd, env);
	}
	close(infd);
	close(outfd);
	waitpid(pid, NULL, 0);
}

static int	open_file(char *path, int flags, mode_t mode)
{
	int	fd;

	fd = open(path, flags, mode);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static void	here_doc(char *limiter)
{
	int		pipefd[2];
	char	*line;
	pid_t	pid;

	if (pipe(pipefd) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		while ((line = get_next_line(0)) != NULL)
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				break ;
			write(pipefd[1], line, ft_strlen(line));
			write(pipefd[1], "\n", 1);
			free(line);
		}
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
	close(pipefd[1]);
	waitpid(pid, NULL, 0);
	safe_dup2(pipefd[0], STDIN_FILENO);
}

static void	process_commands(t_cmdline *cmds, int count, int outfd, char **env)
{
	int	i;
	int	infd;
	int	pipefd[2];

	infd = STDIN_FILENO;
	i = -1;
	while (++i < count)
	{
		if (i == count - 1)
			outfd = outfd;
		else if (pipe(pipefd) < 0)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		run_command(&cmds[i], infd, (i == count-1) ? outfd : pipefd[1], env);
		if (i < count -1)
		{
			close(pipefd[1]);
			infd = pipefd[0];
		}
	}
	close(outfd);
}

int	main(int argc, char **argv, char **env)
{
	t_cmdline	*cmds;
	int			outfd;
	int			i;
	int			heredoc;

	heredoc = (argc > 1 && ft_strncmp(argv[1], "here_doc", 8) == 0);
	if (heredoc && argc < 6)
		ft_putstr_fd("Usage: ./pipex here_doc LIMITER cmd1..cmdn outfile\n", 2);
	else if (!heredoc && argc < 5)
		ft_putstr_fd("Usage: ./pipex infile cmd1..cmdn outfile\n", 2);
	if ((heredoc && argc < 6) || (!heredoc && argc < 5))
		exit(EXIT_FAILURE);

	const int cmd_count = heredoc ? argc - 4 : argc - 3;
	cmds = malloc(cmd_count * sizeof(t_cmdline));
	if (!cmds)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	if (heredoc)
	{
		here_doc(argv[2]);
		outfd = open_file(argv[argc-1], O_WRONLY|O_CREAT|O_APPEND, 0644);
		for (i = 0; i < cmd_count; i++)
			setup_cmd(&cmds[i], argv[3 + i]);
	}
	else
	{
		safe_dup2(open_file(argv[1], O_RDONLY, 0), STDIN_FILENO);
		outfd = open_file(argv[argc-1], O_WRONLY|O_CREAT|O_TRUNC, 0644);
		for (i = 0; i < cmd_count; i++)
			setup_cmd(&cmds[i], argv[2 + i]);
	}

	for (i = 0; i < cmd_count; i++)
		extract_path(&cmds[i], env);

	process_commands(cmds, cmd_count, outfd, env);
	cleanup_cmd(cmds, cmd_count);
	return (0);
}