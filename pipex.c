#include "pipex.h"

void	run_cmd(const char *cmd)
{
	int		i;
	char	**ar;

	i = 0;
	ar = ft_split(cmd, ' ');
	cmd = ft_strjoin("/bin/", ar[0]);
	execve(cmd, ar, NULL);
	cmd = ft_strjoin("/usr/local/bin/", ar[0]);
	execve(cmd, ar, NULL);
	cmd = ft_strjoin("/usr/bin/", ar[0]);
	execve(cmd, ar, NULL);
	cmd = ft_strjoin("/user/sbin/", ar[0]);
	execve(cmd, ar, NULL);
	cmd = ft_strjoin("/sbin/", ar[0]);
	execve(cmd, ar, NULL);
	ft_putstr_fd("Error: command does not exist.\n", 2);
	exit(1);
}

void	parent(char const *cmd, int *fd, int out)
{
	close(fd[1]);
	dup2(out, 1);
	dup2(fd[0], 0);
	run_cmd(cmd);
	close(out);
	close(fd[0]);
}

void	child(char const *cmd, int *fd, int in)
{
	close(fd[0]);
	dup2(in, 0);
	dup2(fd[1], 1);
	run_cmd(cmd);
	close(in);
	close(fd[1]);
}
