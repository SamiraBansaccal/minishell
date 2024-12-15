# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/02 00:45:56 by sbansacc          #+#    #+#              #
#    Updated: 2024/10/25 22:17:38 by sbansacc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCDIR = src/
BNSDIR = _bonus/

SRC_FILES = ft_printf.c \
	print_char.c \
	print_hexa.c \
	print_lowhexa.c \
	print_nbr.c \
	print_str.c \
	print_uint.c \
	print_uphexa.c

BNS_FILES = ft_printf_bonus.c \
	hexas_utils_bonus.c \
	print_char_bonus.c \
	print_lowhexa_bonus.c \
	print_percent_bonus.c\
	print_uint_bonus.c \
	nbrs_utils_bonus.c \
	print_hexa_bonus.c \
	print_nbr_bonus.c \
	print_str_bonus.c \
	print_uphexa_bonus.c

SRC = $(addprefix $(SRCDIR), $(SRC_FILES))
BNS = $(addprefix $(BNSDIR), $(BNS_FILES))

OBJ = $(SRC:.c=.o)
BNSOBJ = $(BNS:.c=.o)

all: $(NAME)

$(SRCDIR)%.o: $(SRC)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BNSDIR)%.o: $(BNSDIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

bonus: fclean $(BNSOBJ)
	ar rcs $(NAME) $(BNSOBJ)

clean:
	rm -f $(SRCDIR)*.o $(BNSDIR)*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
