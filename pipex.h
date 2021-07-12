#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"

# define READ 0
# define WRITE 1

void	error(char *error);
void	run_cmd(const char *cmd);
void	parent(char const *file, char const *cmd, int *fd);
void	child(char const *file, char const *cmd, int *fd);

#endif