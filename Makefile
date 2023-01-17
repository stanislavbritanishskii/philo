# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 18:04:41 by sbritani          #+#    #+#              #
#    Updated: 2023/01/17 18:26:24 by sbritani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
SRCS = 	philo/eat.c philo/inits.c philo/times.c philo/philo_inits.c philo/main.c
BONUS_SRCS = 	main_bonus.c utils_bonus.c paths_bonus.c pipes_bonus.c plumbs_bonus.c
NAME =  pipex
BONUS_NAME =  pipex_bonus
LIBFT	:= ./libft
OBJ	= $(SRCS:.c=.o)
BONUS_OBJ	= $(BONUS_SRCS:.c=.o)
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

bonus: $(BONUS_OBJ)
	$(CC) $(BONUS_OBJ) -o $(BONUS_NAME)

clean:
	rm -f $(OBJ)
	rm -f $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)

re: fclean all

norm:
	norminette $(SRCS) pipex.h

.PHONY: all clean fclean re norm libft bonus