/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 21:52:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/06/06 23:53:38 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/* temporaray lib */
#include <stdio.h>

void		*thinking(void *philo)
{
	int			diff;

	diff = ((t_philo *)philo)->time_to_die - ((t_philo *)philo)->time_to_eat
		- ((t_philo *)philo)->time_to_sleep;
	pthread_mutex_lock(((t_philo *)philo)->speaking);
	printf("%d is thinking\n", ((t_philo *)philo)->id);
	pthread_mutex_unlock(((t_philo *)philo)->speaking);
	usleep(diff);
	eating(philo);
	return (NULL);

}

void		*sleeping(void *philo)
{
	pthread_mutex_lock(((t_philo *)philo)->speaking);
	printf("%d is sleeping\n", ((t_philo *)philo)->id);
	usleep(((t_philo *)philo)->time_to_sleep);
	pthread_mutex_unlock(((t_philo *)philo)->speaking);
	thinking(philo);
	return (NULL);
}

void		*eating(void *philo)
{
	pthread_mutex_lock(&((t_philo *)philo)->left_fork->mutex);
	pthread_mutex_lock(&((t_philo *)philo)->right_fork->mutex);
	pthread_mutex_lock(((t_philo *)philo)->speaking);
		printf("%d is eating\n", ((t_philo *)philo)->id);
	usleep(((t_philo *)philo)->time_to_eat);
	pthread_mutex_unlock(&((t_philo *)philo)->left_fork->mutex);
	pthread_mutex_unlock(&((t_philo *)philo)->right_fork->mutex);
	pthread_mutex_unlock(((t_philo *)philo)->speaking);
	sleeping(philo);
	return (NULL);
}

int			main(int ac, char **av)
{
	t_setting		setting;

	if (ac <= 4 || ac > 6)
	{
		write(2, WRONG_SETTINGS, sizeof(WRONG_SETTINGS));
		return (0);
	}
	parse_setting(&setting, ac, av);
	initiate(&setting);
	return (0);
}
