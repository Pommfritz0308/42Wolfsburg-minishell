# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/18 18:32:16 by fbohling          #+#    #+#              #
#    Updated: 2023/09/22 09:37:14 by psimonen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

OBJ_DIR = 		build
SRC_DIR =		srcs
BUILTINS_DIR=	builtins
INCL_DIR =		includes

_SRC = 			main resolve_env resolve_env_utils parser init exec_builtin \
				tokenizer tokenizer_utils redirections executor executor_utils \
				str_utils str_utils_2 str_utils_3 tree_utils tree_utils_2 \
				env_utils signals clean errors path debug
_BUILTINS_SRC =	export export_2 pwd env cd cd_2 unset echo

SRCS =	$(addprefix $(BUILTINS_DIR)/,	$(addsuffix .c, $(_SRC)))
SRCS +=	$(addprefix $(BUILTINS_DIR)/,	$(addsuffix .c, $(_BUILTINS_SRC)))
OBJS =	$(addprefix $(OBJ_DIR)/, 		$(addsuffix .o, $(_SRC)))
OBJS +=	$(addprefix $(OBJ_DIR)/, 		$(addsuffix .o, $(_BUILTINS_SRC)))

CC = 		cc
RM = 		rm -f
CFLAGS =	-Wall -Werror -Wextra \
			-I/Users/$(USER)/.brew/Cellar/readline/8.2.1/include \
			-I.$(INCL_DIR)
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

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(BUILTINS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean bonus re
