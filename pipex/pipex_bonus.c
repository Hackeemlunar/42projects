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

static void	extract_path_dir(t_cmdline *cmd, char **dirs)
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
			cmd->cmd_args[0] = cmd_with_path;
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
	char	*path;
	char	**dirs;
	int		i;

	i = -1;
	while (env[++i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = env[i] + 5;
			break ;
		}
	}
	dirs = ft_split(path, ':');
	extract_path_dir(cmd, dirs);
	free(dirs);
	dirs = NULL;
}

void	setup_cmd(t_cmdline *cmd, int fd, char *full_cmd, int is_input)
{
	ft_memset(cmd, 0, sizeof(t_cmdline));
	cmd->cmd_args = parse_cmd(full_cmd);
	if (!cmd->cmd_args)
	{
		ft_putstr_fd("Command parsing failed\n", 2);
		exit(EXIT_FAILURE);
	}
	cmd->cmd = cmd->cmd_args[0];
	if (is_input)
		cmd->in_fd = fd;
	else
		cmd->out_fd = fd;
}

void	safe_dup2(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
}

void	run_command(t_cmdline *cmd, int in_fd, int out_fd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		safe_dup2(in_fd, STDIN_FILENO);
		safe_dup2(out_fd, STDOUT_FILENO);
		execve(cmd->cmd, cmd->cmd_args, env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	if (waitpid(pid, NULL, 0) < 0)
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}
}

static void	setup_out_fd(int *out_fd, char **argv, int heredoc)
{
	int	lst_idx;

	lst_idx = 0;
	while (argv[lst_idx] != NULL)
		lst_idx++;
	if (!heredoc)
		*out_fd = open(argv[lst_idx - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		*out_fd = open(argv[lst_idx - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*out_fd < 0)
	{
		perror("open output file");
		exit(EXIT_FAILURE);
	}
}

static void	setup_in_fd(int *in_fd, char **argv)
{
	*in_fd = open(argv[1], O_RDONLY);
	if (*in_fd < 0)
	{
		perror("open input file");
		exit(EXIT_FAILURE);
	}
}

void	safe_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

static void	cleanup_cmd(t_cmdline *cmds, int count)
{
	int		i;
	char	**full_cmds;

	i = 0;
	while (i < count)
	{
		if (cmds[i].cmd_args)
		{
			full_cmds = cmds[i].cmd_args;
			while (*full_cmds)
			{
				free(*full_cmds);
				full_cmds++;
			}
			free(cmds[i].cmd_args);
			cmds[i].cmd_args = NULL;
		}
		i++;
	}
	free(cmds);
}

int check_heredoc(char *heredoc)
{
	int heredoc_len;

	heredoc_len = 8;
	if (ft_strncmp("here_doc", heredoc, heredoc_len) == 0)
		return (1);
	return (0);
}

void	pipe_cmd(t_cmdline *cmds, char **argv, char **env, int num_cmds)
{
	int		pipes[2][2];
	int		in_out_fd[2];
	int		i;

	safe_pipe(pipes[0]);
	setup_in_fd(&in_out_fd[0], argv);
	setup_out_fd(&in_out_fd[1], argv, 0);
	setup_cmd(&cmds[0], in_out_fd[0], argv[2], 1);
	extract_path(&cmds[0], env);
	run_command(&cmds[0], in_out_fd[0], pipes[0][1], env);
	close(pipes[0][1]);
	i = 1;
	while (i < num_cmds - 1)
	{
		safe_pipe(pipes[1]);
		setup_cmd(&cmds[i], pipes[0][0], argv[i + 2], 1);
		extract_path(&cmds[i], env);
		run_command(&cmds[i], pipes[0][0], pipes[1][1], env);
		close(pipes[0][0]);
		close(pipes[1][1]);
		pipes[0][0] = pipes[1][0];
		pipes[0][1] = pipes[1][1];
		i++;
	}
	setup_cmd(&cmds[num_cmds - 1], in_out_fd[1], argv[num_cmds + 1], 0);
	extract_path(&cmds[num_cmds - 1], env);
	run_command(&cmds[num_cmds - 1], pipes[0][0], cmds[i].out_fd, env);
	close(pipes[0][0]);
	close(in_out_fd[0]);
	close(in_out_fd[1]);
}

void write_until_limiter(int fd, char *limiter)
{
	char	*str;
	int		limiter_len;

	limiter_len = ft_strlen(limiter);
	str = get_next_line(0);
	while (ft_strncmp(limiter, str, limiter_len) != 0)
	{
		ft_putstr_fd(str, fd);
		free(str);
		str = get_next_line(0);
	}
	if (str)
		free(str);
}

void pipe_here_doc(t_cmdline *cmds, char **argv, char **env, int num_cmds)
{
	int		pipes[2][2];
	int		in_out_fd[2];
	int		i;

	safe_pipe(pipes[0]);
	safe_pipe(pipes[1]);
	write_until_limiter(pipes[0][1], argv[2]);
	setup_out_fd(&in_out_fd[1], argv, 1);
	setup_cmd(&cmds[0], pipes[0][0], argv[3], 1);
	extract_path(&cmds[0], env);
	close(pipes[0][1]);
	run_command(&cmds[0], pipes[0][0], pipes[1][1], env);
	i = 1;
	while (i < num_cmds - 1)
	{
		setup_cmd(&cmds[i], pipes[0][0], argv[i + 3], 1);
		extract_path(&cmds[i], env);
		run_command(&cmds[i], pipes[0][0], pipes[1][1], env);
		close(pipes[0][0]);
		close(pipes[1][1]);
		pipes[0][0] = pipes[1][0];
		pipes[0][1] = pipes[1][1];
		i++;
	}
	setup_cmd(&cmds[num_cmds - 1], in_out_fd[1], argv[num_cmds + 2], 0);
	extract_path(&cmds[num_cmds - 1], env);
	run_command(&cmds[num_cmds - 1], pipes[0][0], cmds[i].out_fd, env);
	close(pipes[0][0]);
	close(in_out_fd[0]);
	close(in_out_fd[1]);
}

int main(int argc, char **argv, char **env)
{
	t_cmdline	cmd[20];
	int			n;

	if (argc > 5 && check_heredoc(argv[1]))
	{
		n = argc - 4;
		pipe_here_doc(cmd, argv, env, n);
	}
	else if(argc > 4)
	{
		n = argc - 3;
		pipe_cmd(cmd, argv, env, n);
	}
	else
	{
		ft_putendl_fd("Usg: ./pipex infile cmd1 .. cmdn outfile", 2);
		ft_putstr_fd("Usg: ./pipex here_doc LIMITER cmdn .. cmd2 outfile", 2);
		return (1);
	}
	cleanup_cmd(cmd, n);
	return (0);
}
