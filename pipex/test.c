#include "pipex.h"

void safe_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

static void cleanup_cmd(t_cmdline *cmds)
{
	char **full_cmds;

	if (cmds->cmd_args)
	{
		full_cmds = cmds->cmd_args;
		while (*full_cmds)
		{
			free(*full_cmds);
			full_cmds++;
		}
		free(cmds->cmd_args);
		cmds->cmd_args = NULL;
	}
	if (access("/tmp/heredoc", F_OK) == 0)
		unlink("/tmp/heredoc");
}

void setup_cmd(t_cmdline *cmd, int fd, char *full_cmd, int is_input)
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

int check_heredoc(char *heredoc)
{
	int heredoc_len;

	heredoc_len = 8;
	if (ft_strncmp("here_doc", heredoc, heredoc_len) == 0)
		return (1);
	return (0);
}

static void extract_path_dir(t_cmdline *cmd, char **dirs)
{
	int i;
	char *cmd_with_path;
	char *temp;

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
			break;
		}
		free(cmd_with_path);
	}
	while (dirs[i])
		free(dirs[i++]);
}

void extract_path(t_cmdline *cmd, char **env)
{
	char *path = NULL;
	char **dirs;
	int i = 0;

	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = env[i] + 5;
			break;
		}
		i++;
	}
	if (!path)
		return;
	dirs = ft_split(path, ':');
	if (!dirs)
		return;
	extract_path_dir(cmd, dirs);
	free(dirs);
}

void safe_dup2(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(old_fd);
}

void run_command(t_cmdline *cmd, int in_fd, int out_fd, char **env)
{
	pid_t pid = fork();
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
		cleanup_cmd(cmd);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
	cleanup_cmd(cmd);
}

void setup_fd(int *fd, char *file, int flags, mode_t mode)
{
	*fd = open(file, flags, mode);
	if (*fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
}

void execute_pipeline(t_cmdline *cmds, char **argv, char **env, int num_cmds, int heredoc)
{
	int pipes[2];
	int in_fd;
	int out_fd;
	int i;

	if (heredoc)
	{
		setup_fd(&in_fd, "/tmp/heredoc", O_RDONLY | O_CREAT, 0644);
		setup_fd(&out_fd, argv[num_cmds + 2], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		setup_fd(&in_fd, argv[1], O_RDONLY, 0);
		setup_fd(&out_fd, argv[num_cmds + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	i = -1;
	while (++i < num_cmds)
	{
		if (i < num_cmds - 1)
			safe_pipe(pipes);
		if (i == 0)
			setup_cmd(&cmds[i], in_fd, argv[i + 2 + heredoc], i == 0);
		else
			setup_cmd(&cmds[i], pipes[0], argv[i + 2 + heredoc], i == 0);
		extract_path(&cmds[i], env);
		int output_fd;
		if (i == num_cmds - 1)
			run_command(&cmds[i], cmds[i].in_fd, out_fd, env);
		else
			run_command(&cmds[i], cmds[i].in_fd, pipes[1], env);
		if (i > 0)
			close(pipes[0]);
		if (i < num_cmds - 1)
			pipes[0] = pipes[1];
	}
	close(out_fd);
}

int main(int argc, char **argv, char **env)
{
	t_cmdline cmds[20];
	int num_cmds;
	int heredoc = 0;

	if (argc > 5 && check_heredoc(argv[1]))
	{
		num_cmds = argc - 4;
		heredoc = 1;
	}
	else if (argc > 4)
		num_cmds = argc - 3;
	else
	{
		ft_putendl_fd("Usage: ./pipex infile cmd1 .. cmdn outfile", 2);
		ft_putendl_fd("Usage: ./pipex here_doc LIMITER cmd1 .. cmdn outfile", 2);
		return (1);
	}
	execute_pipeline(cmds, argv, env, num_cmds, heredoc);
	return (0);
}
