#!/bin/sh

clear
output=$(echo $1 | sed "s/\..*//")
rm output
SRC="libft/libft.a philo/eat.c philo/inits.c philo/times.c philo/philo_inits.c"

echo $SRCS

gcc $SRC $1
# gcc -fsanitize=thread $SRC $1
mv a.out output
./output $2 $3 $4 $5 $6