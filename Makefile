# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/28 23:35:25 by gwyman-m          #+#    #+#              #
#    Updated: 2019/09/23 21:55:13 by sts              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEM_IN=lem-in

FLAGS = -g -Wall -Wextra -Werror -I. -I libft/
LIB = -L libft/ -lft

SRC_DIR= src/

HEADER=	lem_in.h

CFILES= main.c count_and_check_func.c valid_split.c validation.c init_table.c \
		get_.c find_no_.c compare.c free.c print.c create_links.c read.c \
		check_start_and_end.c solution.c dup_.c init_path.c add_path.c \

OFILES= $(CFILES:%.c=%.o)

SRC= $(addprefix $(SRC_DIR),$(CFILES))

OBJ= $(addprefix $(SRC_DIR),$(OFILES))

LIBFT=libft/libft.a

RULE=$(firstword $(MAKECMDGOALS))

VPATH := src

.PHONY=all clean fclean re

all: $(LEM_IN)

$(LEM_IN): $(LIBFT) $(OBJ) $(HEADER)
	@gcc $(FLAGS) $(OBJ) -o $(LEM_IN) $(LIB)
	@printf "\033[0;32mlem-in files are ready                        \033[0m\n"
	@printf "\e[?25h\033[0;32mlem-in is ready\033[0m\n"

$(LIBFT):
	@make -C libft/

src/%.o: %.c $(HEADER)
	@gcc -c $(FLAGS) $< -o $@
	@printf "\e[?25l\033[0;34mcompiling $<\033[0m\033\r"
	@printf "                                 \r"

clean:
	@rm -f $(OBJ)
ifneq ($(RULE),$(filter $(RULE), fclean re))
	@make clean -C libft/
endif
	@echo "\033[0;33mthe src directory is cleaned\033[0m"

fclean: clean
	@make fclean -C libft/
	@rm -f $(LEM_IN)
	@echo "\033[0;33mdeleted lem-in\033[0m"

re: fclean all
