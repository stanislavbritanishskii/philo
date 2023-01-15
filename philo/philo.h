/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:02:15 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/15 18:44:41 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/libft.h"
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct philo_s
{
	int				number;
	pthread_t		*thread;
	int				total;
	int				*okay;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*say_lock;
	pthread_mutex_t	*okay_lock;
	long long		time_to_sleep;
	long long		time_to_eat;
	long long		time_to_die;
	long long		start_time;
	long long		last_meal_time;
	int				eaten_times;
}	t_philo;

typedef struct settings_s
{
	int				count;
	int				*ok;
	int				done;
	int				i;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start_time;
	long long		time_to_die;
	int				amount_of_meals;
	int				all_ate_enough;
	pthread_mutex_t	*say_lock;
	pthread_mutex_t	*okay_lock;
	pthread_mutex_t	**forks;
	t_philo			**philos;
}	t_settings;

pthread_mutex_t	**init_forks(int n);
t_philo			**create_philos(int n, int*ok,
					pthread_mutex_t **forks, pthread_mutex_t *okay_lock);
void			some_more_vars_for_philos(t_philo **philos,
					long long time_to_eat,
					long long time_to_sleep, long long start_time);
long long		get_time(void);
int				get_other_time(void);
pthread_t		*create_thread(void);
int				say(char *phrase, t_philo *philo);
void			*main_eat(void *var);
t_settings		*create_settings(int count);

#endif