#include "pipex.h"


	int main(int argc, char **argv, char **env) {
		char *path;
		char **dirs;
		int i = 0;
		while (env[i] != NULL)
		{
			if (ft_strncmp(env[i], "PATH=", 5) == 0)
			{
				path = env[i] + 5;
				break ;
			}
			i++;
		}
		dirs = ft_split(path, ':');
		i = 0;
		while (dirs[i] != NULL)
		{
			printf("%s\n", dirs[i]);
			free(dirs[i]);
			i++;
		}
		return (0);
	}