/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 12:36:23 by thgermai          #+#    #+#             */
/*   Updated: 2020/06/13 14:31:10 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/* temporaray lib */
#include <stdio.h>

void		initiate_forks(int num, t_fork *forks)
{
	int			i;

	i = -1;
	while (++i < num)
	{
		(forks + i)->id = i;
		pthread_mutex_init(&(forks + i)->mutex, NULL);
		// pthread_mutex_unlock(&(forks + i)->mutex);
	}
}

void		initiate_philos(t_setting *setting, t_philo *philos, t_fork *forks)
{
	int				i;
	pthread_mutex_t speaking;

	pthread_mutex_init(&speaking, NULL);
	// pthread_mutex_unlock(&speaking);
	i = -1;
	while (++i < setting->num_of_philo)
	{
		if (i == 0)
			philos->left_fork = forks + (setting->num_of_philo - 1);
		else
			(philos + i)->left_fork = forks + (i - 1);
		(philos + i)->right_fork = forks + i;
		(philos + i)->id = i + 1;
		(philos + i)->speaking = &speaking;
		(philos + i)->setting = setting;
		(philos + i)->death_time = get_current_time() + setting->time_to_die;
		pthread_create(&(philos + i)->thread, NULL, start_routine, philos + i);
		usleep(philos->setting->time_to_eat * 1000);
	}
}

void		clean_mutex_thread(t_philo *philos)
{
	int		i;

	i = -1;
	pthread_mutex_destroy(philos->speaking);
	while (++i < philos->setting->num_of_philo)
		pthread_mutex_destroy(&(philos + i)->right_fork->mutex);
}

void		initiate(t_setting *setting, pthread_t *monitoring)
{
	t_fork			forks[setting->num_of_philo];
	t_philo			philos[setting->num_of_philo];

	initiate_forks(setting->num_of_philo, forks);
	initiate_philos(setting, philos, forks);
	pthread_create(monitoring, NULL, monitoring_thread, philos);
}

void		parse_setting(t_setting *setting, int ac, char **arg)
{
	setting->num_of_philo = ft_atoi(arg[1]);
	setting->time_to_die = ft_atoi(arg[2]);
	setting->time_to_eat = ft_atoi(arg[3]);
	setting->time_to_sleep = ft_atoi(arg[4]);
	if (ac == 6)
		setting->number_of_time_to_eat = ft_atoi(arg[5]);
	else
		setting->number_of_time_to_eat = -1;
}
