# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/18 18:32:16 by fbohling          #+#    #+#              #
#    Updated: 2023/09/26 14:33:23 by fbohling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 			minishell

OBJ_DIR = 		build
SRC_DIR =		srcs
BUILTINS_DIR=	builtins
INCL_DIR =		includes

SRC = 			main resolve_env resolve_env_utils init exec_builtin signals \
				tokenizer tokenizer_utils executor executor_utils env_utils \
				str_utils str_utils_2 str_utils_3 tree_utils tree_utils_2 \
				redirections redirections_utils parser parser_utils heredoc \
				path clean clean_2 fd_utils errors debug wildcards
BUILTINS =		export export_2 pwd env cd cd_2 unset echo exit exit2

OBJS =			$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC)))
OBJS +=			$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(BUILTINS)))

CC = 			cc
RM = 			rm -f
CFLAGS =		-Wall -Werror -Wextra \
				-I/Users/$(USER)/.brew/Cellar/readline/8.2.1/include \
				-I./$(INCL_DIR)
LIBFT_DIR =		libft
LIBFT =			$(LIBFT_DIR)/libft.a
LIBS =			-L$(LIBFT_DIR) \
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
