# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/27 06:00:36 by mcesar-d          #+#    #+#              #
#    Updated: 2022/11/27 06:00:46 by mcesar-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = utils.c philo.c

FLAGS = -g -Werror -Wextra -Wall -pthread

OBJS = ${SRCS:.c=.o}

$(NAME) : $(OBJS)
	gcc $(FLAGS) $(SRCS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all make clean

.PHONY: clean fclean re
