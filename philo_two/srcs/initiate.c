/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 12:36:23 by thgermai          #+#    #+#             */
/*   Updated: 2020/11/04 05:37:05 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void		set_init_value(t_philo *philo, sem_t *forks,
	t_setting *setting, int i)
{
	philo->forks = forks;
	philo->id = i + 1;
	philo->setting = setting;
	philo->n_eat = setting->nb_time_eat;
}

static int		initiate_philos(t_setting *setting,
	t_philo *philos, sem_t *forks)
{
	int				i;
	sem_t			*speaking;

	if (!(speaking = create_sem("/speaking", 1)))
		return (EXIT_FAILURE);
	i = -1;
	g_start_time = get_current_time();
	setting->end_count = 0;
	setting->end_signal = 0;
	while (++i < setting->num_of_philo)
	{
		philos[i].speaking = speaking;
		set_init_value(&philos[i], forks, setting, i);
		philos[i].monitor_name = get_name(philos[i].id);
		if (!(philos[i].monitor_sem = create_sem(philos[i].monitor_name, 1)))
			return (EXIT_FAILURE);
		pthread_create(&philos[i].thread, NULL, start_routine, philos + i);
		pthread_detach(philos[i].thread);
		usleep(philos->setting->time_to_eat);
	}
	return (EXIT_SUCCESS);
}

static void		*wait_philo_died(void *arg)
{
	t_philo		*philos;

	philos = (t_philo *)arg;
	while (!philos->setting->end_signal &&
		philos->setting->end_count != philos->setting->num_of_philo)
		;
	return (NULL);
}

static void		clean_mutex_thread(t_philo *philos)
{
	int		i;

	i = -1;
	while (++i < philos->setting->num_of_philo)
	{
		if (philos[i].monitor_sem)
			sem_unlink(philos[i].monitor_name);
		free(philos[i].monitor_name);
	}
	sem_unlink("/forks");
	sem_unlink("/speaking");
}

void			initiate(t_setting *setting)
{
	sem_t			*forks;
	t_philo			*philos;

	if (!(forks = create_sem("/forks", setting->num_of_philo)))
		return ;
	if (!(philos = malloc(sizeof(t_philo) * setting->num_of_philo)))
	{
		sem_unlink("/forks");
		return ;
	}
	if (initiate_philos(setting, philos, forks) == EXIT_SUCCESS)
		wait_philo_died(philos);
	clean_mutex_thread(philos);
	free(philos);
}
