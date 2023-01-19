/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:13:29 by sbritani          #+#    #+#             */
/*   Updated: 2023/01/19 20:02:53 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <semaphore.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <sys/time.h>
# include <signal.h>

typedef struct philo_s
{
	int				number;
	long long		time_to_sleep;
	long long		time_to_eat;
	long long		time_to_die;
	long long		start_time;
	long long		last_meal_time;
	int				eaten_times;
	sem_t			*main_semaphore;
	char			*sem_name;
	sem_t			*say_semaphore;
	long long		death_time;
	int				amount_of_meals;

}	t_philo;

typedef struct settings_s
{
	int				amount;
	int				amount_of_meals;
	long long		time_to_sleep;
	long long		time_to_eat;
	long long		time_to_die;
	long long		start_time;
	sem_t			*main_semaphore;
	char			*sem_name;
	sem_t			*say_semaphore;
	char			*say_name;
	t_philo			**philos;
	int				*pids;
} t_settings;

int	get_other_time(void);
t_philo	*create_philo(t_settings *settings, int number);
void	create_philos(t_settings *settings);
void	free_philos(t_philo **philos);
void	check_death(t_philo *philo);
void	check_ate_enough(t_philo *philo);

#endif