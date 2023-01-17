/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:15:52 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/17 19:25:41 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_settings *settings)
{
	int	i;

	i = 0;
	while (i < settings->count)
	{
		pthread_join(*settings->philos[i]->thread, NULL);
		i++;
	}
}

void	finita(t_settings *settings)
{
	join_threads(settings);
	pthread_mutex_destroy(settings->say_lock);
	free(settings->say_lock);
	pthread_mutex_destroy(settings->time_lock);
	free(settings->time_lock);
	destroy_philos(settings->philos);
	destroy_forks(settings->forks);
	free(settings);
}

int	check_initial(t_settings *settings)
{
	if (settings->time_to_die && settings->time_to_eat
		&& settings->time_to_sleep && settings->count > 1)
		return (1);
	else if (settings->count == 1)
	{
		say("has taken a fork", settings->philos[0]);
		sleep_for(settings->time_to_die, settings->philos[0]);
		say("died", settings->philos[0]);
	}
	if (settings->count)
		pthread_mutex_destroy(settings->say_lock);
	free(settings->say_lock);
	pthread_mutex_destroy(settings->time_lock);
	free(settings->time_lock);
	destroy_philos(settings->philos);
	destroy_forks(settings->forks);
	free(settings);
	return (0);
}

void	destroy_philos(t_philo **philos)
{
	int	i;

	i = -1;
	while (philos[++i])
	{
		pthread_mutex_destroy(philos[i]->eat_lock);
		pthread_mutex_destroy(philos[i]->okay_lock);
		pthread_detach(*philos[i]->thread);
		free(philos[i]->thread);
		free(philos[i]->eat_lock);
		free(philos[i]->okay_lock);
		free(philos[i]);
	}
	free(philos);
}

void	destroy_forks(pthread_mutex_t **forks)
{
	int	i;

	i = -1;
	while (forks[++i])
	{
		pthread_mutex_destroy(forks[i]);
		free(forks[i]);
	}
	free(forks);
}
