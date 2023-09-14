# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/18 18:32:16 by fbohling          #+#    #+#              #
#    Updated: 2023/09/14 20:05:13 by psimonen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

OBJ_DIR = build
BUILTINS_DIR = builtins

_SRC = 			main resolve_env parser signals init errors path debug \
				tokenizer tokenizer_utils executor redirections \
				str_utils tree_utils env_utils exec_builtin
_BUILTINS_SRC =	export export_2 pwd env cd

SRCS =									$(addsuffix .c, $(_SRC))
SRCS +=	$(addprefix $(BUILTINS_DIR)/,	$(addsuffix .c, $(_BUILTINS_SRC)))
OBJS =	$(addprefix $(OBJ_DIR)/, 		$(addsuffix .o, $(_SRC)))
OBJS +=	$(addprefix $(OBJ_DIR)/, 		$(addsuffix .o, $(_BUILTINS_SRC)))

CC = 		cc
RM = 		rm -f
CFLAGS =	-Wall -Werror -Wextra \
			-I/Users/$(USER)/.brew/Cellar/readline/8.2.1/include
LIBFT_DIR	= libft
LIBFT 		= $(LIBFT_DIR)/libft.a
LIBS 		= \
			-L$(LIBFT_DIR) \
			-lft \
			-ltermcap \
			-lreadline \
			-L/Users/$(USER)/.brew/Cellar/readline/8.2.1/lib

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(BUILTINS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) $(OBJS)
	$(RM) $(BONUS_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean bonus re
