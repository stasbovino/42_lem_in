# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/28 23:35:25 by gwyman-m          #+#    #+#              #
#    Updated: 2019/09/11 21:55:38 by gwyman-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEM_IN=lem-in

FLAGS = -g -Wall -Wextra -Werror -I. -I libft/
LIB = -L libft/ -lft

SRC_DIR= src/

HEADER=	lem_in.h

CFILES= main.c count_and_check_func.c valid_split.c validation.c

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
	@echo "\n\033[0;32mlem-in is ready\033[0m"

$(LIBFT):
	@make -C libft/

src/%.o: %.c $(HEADER)
	@gcc -c $(FLAGS) $< -o $@
	@printf "\033[0;34mcompiling $<\033[0m\033\r"
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
