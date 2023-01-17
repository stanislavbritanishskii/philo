#!/bin/sh

clear
output=$(echo $1 | sed "s/\..*//")
rm output
SRC="philo/eat.c philo/inits.c philo/times.c philo/philo_inits.c philo/main.c"

echo $SRCS

gcc $SRC
# gcc -fsanitize=thread $SRC
mv a.out output
./output $1 $2 $3 $4 $5
