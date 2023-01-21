/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:48:15 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/21 22:13:00 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	part_of_main_thread(t_settings *settings, int i, long long *meals)
{
	int	time_of_death;

	if (meals[0]
		+ settings->time_to_die <= get_other_time(settings->time_lock))
	{
		time_of_death = get_other_time(settings->time_lock);
		set_all_dead(settings->philos);
		pthread_mutex_lock(settings->say_lock);
		printf("%d %d died\n", time_of_death, i);
		pthread_mutex_unlock(settings->say_lock);
		settings->done = 1;
	}
}

void	another_part_of_main_thread(t_settings *settings, int all_ate_enough)
{
	if (all_ate_enough)
	{
		set_all_dead(settings->philos);
		settings->done = 1;
	}
}

void	main_thread(t_settings *settings, int amount_of_meals)
{
	int			i;
	int			all_ate_enough;
	long long	*meals;

	i = 0;
	all_ate_enough = 0;
	while (!settings->done)
	{
		i = 0;
		all_ate_enough = 1;
		while (!settings->done && settings->philos[i])
		{
			meals = get_meals(settings->philos[i]);
			part_of_main_thread(settings, i, meals);
			all_ate_enough *= (meals[1]
					>= amount_of_meals && amount_of_meals >= 0);
			i++;
			free(meals);
		}
		another_part_of_main_thread(settings, all_ate_enough);
		usleep(1000);
	}
}

void	func(int argc, char **argv)
{
	int			amount_of_meals;
	t_settings	*settings;

	if (argc == 5)
		amount_of_meals = -1;
	else if (argc == 6)
		amount_of_meals = ft_atoi(argv[5]);
	else
		return ;
	settings = create_settings(ft_atoi(argv[1]));
	settings->time_to_die = ft_atoi(argv[2]);
	settings->time_to_eat = ft_atoi(argv[3]);
	settings->time_to_sleep = ft_atoi(argv[4]);
	some_more_vars_for_philos(settings->philos,
		settings->time_to_eat, settings->time_to_sleep, settings->start_time);
	and_more_philo_vars(settings->philos, settings->time_lock);
	if (!check_initial(settings))
		return ;
	create_threads(settings);
	settings->amount_of_meals = amount_of_meals;
	main_thread(settings, amount_of_meals);
	finita(settings);
}

int	main(int argc, char **argv)
{
	func(argc, argv);
}
