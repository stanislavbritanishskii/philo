#!/bin/sh

clear
output=$(echo $1 | sed "s/\..*//")
rm output
SRC="libft/libft.a eat.c inits.c times.c philo_inits.c"

echo $SRCS

gcc $SRC $1
mv a.out output
./output $2 $3 $4 $5 $6