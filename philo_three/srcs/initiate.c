/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 12:36:23 by thgermai          #+#    #+#             */
/*   Updated: 2020/11/03 03:22:04 by thgermai         ###   ########.fr       */
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
	t_philo *philos, sem_t *forks, pid_t *pids)
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
		if ((pids[i] = fork()) == 0)
			start_routine(&philos[i]);
		usleep(philos->setting->time_to_eat);
	}
	return (EXIT_SUCCESS);
}

static void		clean_mutex_thread(t_philo *philos, pid_t *pids)
{
	int		i;

	i = -1;
	while (++i < philos->setting->num_of_philo)
	{
		if (philos[i].monitor_sem)
			sem_unlink(philos[i].monitor_name);
		free(philos[i].monitor_name);
		kill(pids[i], 3);
	}
	sem_unlink("/forks");
	sem_unlink("/speaking");
}

void			initiate(t_setting *setting)
{
	sem_t			*forks;
	t_philo			*philos;
	pid_t			*pids;

	if (!(forks = create_sem("/forks", setting->num_of_philo)))
		return ;
	if (!(pids = malloc(sizeof(pid_t) * setting->num_of_philo)))
	{
		sem_unlink("/forks");
		return ;
	}
	if (!(philos = malloc(sizeof(t_philo) * setting->num_of_philo)))
	{
		sem_unlink("/forks");
		free(pids);
		return ;
	}
	if (initiate_philos(setting, philos, forks, pids) == EXIT_SUCCESS)
		waitpid(-1, NULL, 0);
	clean_mutex_thread(philos, pids);
	free(pids);
	free(philos);
}
