/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_death.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 11:46:08 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/09 18:15:04 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h> // a del

static void			init_array(t_philo *arr, t_philo *philos)
{
	int			i;

	i = -1;
	while (++i < 8)
		arr[i] = philos[i];
}

static void			*check_philos_health(void *args)
{
	t_philo		philos[8];
	int			i;

	i = -1;
	init_array(philos, (t_philo *)args);
	while (++i <= 8)
	{
		if (i == 8)
			i = 0;
		if (get_current_time() >= philos[i].death_time)
		{
			display(philos[i].speaking, philos[i].id, DEAD);
			*philos[i].signal = 1;
			return (NULL);
		}
	}
	return (NULL);
}

void			wait_philo_died(t_philo *philos)
{
	int			i;
	int			signal;
	pthread_t	thread;

	signal = 0;
	i = -1;
	while (++i < philos->setting->num_of_philo)
		philos[i].signal = &signal;
	i = 0;
	while (philos->setting->num_of_philo - i > 8)
	{
		pthread_create(&thread, NULL, &check_philos_health, (void *)(philos + i));
		i += 8;
	}
	pthread_create(&thread, NULL, &check_philos_health, (void *)(philos + i));
	while (signal != 1)
		;
}
