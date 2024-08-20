# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astefans <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/14 13:39:33 by astefans          #+#    #+#              #
#    Updated: 2024/08/14 13:39:36 by astefans         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -Iincludes
LIBFT_PATH = includes/libft
LIBFT = $(LIBFT_PATH)/libft.a
RM = rm -f
NAME = minishell
SRC = minishell.c handle_ctrl.c
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

