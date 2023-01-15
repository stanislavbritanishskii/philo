/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:37:59 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/15 15:42:22 by sbritani         ###   ########.fr       */
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

void	and_more_philo_vars(t_philo **philos, long long time_to_die)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		philos[i]->time_to_die = time_to_die;
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
	res->count = count;
	res->forks = init_forks(count);
	res->philos = create_philos(count, res->ok, res->forks, res->okay_lock);
	res->done = 0;
	return (res);
}
