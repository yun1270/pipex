#include "pipex.h"

void	error(char *error)
{
	ft_putstr_fd(error, ft_strlen(error));
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

// 프로그램의 경로는 시스템 환경에 따라 달라질 수 있습니다
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

	out = open(file, O_WRONLY);
	if (out < 0)
		error("file ");
	close(fd[WRITE]);
	dup2(out, WRITE);
	dup2(fd[READ], READ);
	run_cmd(cmd);
	close(out);
	close(fd[READ]);
	// wait(1);
}

void	child(char const *file, char const *cmd, int *fd)
{
	int	in;

	in = open(file, O_RDONLY);
	if (in < 0)
		error("file ");
	close(fd[READ]);
	dup2(in, READ);
	dup2(fd[WRITE], WRITE);
	run_cmd(cmd);
	close(in);
	close(fd[WRITE]);
}

int	main(int ac, char const *av[])
{
	int	fd[2];
	int	pid;

	if (ac != 5)
		error("ac ");
	pipe(fd);
	pid = fork();
	if (pid == -1)
		error("pid ");
	else if (pid > 0)
		parent(av[4], av[3], fd);
	else if (pid == 0)
		child(av[1], av[2], fd);
	return (1);
}
