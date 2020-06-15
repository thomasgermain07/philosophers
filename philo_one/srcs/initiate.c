/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 12:36:23 by thgermai          #+#    #+#             */
/*   Updated: 2020/06/15 15:09:29 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h> // a del

static void		initiate_philos(t_setting *setting,
	t_philo *philos, pthread_mutex_t *forks)
{
	int						i;
	static pthread_mutex_t	speaking;

	pthread_mutex_init(&speaking, NULL);
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
		(philos + i)->n_eat = 0;
		(philos + i)->death_time = get_current_time() + setting->time_to_die;
		pthread_create(&(philos + i)->thread, NULL, start_routine, philos + i);
		usleep(philos->setting->time_to_eat * 100);
	}
}

static void		clean_mutex_thread(t_philo *philos)
{
	int		i;

	i = -1;
	pthread_mutex_destroy(philos->speaking);
	while (++i < philos->setting->num_of_philo)
		pthread_mutex_destroy((philos + i)->right_fork);
}

void		initiate(t_setting *setting)
{
	pthread_mutex_t	forks[setting->num_of_philo];
	t_philo			philos[setting->num_of_philo];
	int				i;

	i = -1;
	while (++i < setting->num_of_philo)
		pthread_mutex_init(&forks[i], NULL);
	initiate_philos(setting, philos, forks);
	wait_philo_died(philos);
	clean_mutex_thread(philos);
}

static int		check_param(t_setting *setting, int ac)
{
	if (setting->num_of_philo <= 0)
		return (1);
	if (setting->time_to_die < 0 || setting->time_to_eat < 0 ||
		setting->time_to_sleep < 0)
		return (1);
	if (ac == 6 && setting->number_of_time_to_eat < 0)
		return (1);
	return (0);
}

int				parse_setting(t_setting *setting, int ac, char **arg)
{
	setting->num_of_philo = ft_atoi(arg[1]);
	setting->time_to_die = ft_atoi(arg[2]);
	setting->time_to_eat = ft_atoi(arg[3]);
	setting->time_to_sleep = ft_atoi(arg[4]);
	if (ac == 6)
		setting->number_of_time_to_eat = ft_atoi(arg[5]);
	else
		setting->number_of_time_to_eat = -1;
	if (check_param(setting, ac))
	{
		printf("Error: wrong parameters\n");
		return (-1);
	}
	return (0);
}
