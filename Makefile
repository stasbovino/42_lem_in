# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/28 23:35:25 by gwyman-m          #+#    #+#              #
#    Updated: 2019/09/09 21:00:17 by gwyman-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEM_IN=lem-in

FLAGS = -g -Wall -Wextra -Werror -I. -I libft/
LIB = -L libft/ -lft

SRC_DIR= src/

HEADER= lem_in.h

CFILES= main.c count_and_check_func.c valid_split.c validation.c

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
