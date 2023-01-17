/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 22:15:43 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/17 19:16:19 by sbritani         ###   ########.fr       */
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
	pthread_mutex_lock(philo->say_lock);
	if (okay(philo))
	{
		printf("%d %d %s\n",
			get_other_time(philo->time_lock), philo->number, phrase);
	}
	pthread_mutex_unlock(philo->say_lock);
	return (1);
}

int	mmax(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	part_of_main_eat(t_philo *philo)
{
	update_meals(philo);
	say("is eating", philo);
	sleep_for(philo->time_to_eat, philo);
}

void	*main_eat(void *var)
{
	t_philo	*philo;

	philo = (t_philo *)var;
	while (okay(philo))
	{
		pthread_mutex_lock(philo->forks[philo->number]);
		if (okay(philo))
		{
			say("has taken a fork", philo);
			pthread_mutex_lock(philo->forks[(philo->number + 1)
				% philo->total]);
			if (okay(philo))
				part_of_main_eat(philo);
			pthread_mutex_unlock(philo->forks[(philo->number + 1)
				% philo->total]);
		}
		pthread_mutex_unlock(philo->forks[philo->number]);
		say("is sleeping", philo);
		sleep_for(philo->time_to_sleep, philo);
		say("is thinking", philo);
	}
	return (NULL);
}
