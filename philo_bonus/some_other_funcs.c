/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_other_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:10:28 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/19 20:23:00 by sbritani         ###   ########.fr       */
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
			return (0);
	}
	return (res);
}

void	finish(t_settings *settings)
{
	free_philos(settings->philos);
	free(settings->pids);
	free(settings);
	exit(0);
}

void	update_meals(t_philo *philo)
{
	philo->last_meal_time = get_other_time();
	philo->death_time = philo->last_meal_time + philo->time_to_die;
	philo->eaten_times++;
}

void	say(sem_t *say_sem, int number, char *phrase, int final)
{
	sem_wait(say_sem);
	printf("%d %d %s\n", get_other_time(), number, phrase);
	if (!final)
		sem_post(say_sem);
}
