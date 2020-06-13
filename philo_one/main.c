/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 21:52:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/06/13 14:31:25 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/* temporaray lib */
#include <stdio.h>

long unsigned int		get_current_time(void)
{
	struct timeval		t1;

	gettimeofday(&t1, NULL);
	return ((t1.tv_sec * 1000) + (t1.tv_usec / 1000));
}

void					display(pthread_mutex_t *speaking, int id, char *status)
{
	pthread_mutex_lock(speaking);
	printf("%lu %d %s\n", get_current_time(), id, status);
	pthread_mutex_unlock(speaking);
}

void					*start_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		// Eating
		pthread_mutex_lock(&philo->left_fork->mutex);
		display(philo->speaking, philo->id, FORK);
		pthread_mutex_lock(&philo->right_fork->mutex);
		display(philo->speaking, philo->id, FORK);
		philo->death_time = get_current_time() + philo->setting->time_to_die;
		display(philo->speaking, philo->id, EAT);
		usleep(philo->setting->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		// Sleeping
		display(philo->speaking, philo->id, SLEEP);
		usleep(philo->setting->time_to_sleep * 1000);
		// Thinking
		display(philo->speaking, philo->id, THINK);
	}
	return (NULL);
}

void					*monitoring_thread(void *philos)
{
	int			i;
	t_philo		*philo;

	i = -1;
	philo = NULL;
	while (++i <= ((t_philo *)philos)->setting->num_of_philo)
	{
		if (i == ((t_philo *)philos)->setting->num_of_philo)
			i = 0;
		philo = ((t_philo *)philos + i);
		if (philo->death_time <= get_current_time())
		{
			pthread_mutex_lock(philo->speaking);
			printf("%lu %d died\n", get_current_time(), philo->id);
			return (NULL);
		}
	}
	return (NULL);
}

int						main(int ac, char **av)
{
	t_setting		setting;
	pthread_t		monitoring;

	if (ac <= 4 || ac > 6)
	{
		write(2, WRONG_SETTINGS, sizeof(WRONG_SETTINGS));
		return (0);
	}
	parse_setting(&setting, ac, av);
	initiate(&setting, &monitoring);
	pthread_join(monitoring, NULL);
	return (0);
}
