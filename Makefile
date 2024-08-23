# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/14 13:39:33 by astefans          #+#    #+#              #
#    Updated: 2024/08/23 18:48:02 by zogorzeb         ###   ########.fr        #
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
		meat/parser/0_parser.c \
		meat/lexer/lexer.c \
		meat/lexer/validation.c \
		minishell.c \
		# meat/signals/handle_ctrl.c \

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

# testy
make lexer:
	cc -Wall -Wextra -Werror -lreadline meat/lexer/lexer.c includes/libft/libft.a meat/utils/ft_lstadd_back.c meat/utils/ft_lstclear.c meat/utils/ft_lstdelone.c meat/utils/ft_lstlast.c meat/utils/ft_lstnew.c