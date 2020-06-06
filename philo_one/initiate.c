/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 16:22:16 by thomasgerma       #+#    #+#             */
/*   Updated: 2020/06/06 23:54:22 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		initiate_forks(int num, t_fork *forks)
{
	int			i;

	i = -1;
	while (++i < num)
	{
		(forks + i)->id = i;
		pthread_mutex_init(&(forks + i)->mutex, NULL);
	}
}

void		initiate_philos(t_setting *setting, t_philo *philos, t_fork *forks)
{
	int 			i;
	pthread_mutex_t speaking;

	pthread_mutex_init(&speaking, NULL);
	philos->id = 1;
	philos->left_fork = forks + (setting->num_of_philo - 1);
	philos->right_fork = forks;
	pthread_create(&philos->thread, NULL, eating, philos);
	philos->speaking = &speaking;
	i = 0;
	while (++i < setting->num_of_philo)
	{
		(philos + i)->id = i + 1;
		(philos + i)->left_fork = forks + (i - 1);
		(philos + i)->right_fork = forks + i;
		pthread_create(&(philos + i)->thread, NULL, eating, philos + i);
		(philos + i)->speaking = &speaking;
	}
}

void		initiate(t_setting *setting)
{
	t_fork		forks[setting->num_of_philo];
	t_philo		philos[setting->num_of_philo];
	int			i;

	i = -1;
	while (++i < setting->num_of_philo)
		ft_memccpy(&philos[i], setting, sizeof(setting), sizeof(setting));
	initiate_forks(setting->num_of_philo, forks);
	initiate_philos(setting, philos, forks);
	i = -1;
	while (++i < setting->num_of_philo)
		pthread_join(philos[i].thread, NULL);
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
