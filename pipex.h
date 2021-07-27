#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"

void	parent(char const *cmd, int *fd, int out);
void	child(char const *cmd, int *fd, int in);

#endif