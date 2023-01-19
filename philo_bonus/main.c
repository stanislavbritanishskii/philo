/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:13:28 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/19 19:56:06 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	say(sem_t *say_sem, int number, char *phrase, int final)
{
	sem_wait(say_sem);
	printf("%d %d %s\n", get_other_time(), number, phrase);
	if (!final)
		sem_post(say_sem);
}

long long	get_time(void)
{
	static struct timeval	tv;
	static struct timezone	tz;
	long long				res;

	gettimeofday(&tv, &tz);
	res = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (res);
}

int	get_other_time(void)
{
	static long long		start = 0;
	int						res;

	if (start == 0)
	{
		start = get_time();
		return (0);
	}
	else
	{
		res = (int)(get_time() - start);
		return (res);
	}
}

t_settings	*create_settings(int count, long long time_to_eat, long long time_to_die, long long time_to_sleep)
{
	t_settings *res;

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
	res->main_semaphore = sem_open(res->sem_name, O_CREAT, S_IRGRP | S_IWGRP, count);
	res->say_semaphore = sem_open(res->say_name, O_CREAT, S_IRGRP | S_IWGRP, 1);
	create_philos(res);
	return (res);
}

void	finish(t_settings *settings)
{
	free_philos(settings->philos);
	free(settings->pids);
	// free(settings->main_semaphore);
	// free(settings->sem_name);
	free(settings);
	exit(0);
}



void	sleep_for(int time_to_sleep, t_philo *philo)
{
	int	end_time;
	int	death_time;

	end_time = get_other_time() + time_to_sleep;
	while (get_other_time() < end_time)
	{
		check_death(philo);
		usleep(100);
	}
	// printf("%d should die at %lld\n", philo->number, philo->death_time);
}

void	update_meals(t_philo *philo)
{
	philo->last_meal_time = get_other_time();
	philo->death_time = philo->last_meal_time + philo->time_to_die;
	philo->eaten_times++;
}

void main_forked_process(t_philo *philo)
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
	int amount_of_exited;
	int exit_status;

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
}

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
			return (0);
	}
	return (res);
}

int main(int argc, char **argv)
{
	int pid;
	int i;
	int amount_of_meals;
	t_settings *settings;

	if (argc == 5)
		amount_of_meals = -1;
	else if (argc == 6)
		amount_of_meals = ft_atoi(argv[5]);
	else
		return (0);
	settings = create_settings(ft_atoi(argv[1]), ft_atoi(argv[3]), ft_atoi(argv[2]), ft_atoi(argv[4]));
	settings->amount_of_meals = amount_of_meals;
	settings->amount_of_meals = amount_of_meals;
	for (int i = 0; i < settings->amount; i++)
		settings->philos[i]->amount_of_meals = settings->amount_of_meals;
	i = 0;
	get_other_time();
	while (i < settings->amount)
	{
		// printf("%d\n", i);
		settings->pids[i] = fork();
		if (!settings->pids[i])
		{
			update_meals(settings->philos[i]);
			settings->philos[i]->eaten_times--;
			main_forked_process(settings->philos[i]);
			return (0);
		}
		i++;
		if (i == settings->amount / 2)
			usleep(5000);
	}
	waitress(settings);
	sem_unlink(settings->sem_name);
	sem_close(settings->main_semaphore);
	return(0);
}