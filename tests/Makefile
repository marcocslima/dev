# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 02:03:37 by acosta-a          #+#    #+#              #
#    Updated: 2022/09/11 12:26:49 by mcesar-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test

# Compilation #
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
OPTCC=  -I. -c
RM = rm -rf

#HEADER = /include#
LIBFT = ../minishell_testes/libft/libft.a
LIBFT_PATH = ../minishell_testes/libft
# SOURCE FILES #
SRC = ./list_test.c


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

debug:
					$(MAKE) -C $(LIBFT_PATH)
					$(CC) -g $(CFLAGS) $(SRC) $(LIBFT) -o $@

.PHONY: clean fclean re
