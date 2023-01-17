/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:48:15 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/17 18:24:10 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign += -2 * (str[i++] == '-');
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9')
		{
		res *= 10;
		res += sign * (str[i] - '0');
		i++;
		}
		else
			return(0);
	}
	return (res);
}

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
	usleep(1000);
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
	int time_of_death;
	long long *meals;
	while (!settings->done)
	{
		i = 0;
		all_ate_enough = 1;
		while (!settings->done && settings->philos[i])
		{
			meals = get_meals(settings->philos[i]);
			if (meals[0]
				+ settings->time_to_die < get_other_time(settings->time_lock))
			{
				time_of_death = get_other_time(settings->time_lock);
				set_all_dead(settings->philos);
				pthread_mutex_lock(settings->say_lock);
				printf("%d %d died\n",time_of_death, i);
				pthread_mutex_unlock(settings->say_lock);
				settings->done = 1;
			}
			all_ate_enough *= (meals[1]
					>= amount_of_meals && amount_of_meals >= 0);
			i++;
			free(meals);
		}
		if (all_ate_enough)
		{
			set_all_dead(settings->philos);
			settings->done = 1;
		}
		usleep(1000);
	}
}

void	destroy_forks(pthread_mutex_t **forks)
{
	int	i;

	i = -1;
	while(forks[++i])
	{
		pthread_mutex_destroy(forks[i]);
		free(forks[i]);
	}
	free(forks);
}

void	destroy_philos(t_philo **philos)
{
	int i;

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

void printer(char *str)
{
	static int i = 0;
	printf("that is %d's call in %s\n", i++, str);
}

int check_initial(t_settings *settings)
{
	if (settings->time_to_die && settings->time_to_eat && settings->time_to_sleep && settings->count > 1)
		return (1);
	else if (settings->count == 1)
	{
		say("has taken a fork", settings->philos[0]);
		sleep_for(settings->time_to_die, settings->philos[0]);
		say("died", settings->philos[0]);
	}
	if (settings->count)
		pthread_mutex_destroy(settings->say_lock);
	printer("check");
	free(settings->say_lock);
	printer("check");
	pthread_mutex_destroy(settings->time_lock);
	free(settings->time_lock);
	destroy_philos(settings->philos);
	destroy_forks(settings->forks);
	free(settings);
	return (0);
}
void	func(int argc, char **argv)
{
	int			i;
	int			amount_of_meals;
	int			all_ate_enough;
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
	main_thread(settings, i, all_ate_enough, amount_of_meals);
	join_threads(settings);
	pthread_mutex_destroy(settings->say_lock);
	free(settings->say_lock);
	pthread_mutex_destroy(settings->time_lock);
	free(settings->time_lock);
	destroy_philos(settings->philos);
	destroy_forks(settings->forks);
	free(settings);
}
int main(int argc, char **argv)
{
	func(argc, argv);
	system("leaks output");
}