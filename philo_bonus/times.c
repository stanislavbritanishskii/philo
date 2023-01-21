/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:07:25 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/21 20:21:13 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	sleep_for(int time_to_sleep, t_philo *philo)
{
	int	end_time;

	end_time = get_other_time() + time_to_sleep;
	while (get_other_time() < end_time)
	{
		check_death(philo);
		usleep(100);
	}
}
