# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 18:04:41 by sbritani          #+#    #+#              #
#    Updated: 2023/01/21 19:19:11 by sbritani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
SRCS =			philo/eat.c\
				philo/inits.c\
				philo/main.c\
				philo/philo_inits.c\
				philo/times.c\
				philo/utils1.c\
				philo/utils2.c
BONUS_SRCS =	philo_bonus/main.c\
				philo_bonus/philos.c\
				philo_bonus/some_other_funcs.c\
				philo_bonus/times.c

NAME =  philo_exec
BONUS_NAME =  philo_bonus_exec
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

.PHONY: all clean fclean re norm bonus