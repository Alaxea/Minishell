# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/05 12:30:02 by astefans          #+#    #+#              #
#    Updated: 2024/08/20 13:08:38 by zogorzeb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
NAME = libft.a
SRC = ft_bzero.c ft_isalnum.c ft_isalpha.c \
	  ft_isascii.c ft_isdigit.c ft_isprint.c\
	  ft_memchr.c ft_memcpy.c ft_memmove.c \
	  ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
	  ft_putstr_fd.c ft_putnbr_fd.c  ft_strchr.c \
	  ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
	  ft_strrchr.c ft_tolower.c ft_toupper.c \
	  ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c \
	  ft_split.c ft_strjoin.c ft_strtrim.c ft_itoa.c \
	  ft_substr.c ft_strdup.c ft_strmapi.c ft_striteri.c
OBJ = $(SRC:.c=.o)
all: $(NAME)
$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean $(NAME)

.PHONY: all clean fclean re 

 
