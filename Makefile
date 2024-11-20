# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/14 13:39:33 by astefans          #+#    #+#              #
#    Updated: 2024/11/20 15:09:26 by zogorzeb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
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
		meat/parser/0_parser.c \
		meat/parser/parser_utils.c \
		meat/parser/ft_split_quotes.c \
		meat/parser/quotes_utils.c	\
		meat/parser/expander.c \
		meat/parser/expander_utils.c \
		meat/parser/cmd_valid.c \
		meat/lexer/tokenization.c \
		meat/lexer/validation.c \
		meat/builtins/env_builtin.c \
		meat/builtins/pwd_builtin.c \
		meat/builtins/exit_builtin.c \
		meat/builtins/echo_builtin.c \
		meat/builtins/cd_builtin.c \
		meat/builtins/export_builtin.c \
		meat/builtins/unset_builtin.c \
		meat/executor/clean.c \
		meat/executor/env_helper.c \
		meat/executor/builtins_gate.c \
		meat/executor/redirections.c \
		meat/executor/heredoc.c \
		meat/executor/execute.c \
		meat/executor/exec_path.c \
		meat/executor/pipes_1.c \
		meat/executor/pipes_2.c \
		meat/executor/pipes_3.c \
		meat/executor/utils.c \
		meat/executor/env_utils.c \
		meat/executor/execute_utils.c \
		meat/signals/handle_signals.c \
		minishell.c \
		main.c \

		
OBJ_DIR = objects
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR) $(OBJ_DIR)/meat/utils $(OBJ_DIR)/meat/parser \
	    $(OBJ_DIR)/meat/lexer $(OBJ_DIR)/meat/builtins $(OBJ_DIR)/meat/executor \
	    $(OBJ_DIR)/meat/signals

$(LIBFT):
	make -C $(LIBFT_PATH)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline

clean:
	$(RM) $(OBJ)
	make -C $(LIBFT_PATH) clean
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re



PATHUNITY = unity/src

# testy
# lexer:
	# cc -Wall -Wextra -Werror -lreadline tests/meat/lexer/tokenization.c includes/libft/libft.a meat/utils/ft_lstadd_back.c meat/utils/ft_lstclear.c meat/utils/ft_lstdelone.c meat/utils/ft_lstlast.c meat/utils/ft_lstnew.c
test_lexer:
	cc -Wall -Wextra -Werror $(PATHUNITY)/unity.c tests/lexer_test.c -lreadline meat/lexer/tokenization.c includes/libft/libft.a meat/utils/ft_lstadd_back.c meat/utils/ft_lstclear.c meat/utils/ft_lstdelone.c meat/utils/ft_lstlast.c meat/utils/ft_lstnew.c && ./a.out
test_validation:
	cc -Wall -Wextra -Werror $(PATHUNITY)/unity.c tests/lex_valid_test.c -lreadline meat/lexer/tokenization.c meat/lexer/validation.c includes/libft/libft.a meat/utils/ft_lstadd_back.c meat/utils/ft_lstclear.c meat/utils/ft_lstdelone.c meat/utils/ft_lstlast.c meat/utils/ft_lstnew.c && ./a.out
test_sc:
	cc -Wall -Wextra -Werror $(PATHUNITY)/unity.c tests/single_sc_test.c -lreadline meat/parser/ft_split_quotes.c meat/parser/parser_utils.c meat/lexer/tokenization.c meat/parser/quotes_utils.c meat/parser/0_parser.c includes/libft/libft.a meat/utils/ft_lstadd_back.c meat/utils/ft_lstclear.c meat/utils/ft_lstdelone.c meat/utils/ft_lstlast.c meat/utils/ft_lstnew.c && ./a.out
test_lst:
	cc -Wall -Wextra -Werror $(PATHUNITY)/unity.c tests/sc_list.c -lreadline meat/parser/quotes_utils.c meat/parser/ft_split_quotes.c meat/lexer/tokenization.c meat/parser/parser_utils.c meat/parser/0_parser.c includes/libft/libft.a meat/utils/ft_lstadd_back.c meat/utils/ft_lstclear.c meat/utils/ft_lstdelone.c meat/utils/ft_lstlast.c meat/utils/ft_lstnew.c && ./a.out
test_expander:
	cc -Wall -Wextra -Werror $(PATHUNITY)/unity.c tests/test_expander.c -lreadline meat/parser/ft_split_quotes.c meat/parser/parser_utils.c meat/parser/expander_utils.c meat/parser/expander.c meat/lexer/tokenization.c meat/parser/0_parser.c includes/libft/libft.a meat/utils/ft_lstadd_back.c meat/utils/ft_lstclear.c meat/utils/ft_lstdelone.c meat/utils/ft_lstlast.c meat/utils/ft_lstnew.c && ./a.out
test_exec:
	cc -Wall -Wextra -Werror $(PATHUNITY)/unity.c tests/test_exec.c -lreadline meat/parser/ft_split_quotes.c meat/parser/expander_utils.c meat/parser/parser_utils.c meat/parser/expander.c meat/lexer/tokenization.c meat/parser/0_parser.c includes/libft/libft.a meat/utils/ft_lstadd_back.c meat/utils/ft_lstclear.c meat/utils/ft_lstdelone.c meat/utils/ft_lstlast.c meat/utils/ft_lstnew.c meat/executor/builtins_gate.c meat/executor/execute.c meat/utils/env_helper.c meat/executor/redirections.c && ./a.out
