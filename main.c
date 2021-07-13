#include "pipex.h"

int	main(int ac, char const *av[])
{
	int	fd[2];
	int	pid;
	int	status;

	if (ac != 5)
		error("ac ");
	pipe(fd);
	pid = fork();
	if (pid < 0)
		error("pid ");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		parent(av[4], av[3], fd);
	}
	else if (pid == 0)
		child(av[1], av[2], fd);
	return (1);
}
