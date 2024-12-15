# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/29 17:49:57 by sabansac          #+#    #+#              #
#    Updated: 2024/12/04 05:18:28 by sabansac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror #-fsanitize=address -g
SRCDIR		:= src/
OBJDIR		:= obj/
LIBFTDIR	:= lib/libft/
INCLFLAGS	:= -I$(SRCDIR) -I$(LIBFTDIR) -I/Users/sabansac/.brew/opt/readline/include
LDFLAGS		:= -L$(LIBFTDIR) -lft -lreadline -L/Users/sabansac/.brew/opt/readline/lib 

SRC_FILES	:= main.c \
				utils/initialisations.c utils/init_utils.c utils/cleanups.c \
				utils/errors_handler.c utils/errors_handler_utils.c \
				utils/signals.c \
				parsing/parse_operator.c parsing/parse_quotes.c \
				parsing/parse_variable.c parsing/parse_word.c \
				parsing/parse.c parsing/tokenize.c \
				execution/cmd_is_valid.c execution/cmd_is_valid_utils.c \
				execution/execute_cmd.c execution/pipeline_utils.c \
				execution/copy_env.c execution/here_doc.c \
				builtins/builtins.c builtins/ft_cd.c builtins/ft_echo.c \
				builtins/ft_env.c builtins/ft_exit.c builtins/ft_export.c \
				builtins/ft_pwd.c builtins/ft_unset.c \
				../tests/exec_tester.c ../tests/parsing_tester.c \

SRC			:= $(addprefix $(SRCDIR), $(SRC_FILES))
OBJ			:= $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

LIBFT		:= $(LIBFTDIR)libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@
	@echo "🚀 Houston, we have a minishell!"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLFLAGS) -c $< -o $@

$(LIBFT):
	@echo "🏗️  Building libft..."
	@$(MAKE) -C $(LIBFTDIR)

clean:
	@echo "🧹 Cleaning up the mess..."
	@$(MAKE) -C $(LIBFTDIR) clean
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "🧨 Obliterating all traces..."
	@$(MAKE) -C $(LIBFTDIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re