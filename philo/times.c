/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:54:32 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/15 15:35:48 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;
	struct timezone	tz;
	long long		res;

	gettimeofday(&tv, &tz);
	res = tv.tv_sec * 10000 + tv.tv_usec / 100;
	return (res);
}

int	get_other_time(void)
{
	static long long		start = 0;
	static pthread_mutex_t	lock;
	int						res;

	if (start == 0)
	{
		start = get_time();
		pthread_mutex_init(&lock, NULL);
		return (0);
	}
	else
	{
		pthread_mutex_lock(&lock);
		res = (int)(get_time() - start);
		pthread_mutex_unlock(&lock);
		return (res);
	}
}
