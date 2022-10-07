# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 21:00:15 by mcesar-d          #+#    #+#              #
#    Updated: 2022/10/03 22:15:25 by acosta-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_atoi.c \
					ft_isprint.c ft_toupper.c ft_tolower.c ft_strlen.c ft_strdup.c \
					ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c \
					ft_memset.c ft_memcmp.c ft_memcpy.c ft_memchr.c ft_memmove.c \
					ft_strnstr.c ft_bzero.c ft_calloc.c ft_substr.c ft_strjoin.c \
					ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putstrs.c ft_putchar_fd.c \
					ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c ft_findrchr.c
OBJS			=	$(SRCS:.c=.o)
BONUS			=	ft_lstnew.c ft_lstadd_front.c ft_lstlast.c ft_lstadd_back.c ft_lstsize.c \
					ft_lstdelone.c ft_lstiter.c ft_lstclear.c ft_lstmap.c
BONUS_O			=	$(BONUS:.c=.o)
CC				=	gcc
CFLAGS			=	-g3 -Wall -Wextra -Werror
NAME			=	libft.a

all:		$(NAME)

$(NAME):	$(OBJS)
			ar -rcs $(NAME) $(OBJS)
			make bonus

%.o:		%.c	libft.h
			$(CC) $(CFLAGS) -I . -c $< -o $@

bonus:		$(BONUS_O)
			make OBJS="$(OBJS) $(BONUS_O)" all

clean:
			rm -rf $(OBJS) $(BONUS_O)

fclean:		clean
			rm -rf $(NAME)

re:			fclean $(NAME)

.PHONY: all clean fclean re bonus
