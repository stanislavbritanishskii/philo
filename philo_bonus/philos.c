/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:55:14 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/19 19:56:09 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_philo(t_settings *settings, int number)
{
	t_philo *res;

	res = malloc(sizeof(t_philo));
	res->number = number;
	res->amount_of_meals = 0;
	res->eaten_times = 0;
	res->last_meal_time = get_other_time();
	res->time_to_die = settings->time_to_die;
	res->death_time = res->last_meal_time + res->time_to_die;
	res->time_to_eat = settings->time_to_eat;
	res->time_to_sleep = settings->time_to_sleep;
	res->main_semaphore = settings->main_semaphore;
	res->say_semaphore = settings->say_semaphore;
	return (res);
}


void	create_philos(t_settings *settings)
{
	int	i;
	
	settings->philos = malloc(sizeof(t_philo *) * (settings->amount + 1));
	i = 0;
	while (i < settings->amount)
	{
		settings->philos[i] = create_philo(settings, i);
		i++;
	}
	settings->philos[i] = NULL;
}

void	free_philos(t_philo **philos)
{
	int	i;
	
	i = -1;
	while(philos[++i])
		free(philos[i]);
	free(philos);
}

void	check_death(t_philo *philo)
{
	if (get_other_time() > philo->death_time)
	{
		say(philo->say_semaphore, philo->number, "died", 1);
		exit(10);
	}
}

void	check_ate_enough(t_philo *philo)
{
	if (philo->amount_of_meals == -1)
		return ;
	if (philo->amount_of_meals <= philo->eaten_times)
		exit(0);
}