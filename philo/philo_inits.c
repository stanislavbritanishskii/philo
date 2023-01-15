/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:41:38 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/15 15:42:19 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_philo(int total_number, int individual_number,
		int *ok, pthread_mutex_t **forks)
{
	t_philo	*res;

	res = malloc(sizeof(t_philo));
	res->number = individual_number;
	res->total = total_number;
	res->thread = create_thread();
	res->okay = ok;
	res->forks = forks;
	return (res);
}

t_philo	**create_philos(int n, int*ok, pthread_mutex_t **forks,
		pthread_mutex_t *okay_lock)
{
	t_philo			**res;
	int				i;
	pthread_mutex_t	*say_lock;

	say_lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(say_lock, NULL);
	res = malloc(sizeof(t_philo *) * (n + 1));
	i = 0;
	while (i < n)
	{
		res[i] = create_philo(n, i, ok, forks);
		res[i]->okay_lock = okay_lock;
		res[i]->say_lock = say_lock;
		res[i]->eaten_times = 0;
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	some_more_vars_for_philos(t_philo **philos, long long time_to_eat,
		long long time_to_sleep, long long start_time)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		philos[i]->time_to_sleep = time_to_sleep;
		philos[i]->time_to_eat = time_to_eat;
		philos[i]->start_time = start_time;
		philos[i]->last_meal_time = start_time;
		i++;
	}
}
