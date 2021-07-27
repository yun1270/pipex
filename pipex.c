#include "pipex.h"

void	error(char *error)
{
	ft_putstr_fd(error, ft_strlen(error));
	ft_putstr_fd(" Error\n", 2);
	exit(1);
}

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
	error(ar[0]);
}

void	parent(char const *file, char const *cmd, int *fd)
{
	int	out;

	close(fd[WRITE]);
	out = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (out < 0)
		error("file");
	dup2(out, WRITE);
	dup2(fd[READ], READ);
	run_cmd(cmd);
	close(out);
	close(fd[READ]);
}

void	child(char const *file, char const *cmd, int *fd)
{
	int	in;

	close(fd[READ]);
	in = open(file, O_RDONLY);
	if (in < 0)
		error("file");
	dup2(in, READ);
	dup2(fd[WRITE], WRITE);
	run_cmd(cmd);
	close(in);
	close(fd[WRITE]);
}
