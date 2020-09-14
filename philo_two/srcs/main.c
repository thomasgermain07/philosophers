/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 16:11:53 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/03 13:45:54 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h> // temp

static void			eating(t_philo *philo)
{
	sem_wait(philo->sem);
	display(philo->speaking, philo->id, FORK);
	sem_wait(philo->sem);
	display(philo->speaking, philo->id, FORK);
	philo->death_time = get_current_time() + philo->setting->time_to_die;
	display(philo->speaking, philo->id, EAT);
	usleep(philo->setting->time_to_eat * 1000);
	sem_post(philo->sem);
	sem_post(philo->sem);
	philo->n_eat++;
}

void				*start_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->setting->number_of_time_to_eat != -1)
			if (philo->n_eat == philo->setting->number_of_time_to_eat)
				return (NULL);
		eating(philo);
		if (philo->n_eat == philo->setting->number_of_time_to_eat)
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

static void			initate_philos(t_setting *setting)
{
	t_philo 		philos[setting->num_of_philo];
	sem_t			*sem;
	sem_t			*speaking;

	sem_unlink("/sem");
	sem = sem_open("/sem", O_CREAT | O_EXCL, 0644, setting->num_of_philo);
	if (sem == SEM_FAILED)
	{
		write(2, SEM_OPEN_FAILED, ft_strlen(SEM_OPEN_FAILED));
		exit(EXIT_FAILURE);
	}
	sem_unlink("/speaking");
	speaking = sem_open("/speaking", O_CREAT | O_EXCL, 0644, 1);
	if (speaking == SEM_FAILED)
	{
		write(2, SEM_OPEN_FAILED, ft_strlen(SEM_OPEN_FAILED));
		exit(EXIT_FAILURE);
	}
	create_philos(philos, setting, sem, speaking);
	wait_philo_died((void *)philos);
	printf("C'est encore plus bizzare si ca fini ici\n");
	sem_close(speaking);
	sem_close(sem);
	sem_unlink("/sem");
	sem_unlink("/speaking");
}

int			main(int ac, char **av)
{
	t_setting		setting;

	if (ac != 5 && ac != 6)
	{
		write(2, MISS_SETTINGS, ft_strlen(MISS_SETTINGS));
		return (EXIT_FAILURE);
	}
	if (parse_setting(&setting, ac, av))
		return (EXIT_FAILURE);
	initate_philos(&setting);
	return (EXIT_SUCCESS);
}
