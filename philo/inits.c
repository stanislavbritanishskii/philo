/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:37:59 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/16 20:40:52 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


pthread_mutex_t	*create_fork(void)
{
	pthread_mutex_t	*res;

	res = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(res, NULL);
	return (res);
}

pthread_mutex_t	**init_forks(int n)
{
	pthread_mutex_t	**res;

	res = malloc(sizeof(pthread_mutex_t *) * n);
	while (n--)
		res[n] = create_fork();
	return (res);
}

pthread_t	*create_thread(void)
{
	pthread_t	*res;

	res = malloc(sizeof(pthread_t));
	return (res);
}

void	and_more_philo_vars(t_philo **philos, pthread_mutex_t *time_lock, pthread_mutex_t *start_lock)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		philos[i]->time_lock = time_lock;
		philos[i]->start_lock = start_lock;
		i++;
	}
}

t_settings	*create_settings(int count)
{
	t_settings	*res;

	res = malloc(sizeof(t_settings));
	res->ok = malloc(sizeof(int));
	res->ok[0] = 1;
	res->okay_lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(res->okay_lock, NULL);
	res->time_lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(res->time_lock, NULL);
	res->start_lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(res->start_lock, NULL);
	res->count = count;
	res->forks = init_forks(count);
	res->philos = create_philos(count, 1, res->forks, res->okay_lock);
	res->say_lock = res->philos[0]->say_lock;
	res->done = 0;
	return (res);
}


long long *get_meals(t_philo *philo)
{
	long long *res;

	res = malloc(sizeof(long long) * 2);
	pthread_mutex_lock(philo->eat_lock);
	res[0] = philo->last_meal_time;
	res[1] = philo->eaten_times;
	pthread_mutex_unlock(philo->eat_lock);
	return(res);
}

void update_meals(t_philo *philo)
{
	pthread_mutex_lock(philo->eat_lock);
	philo->last_meal_time = get_other_time(philo->time_lock);
	philo->eaten_times++;
	pthread_mutex_unlock(philo->eat_lock);
}