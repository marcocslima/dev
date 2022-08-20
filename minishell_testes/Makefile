# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 02:03:37 by acosta-a          #+#    #+#              #
#    Updated: 2022/08/16 20:32:41 by acosta-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell2

# Compilation #
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
OPTCC=  -I. -c
RM = rm -rf

#HEADER = /include#
LIBFT = ./libft/libft.a
LIBFT_PATH = ./libft
# SOURCE FILES #
SRC = ./exits.c ./signal.c ./main.c ./utils.c ./parser.c \

#BONUS =

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(<:%.c=%.o)

SRC.O = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(SRC.O)
	$(RM) $(NAME)
	make -C ${LIBFT_PATH}
	$(CC) $(CFLAGS) $(SRC.O) $(LIBFT) -o $(NAME)

clean:
	$(RM) $(SRC.O)
	make clean -C ${LIBFT_PATH}

fclean: clean
	$(RM) $(NAME)
	make fclean -C ${LIBFT_PATH}

re: fclean all
	make clean

.PHONY: clean fclean re
