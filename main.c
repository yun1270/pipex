#include "pipex.h"

void	process(const char *cmd1, const char *cmd2, int in, int out)
{
	int	fd[2];
	int	pid;
	int	status;

	pipe(fd);
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("Error: fork()\n", 2);
		exit(1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		parent(cmd2, fd, out);
	}
	else if (pid == 0)
		child(cmd1, fd, in);
}

int	main(int ac, char const *av[])
{
	int	in;
	int	out;

	if (ac != 5)
	{
		ft_putstr_fd("Error: The program takes 4 arguments.\n", 2);
		exit(1);
	}
	in = open(av[1], O_RDONLY);
	if (in < 0)
	{
		ft_putstr_fd("Error: file1 does not exist.\n", 2);
		exit(1);
	}
	out = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (out < 0)
	{
		ft_putstr_fd("Error: file2 does not exist.\n", 2);
		exit(1);
	}
	process(av[2], av[3], in, out);
	return (1);
}
