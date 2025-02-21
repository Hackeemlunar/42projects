#include "pipex.h"

void setup_cmd(t_cmdline *cmd, int fd, char *full_cmd, int is_input)
{
	ft_memset(cmd, 0, sizeof(t_cmdline));
	cmd->cmd_args = ft_split(full_cmd, ' ');
	cmd->cmd = ft_strjoin("/bin/", cmd->cmd_args[0]);
	if (is_input)
		cmd->in_fd = fd;
	else
		cmd->out_fd = fd;
}

int main(int argc, char **argv)
{
	t_cmdline	cmd;
	int			fd[2];
	int			in_fd;
	int			out_fd;
	pid_t		pid;

	if (argc != 5)
	{
		ft_printf("Usage: %s <inputf> <cmd1> <cmd2> <outputf>\n", argv[0]);
		return 1;
	}

	in_fd = open(argv[1], O_RDONLY);
	out_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pipe(fd);

	setup_cmd(&cmd, in_fd, argv[2], 1);

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