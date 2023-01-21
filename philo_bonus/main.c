/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:13:28 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/21 22:15:00 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_settings	*create_settings(int count, long long time_to_eat,
		long long time_to_die, long long time_to_sleep)
{
	t_settings	*res;

	res = malloc(sizeof(t_settings));
	res->pids = malloc(sizeof(int *) * (count + 1));
	res->sem_name = "main_sem";
	res->say_name = "say_sem";
	res->amount = count;
	res->time_to_eat = time_to_eat;
	res->time_to_die = time_to_die;
	res->time_to_sleep = time_to_sleep;
	sem_unlink(res->sem_name);
	sem_unlink(res->say_name);
	res->main_semaphore = sem_open(res->sem_name,
			O_CREAT, S_IRGRP | S_IWGRP, count);
	res->say_semaphore = sem_open(res->say_name,
			O_CREAT, S_IRGRP | S_IWGRP, 1);
	create_philos(res);
	return (res);
}

void	main_forked_process(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->main_semaphore);
		check_death(philo);
		say(philo->say_semaphore, philo->number, "has taken a fork", 0);
		sem_wait(philo->main_semaphore);
		check_death(philo);
		say(philo->say_semaphore, philo->number, "started eating", 0);
		update_meals(philo);
		sleep_for(philo->time_to_eat, philo);
		sem_post(philo->main_semaphore);
		sem_post(philo->main_semaphore);
		say(philo->say_semaphore, philo->number, "started sleeping", 0);
		check_ate_enough(philo);
		sleep_for(philo->time_to_sleep, philo);
	}
}

void	waitress(t_settings *settings)
{
	int	i;
	int	amount_of_exited;
	int	exit_status;

	i = 0;
	amount_of_exited = 0;
	exit_status = 0;
	while (exit_status == 0 && amount_of_exited < settings->amount)
	{
		waitpid(-1, &exit_status, 0);
		amount_of_exited++;
	}
	if (amount_of_exited == settings->amount)
	{
		printf("all ate enough\n");
		finish(settings);
	}
	while (i < settings->amount)
	{
		kill(settings->pids[i], SIGKILL);
		waitpid(settings->pids[i], NULL, 0);
		i++;
	}
	sem_unlink(settings->sem_name);
	sem_close(settings->main_semaphore);
}

void	do_forks(t_settings *settings, int i)
{
	while (i < settings->amount)
	{
		settings->pids[i] = fork();
		if (!settings->pids[i])
		{
			update_meals(settings->philos[i]);
			settings->philos[i]->eaten_times--;
			main_forked_process(settings->philos[i]);
			return ;
		}
		i++;
		if (i == settings->amount / 2)
			usleep(1000);
	}
}

int	main(int argc, char **argv)
{
	int			i;
	int			amount_of_meals;
	t_settings	*settings;

	if (argc == 5)
		amount_of_meals = -1;
	else if (argc == 6)
		amount_of_meals = ft_atoi(argv[5]);
	else
		return (0);
	settings = create_settings(ft_atoi(argv[1]), ft_atoi(argv[3]),
			ft_atoi(argv[2]), ft_atoi(argv[4]));
	settings->amount_of_meals = amount_of_meals;
	settings->amount_of_meals = amount_of_meals;
	i = settings->amount + 1;
	while (--i)
		settings->philos[i - 1]->amount_of_meals = settings->amount_of_meals;
	i = 0;
	if (!check_initial(settings))
		return (0);
	get_other_time();
	do_forks(settings, i);
	waitress(settings);
	return (0);
}
