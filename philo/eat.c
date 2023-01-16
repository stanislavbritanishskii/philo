/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 22:15:43 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/16 20:37:46 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	okay(t_philo *philo)
{
	int	res;

	res = 0;
	pthread_mutex_lock(philo->okay_lock);
	res = philo->okay;
	pthread_mutex_unlock(philo->okay_lock);
	return (res);
}

int	say(char *phrase, t_philo *philo)
{
	char	*part;

	pthread_mutex_lock(philo->say_lock);
	if (okay(philo))
		printf("%d %d %s\n", get_other_time(philo->time_lock), philo->number, phrase);
	pthread_mutex_unlock(philo->say_lock);
	return (1);
}

int	mmax(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	sleep_for(int time_to_sleep, t_philo *philo)
{
	int	end_time;

	end_time = get_other_time(philo->time_lock) + time_to_sleep;
	usleep(mmax(time_to_sleep - 20, 0));
	while (get_other_time(philo->time_lock) < end_time)
		usleep(1);
}

void	*main_eat(void *var)
{
	t_philo	*philo;
	int		time;

	philo = (t_philo *)var;
	
	// pthread_mutex_lock(philo->start_lock);
	// pthread_mutex_unlock(philo->start_lock);
	while (okay(philo))
	{
		pthread_mutex_lock(philo->forks[philo->number]);
		if (okay(philo))
		{
			pthread_mutex_lock(philo->forks[(philo->number + 1) % philo->total]);
			if (okay(philo))
			{
				update_meals(philo);
				say("started eating", philo);
				sleep_for(philo->time_to_eat, philo);
			}
			pthread_mutex_unlock(philo->forks[(philo->number + 1) % philo->total]);
		}
		pthread_mutex_unlock(philo->forks[philo->number]);
		if (okay(philo))
			say("started sleeping", philo);
		sleep_for(philo->time_to_sleep, philo);
	}
	return (NULL);
}
