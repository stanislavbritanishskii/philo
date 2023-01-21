# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 18:24:12 by sbritani          #+#    #+#              #
#    Updated: 2023/01/09 17:01:06 by sbritani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
SRCS = 	main.c utils.c paths.c pipes.c plumbs.c
BONUS_SRCS = 	main_bonus.c utils_bonus.c paths_bonus.c pipes_bonus.c plumbs_bonus.c
NAME =  pipex
BONUS_NAME =  pipex_bonus
LIBFT	:= ./libft
OBJ	= $(SRCS:.c=.o)
BONUS_OBJ	= $(BONUS_SRCS:.c=.o)
CFLAGS = -Wall -Werror -Wextra

all: libft $(NAME)

libft:
	@$(MAKE) -C $(LIBFT)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFT)/libft.a -o $(NAME)

bonus: libft $(BONUS_OBJ)
	$(CC) $(BONUS_OBJ) $(LIBFT)/libft.a -o $(BONUS_NAME)

clean:
	rm -f $(OBJ)
	rm -f $(BONUS_OBJ)
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all

norm:
	norminette $(SRCS) pipex.h

.PHONY: all clean fclean re norm libft bonus