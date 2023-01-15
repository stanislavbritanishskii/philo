/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 22:15:43 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/15 18:47:48 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	okay(t_philo *philo)
{
	int	res;

	res = 0;
	pthread_mutex_lock(philo->okay_lock);
	res = *philo->okay;
	pthread_mutex_unlock(philo->okay_lock);
	return (res);
}

int	say(char *phrase, t_philo *philo)
{
	char	*part;

	pthread_mutex_lock(philo->say_lock);
	if (okay(philo))
		printf("%d %d %s\n", get_other_time() / 10, philo->number, phrase);
	pthread_mutex_unlock(philo->say_lock);
	return (1);
}

int	mmax(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	sleep_for(int time_to_sleep)
{
	int	end_time;

	end_time = get_other_time() / 10 + time_to_sleep;
	usleep(mmax(time_to_sleep - 20, 0));
	while (get_other_time() / 10 < end_time)
		usleep(1);
}

void	*main_eat(void *var)
{
	t_philo	*philo;
	int		time;

	philo = (t_philo *)var;
	while (okay(philo))
	{
		pthread_mutex_lock(philo->forks[philo->number]);
		if (okay(philo))
		{
			pthread_mutex_lock(philo->forks[(philo->number + 1) % philo->total]);
			if (okay(philo))
			{
				philo->last_meal_time = get_other_time() / 10;
				philo->eaten_times++;
				say("started eating", philo);
				sleep_for(philo->time_to_eat);
			}
			pthread_mutex_unlock(philo->forks[philo->number]);
		}
		pthread_mutex_unlock(philo->forks[(philo->number + 1) % philo->total]);
		if (okay(philo))
			say("started sleeping", philo);
		sleep_for(philo->time_to_sleep);
	}
	return (NULL);
}
