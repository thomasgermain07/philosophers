/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 21:52:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/06/08 19:07:02 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/* temporaray lib */
#include <stdio.h>

long unsigned int		get_current_time(void)
{
	struct timeval		t1;
	long unsigned int	current_time;

	gettimeofday(&t1, NULL);
	current_time = (t1.tv_sec * 1000) + (t1.tv_usec / 1000);
	return (current_time);
}

void					is_alive(t_philo *philo)
{
	if (philo->death_time < get_current_time())
		return (1);
	return (0);
}

void					sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->speaking);
	printf("%lu %d is sleeping\n", get_current_time(), philo->id);
	pthread_mutex_unlock(philo->speaking);
	usleep(philo->setting->time_to_sleep * 1000);
	is_alive((t_philo *)philo);
	pthread_mutex_lock(philo->speaking);
	printf("%lu %d is thinking\n", get_current_time(), philo->id);
	pthread_mutex_unlock(philo->speaking);
}

void					eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->right_fork->mutex);
	is_alive(philo);
	pthread_mutex_lock(philo->speaking);
	printf("%lu %d is eating\n", get_current_time(), philo->id);
	pthread_mutex_unlock(philo->speaking);
	usleep(philo->setting->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	philo->death_time = get_current_time() + philo->setting->time_to_die;
}

void					*start_routine(void *philo)
{
	((t_philo *)philo)->death_time = get_current_time() +
		((t_philo *)philo)->setting->time_to_die;
	while (1)
	{
		eating(((t_philo *)philo));
		sleeping(((t_philo *)philo));
	}
	return (NULL);
}

int						main(int ac, char **av)
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
