# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/14 13:39:33 by astefans          #+#    #+#              #
#    Updated: 2024/09/01 13:46:41 by zogorzeb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -Iincludes
LIBFT_PATH = includes/libft
LIBFT = $(LIBFT_PATH)/libft.a
RM = rm -f
NAME = minishell
SRC =	meat/utils/ft_lstadd_back.c \
		meat/utils/ft_lstadd_front.c \
		meat/utils/ft_lstclear.c \
		meat/utils/ft_lstdelone.c \
		meat/utils/ft_lstlast.c \
		meat/utils/ft_lstmap.c \
		meat/utils/ft_lstnew.c \
		meat/utils/ft_lstsize.c \
		meat/utils/utils.c \
		meat/parser/0_parser.c \
		meat/parser/ft_split_quotes.c \
		meat/lexer/tokenization.c \
		meat/lexer/validation.c \
		meat/builtins/env_builtin.c \
		meat/builtins/export_builtin.c \
		meat/builtins/exit_builtin.c \
		meat/builtins/echo_builtin.c \
		meat/builtins/cd_builtin.c \
		meat/utils/clean.c \
		meat/utils/error.c \
		meat/utils/env_helper.c \
		minishell.c \
		meat/parser/expander.c \


OBJ = $(SRC:.c=.o)
all: $(NAME)
$(LIBFT):
	make -C $(LIBFT_PATH)
$(NAME) :$(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline
clean:
	$(RM) $(OBJ)
	make -C $(LIBFT_PATH) clean
fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_PATH) fclean
re: fclean $(NAME)

.PHONY: all clean fclean re

PATHUNITY = unity/src

# testy
lexer:
	cc -Wall -Wextra -Werror -lreadline meat/lexer/lexer.c includes/libft/libft.a meat/utils/ft_lstadd_back.c meat/utils/ft_lstclear.c meat/utils/ft_lstdelone.c meat/utils/ft_lstlast.c meat/utils/ft_lstnew.c
test_lexer:
	cc -Wall -Wextra -Werror $(PATHUNITY)/unity.c tests/lexer_test.c -lreadline meat/lexer/tokenization.c includes/libft/libft.a meat/utils/ft_lstadd_back.c meat/utils/ft_lstclear.c meat/utils/ft_lstdelone.c meat/utils/ft_lstlast.c meat/utils/ft_lstnew.c && ./a.out
test_validation:
	cc -Wall -Wextra -Werror $(PATHUNITY)/unity.c tests/lex_valid_test.c -lreadline meat/lexer/tokenization.c meat/lexer/validation.c includes/libft/libft.a meat/utils/ft_lstadd_back.c meat/utils/ft_lstclear.c meat/utils/ft_lstdelone.c meat/utils/ft_lstlast.c meat/utils/ft_lstnew.c && ./a.out
test_sc:
	cc -Wall -Wextra -Werror $(PATHUNITY)/unity.c tests/single_sc_test.c -lreadline meat/parser/ft_split_quotes.c meat/lexer/tokenization.c meat/parser/0_parser.c includes/libft/libft.a meat/utils/ft_lstadd_back.c meat/utils/ft_lstclear.c meat/utils/ft_lstdelone.c meat/utils/ft_lstlast.c meat/utils/ft_lstnew.c && ./a.out
test_lst:
	cc -Wall -Wextra -Werror $(PATHUNITY)/unity.c tests/sc_list.c -lreadline meat/parser/ft_split_quotes.c meat/lexer/tokenization.c meat/parser/0_parser.c includes/libft/libft.a meat/utils/ft_lstadd_back.c meat/utils/ft_lstclear.c meat/utils/ft_lstdelone.c meat/utils/ft_lstlast.c meat/utils/ft_lstnew.c && ./a.out
