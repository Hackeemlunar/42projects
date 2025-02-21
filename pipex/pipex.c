#include "pipex.h"

void	setup_cmd(t_cmdline *cmd, int fd, char *full_cmd, int is_input)
{
	ft_memset(cmd, 0, sizeof(t_cmdline));
	cmd->cmd_args = ft_split(full_cmd, ' ');
	cmd->cmd = ft_strjoin("/bin/", cmd->cmd_args[0]);
	if (is_input)
		cmd->in_fd = fd;
	else
		cmd->out_fd = fd;
}

int	main(int argc, char **argv)
{
	t_cmdline   cmd1, cmd2;
	int         fd[2];
	int         in_fd, out_fd;
	pid_t       pid1, pid2;

	if (argc != 5) {
		printf("Usage: %s <input> <cmd1> <cmd2> <output>\n", argv[0]);
		return 1;
	}

	in_fd = open(argv[1], O_RDONLY);
	out_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pipe(fd);

	setup_cmd(&cmd1, in_fd, argv[2], 1);

	// First command (input side)
	if ((pid1 = fork()) == 0)
	{
		dup2(cmd1.in_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		execve(cmd1.cmd, cmd1.cmd_args, NULL);
		exit(0);
	}
	close(fd[1]);

	// Second command (output side)
	setup_cmd(&cmd2, out_fd, argv[3], 0);
	if ((pid2 = fork()) == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(cmd2.out_fd, STDOUT_FILENO);
		close(fd[1]);
		execve(cmd2.cmd, cmd2.cmd_args, NULL);
		exit(0);
	}
	close(fd[0]);

	pipe(fd);

	// Cleanup
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	close(in_fd);
	close(out_fd);

	return 0;
}