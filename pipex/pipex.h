#ifndef PIPEX_H
# define PIPEX_H
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft/libft.h"


typedef struct s_cmdline
{
	char	*cmd;
	char	**cmd_args;
	int		in_fd;
	int		out_fd;
}	t_cmdline;





#endif
