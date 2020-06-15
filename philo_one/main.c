/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 21:52:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/06/15 15:06:08 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h> // a del

static void			eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	display(philo->speaking, philo->id, FORK);
	pthread_mutex_lock(philo->right_fork);
	display(philo->speaking, philo->id, FORK);
	philo->death_time = get_current_time() + philo->setting->time_to_die;
	display(philo->speaking, philo->id, EAT);
	usleep(philo->setting->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void				*start_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		eating(philo);
		philo->n_eat++;
		if (philo->setting->number_of_time_to_eat != -1 &&
			philo->n_eat == philo->setting->number_of_time_to_eat)
		{
			philo->n_eat = -1;
			return (NULL);
		}
		display(philo->speaking, philo->id, SLEEP);
		usleep(philo->setting->time_to_sleep * 1000);
		display(philo->speaking, philo->id, THINK);
	}
	return (NULL);
}

void				wait_philo_died(void *philos)
{
	int			i;
	int			out;
	t_philo		*philo;

	i = -1;
	out = 0;
	philo = (t_philo *)philos;
	while (++i <= philo->setting->num_of_philo
		&& out != philo->setting->num_of_philo)
	{
		if (i == philo->setting->num_of_philo)
			i = 0;
		philo = ((t_philo *)philos + i);
		philo->n_eat == -1 ? out++ : (out = 0);
		if (philo->n_eat != -1 && philo->death_time <= get_current_time())
		{
			pthread_mutex_lock(philo->speaking);
			printf("%lu %d died\n", get_current_time(), philo->id);
			return ;
		}
	}
}

int					main(int ac, char **av)
{
	t_setting		setting;

	if (ac <= 4 || ac > 6)
	{
		printf("Error: missing arguments\n");
		return (0);
	}
	if (parse_setting(&setting, ac, av) == -1)
		return (0);
	initiate(&setting);
	return (0);
}
