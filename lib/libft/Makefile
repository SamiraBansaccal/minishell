# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/31 19:26:07 by sabansac          #+#    #+#              #
#    Updated: 2024/10/25 22:24:56 by sbansacc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
PRINTF_PATH = ../ft_printf/

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
    ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
    ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
    ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
    ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
    ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

BNS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c

OBJ = ${SRC:.c=.o}
BNSOBJ = ${BNS:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(PRINTF_PATH)
	@ar rcs $(NAME) $(OBJ)
	@ar -x $(PRINTF_PATH)libftprintf.a
	@ar rcs $(NAME) *.o
	@rm -f *.o

bonus: $(OBJ) $(BNSOBJ)
	@make -C $(PRINTF_PATH)
	@ar rcs $(NAME) $(OBJ) $(BNSOBJ)
	@ar -x $(PRINTF_PATH)libftprintf.a
	@ar rcs $(NAME) *.o
	@rm -f *.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(BNSOBJ)
	@make -C $(PRINTF_PATH) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(PRINTF_PATH) fclean

re: fclean all

.PHONY: all clean fclean re bonus