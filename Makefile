NAME = philo

SRCS = 		main.c ft_atoi.c parser.c

OBJ = $(patsubst %.c, %.o, $(SRCS))

INCLUDE = philo.h

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
			gcc $(FLAGS) $(OBJ) -pthread -o $(NAME)

clean:
			rm -rf $(OBJ)

fclean: clean
			rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
