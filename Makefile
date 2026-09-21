# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sajabran <sajabran@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/21 18:45:06 by sajabran          #+#    #+#              #
#    Updated: 2026/09/21 22:54:15 by sajabran         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs
RM			= rm -f

SRCS		= ft_printf.c \
			  parser/parsing.c \
			  utils/check_base.c \
			  utils/ft_print_pointer.c \
			  utils/ft_put_hex.c \
			  utils/ft_putchar.c \
			  utils/ft_putnbr.c \
			  utils/ft_putstr.c \
			  utils/ft_putnbr_unsigned.c

OBJS		= $(SRCS:.c=.o)

HEADER		= ft_printf.h

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
