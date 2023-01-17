/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:15:56 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/17 19:20:21 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_for(int time_to_sleep, t_philo *philo)
{
	int	end_time;

	end_time = get_other_time(philo->time_lock) + time_to_sleep;
	while (get_other_time(philo->time_lock) < end_time)
	{
		if (okay(philo))
			usleep(100);
		else
			return ;
	}
}

pthread_mutex_t	*create_fork(void)
{
	pthread_mutex_t	*res;

	res = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(res, NULL);
	return (res);
}

pthread_mutex_t	**init_forks(int n)
{
	pthread_mutex_t	**res;
	int				i;

	i = 0;
	res = malloc(sizeof(pthread_mutex_t *) * (n + 1));
	while (i < n)
	{
		res[i] = create_fork();
		i++;
	}
	res[i] = NULL;
	return (res);
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
