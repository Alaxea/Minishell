# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 11:45:27 by zogorzeb          #+#    #+#              #
#    Updated: 2024/07/26 14:18:12 by zogorzeb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES = main.c \
		 libft.c \
		 exec.c \
		 child.c \
		 ft_split.c \
		 ft_strjoin.c

CFILES_BONUS =  child_bonus.c \
				exec_bonus.c \
				gnl_bonus.c \
				gnl_utils_bonus.c \
				heredoc_bonus.c \
				libft.c \
				ft_split.c \
				ft_strjoin.c \
				main_bonus.c
NAME = pipex
NAME_BONUS = pipex_bonus
CFLAGS = -Wall -Wextra -Werror
CC = cc
OFILES = $(CFILES:.c=.o)
OFILES_BONUS = $(CFILES_BONUS:.c=.o)

all : $(NAME)

$(NAME) : $(OFILES)
	@$(CC) $(CFLAGS) $(OFILES) -o $(NAME)

bonus: $(OFILES_BONUS)
	@$(CC) $(CFLAGS) $(OFILES_BONUS) -o $(NAME_BONUS)

clean:
	@rm -rf $(OFILES) $(OFILES_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all 

.PHONY: all clean fclean re 