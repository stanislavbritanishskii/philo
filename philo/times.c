/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:54:32 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/16 21:51:04 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	static struct timeval	tv;
	static struct timezone	tz;
	long long		res;

	gettimeofday(&tv, &tz);
	res = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (res);
}

int	get_other_time(pthread_mutex_t *time_lock)
{
	static long long		start = 0;
	int						res;

	pthread_mutex_lock(time_lock);
	if (start == 0)
	{
		start = get_time();
	pthread_mutex_unlock(time_lock);
		return (0);
	}
	else
	{
		res = (int)(get_time() - start);
	pthread_mutex_unlock(time_lock);
		return (res);
	}
}
