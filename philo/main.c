/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:48:15 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/15 15:32:39 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_settings *settings)
{
	int	i;

	i = 0;
	while (i < settings->count)
	{
		pthread_create(settings->philos[i]->thread,
			NULL, main_eat, settings->philos[i]);
		i = i + 2;
	}
	usleep(2);
	i = 1;
	while (i < settings->count)
	{
		pthread_create(settings->philos[i]->thread,
			NULL, main_eat, settings->philos[i]);
		i = i + 2;
	}
}

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

void	main_thread(t_settings *settings, int i, int all_ate_enough,
					int amount_of_meals)
{
	while (!settings->done)
	{
		i = 0;
		all_ate_enough = 1;
		while (!settings->done && settings->philos[i])
		{
			if (settings->philos[i]->last_meal_time
				+ settings->time_to_die <= get_other_time() / 10)
			{
				say("died", settings->philos[i]);
				settings->ok[0] = 0;
				settings->done = 1;
			}
			all_ate_enough *= (settings->philos[i]->eaten_times
					>= amount_of_meals && amount_of_meals >= 0);
			i++;
		}
		if (all_ate_enough)
		{
			settings->ok[0] = 0;
			settings->done = 1;
		}
		usleep(10);
	}
}

int	main(int argc, char **argv)
{
	int			i;
	int			amount_of_meals;
	int			all_ate_enough;
	t_settings	*settings;

	if (argc == 6)
		amount_of_meals = -1;
	else if (argc == 7)
		amount_of_meals = ft_atoi(argv[6]);
	else
		return (0);
	settings = create_settings(ft_atoi(argv[1]));
	settings->time_to_die = ft_atoi(argv[2]);
	settings->time_to_eat = ft_atoi(argv[3]);
	settings->time_to_sleep = ft_atoi(argv[4]);
	settings->time_to_sleep = ft_atoi(argv[5]);
	settings->amount_of_meals = amount_of_meals;
	some_more_vars_for_philos(settings->philos,
		settings->time_to_eat, settings->time_to_sleep, settings->start_time);
	create_threads(settings);
	main_thread(settings, i, all_ate_enough, amount_of_meals);
	join_threads(settings);
}
