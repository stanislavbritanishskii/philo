#!/bin/sh

clear
output=$(echo $1 | sed "s/\..*//")
rm output
SRC="libft/libft.a philo/eat.c philo/inits.c philo/times.c philo/philo_inits.c philo/main.c"

echo $SRCS

gcc -pthread $SRC
# gcc -fsanitize=thread $SRC
mv a.out output
./output $1 $2 $3 $4 $5
