NAME = pipex
CC = gcc
CFLAGS = -Werror -Wall -Wextra
RM = rm -rf

SRCS = 	main.c\
		pipex.c\
		libft/ft_split.c\
		libft/ft_strjoin.c\
		libft/ft_putstr_fd.c\
		libft/ft_strlen.c

$(NAME) :
	gcc $(SRCS) -o $(NAME)

all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft

clean :
	$(RM) $(NAME)
	make clean -C libft

re : fclean all