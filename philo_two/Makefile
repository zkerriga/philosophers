# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/10 17:29:48 by zkerriga          #+#    #+#              #
#    Updated: 2020/09/18 17:55:13 by matrus           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_two

PRJ_DIR = philo_two
OBJ_DIR = ../bin
HDR_DIR = includes
LIB_DIR = ../lib

CC = gcc
INCLUDES = -I$(LIB_DIR) -I$(HDR_DIR)
FLAGS = -Wall -Wextra -Werror $(INCLUDES)

LIB_FILES = $(addprefix $(LIB_DIR)/,argparse.c ft_isdigit.c ft_isspace.c ft_itoa.c ft_say_join.c ft_strlcpy.c \
									ft_strlen.c ft_usleep.c get_time_us.c put_error.c )
LIB_FILES_O = $(addprefix $(OBJ_DIR)/, $(subst ../,,$(LIB_FILES:.c=.o)))

FILES = main.c \
		$(addprefix classes/philosopher/philosopher, _actions.c _constructors.c _lifetime.c _say.c ) \
		$(addprefix classes/table/table, _constructors.c _start_simulation.c )
FILES_O = $(addprefix $(OBJ_DIR)/$(PRJ_DIR)/, $(FILES:.c=.o))

.PHONY: all
all: $(OBJ_DIR) $(NAME)
	@echo "\n\033[32m[+] The $(NAME) assembled!\033[0m\n"

$(OBJ_DIR):
	@mkdir -p	$(OBJ_DIR) $(OBJ_DIR)/$(PRJ_DIR) $(OBJ_DIR)/$(subst ../,,$(LIB_DIR)) \
				$(OBJ_DIR)/$(PRJ_DIR)/classes/table $(OBJ_DIR)/$(PRJ_DIR)/classes/philosopher

$(NAME): $(LIB_FILES_O) $(FILES_O)
	@$(CC) $(FLAGS) $(LIB_FILES_O) $(FILES_O) -o $(NAME)

$(LIB_FILES_O): $(OBJ_DIR)/%.o: ../%.c
	$(CC) $(FLAGS) -MMD -c $< -o $@
include $(wildcard $(OBJ_DIR)$(subst ../,,$(LIB_DIR))/*.d)

$(FILES_O): $(OBJ_DIR)/$(PRJ_DIR)/%.o: %.c
	$(CC) $(FLAGS) -MMD -c $< -o $@
include $(wildcard $(OBJ_DIR)/$(PRJ_DIR)/*.d $(OBJ_DIR)/$(PRJ_DIR)/*/*.d $(OBJ_DIR)/$(PRJ_DIR)/*/*/*.d)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all

.PHONY: l0 l1 l2 l3 d0
l0: $(NAME)
	./$(NAME) 5 800 200 200

l1: $(NAME)
	./$(NAME) 5 800 200 200 7

l2: $(NAME)
	./$(NAME) 4 410 200 200

l3: $(NAME)
	./$(NAME) 5 800 200 200 150

l4: $(NAME)
	./$(NAME) 5 800 200 200 2

d0: $(NAME)
	./$(NAME) 4 310 200 100
