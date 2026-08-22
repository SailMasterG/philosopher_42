GREEN = \033[0;32m
RESET = \033[0m

NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread

SRCS = main.c \
	init.c \
	routine.c \
	utils.c \
	monitor.c \
	validation.c \
	ft_strtol.c
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compilating..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Successfully compiled 🚀"

%.o: %.c philo.h
	@echo "Generating the objects..."
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Objects successfully generated 👌"

clean:

	@rm -f $(OBJS)
	@echo "Deleted objects...🚮"

fclean: clean
	@rm -f $(NAME)
	@echo "Deleted objects and executable...🗑️​"

re: fclean all
	@printf "$(GREEN)Making the world green again.$(RESET) ♻️​​"

.PHONY: all clean fclean re
