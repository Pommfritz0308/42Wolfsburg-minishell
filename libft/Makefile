# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/21 12:30:22 by fbohling          #+#    #+#              #
#    Updated: 2023/08/30 13:38:40 by fbohling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	ft_isalnum.c ft_isprint.c \
					ft_strncmp.c ft_atoi.c ft_isalpha.c \
					ft_strchr.c ft_memcmp.c ft_memmove.c ft_memcpy.c \
					ft_strnstr.c ft_tolower.c ft_bzero.c ft_isascii.c \
					ft_strlen.c  ft_strrchr.c ft_strlcat.c ft_strlcpy.c \
					ft_toupper.c ft_isdigit.c ft_memchr.c ft_memset.c ft_calloc.c \
					ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c \
					ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
					ft_putendl_fd.c ft_putnbr_fd.c ft_split.c ft_check_format.c \
					ft_printf.c ft_putchar.c ft_putstr.c ft_putnbr.c \
					ft_dec_to_hexdec.c ft_putnbr_unsigned.c ft_putptr.c \
					ft_lstnew.c ft_lstadd_front.c  ft_lstsize.c ft_lstlast.c \
					ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
					ft_strupper.c ft_strtolower.c ft_atof.c ft_free_array.c ft_split_with_quotations.c \
					ft_count_char.c ft_split_with_char.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g -I.

NAME			= libft.a

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
