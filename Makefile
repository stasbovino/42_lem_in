# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/28 23:35:25 by gwyman-m          #+#    #+#              #
#    Updated: 2019/09/04 01:35:40 by sts              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEM_IN=lem-in

FLAGS = -g -Wall -Wextra -Werror -I. -I libft/
LIB = -L libft/ -lft

SRC_DIR= src/

HEADER= lem_in.h

CFILES= main.c

SRC= $(addprefix $(SRC_DIR),$(CFILES))

all: $(LEM_IN)

$(LEM_IN): $(SRC) $(HEADER)
	@make -C libft/
	gcc $(FLAGS) $(SRC) -o $(LEM_IN) $(LIB)

clean:
	@make clean -C libft/

fclean: clean
	@make fclean -C libft/
	rm -fv $(LEM_IN)

re: fclean all
