/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 12:36:23 by thgermai          #+#    #+#             */
/*   Updated: 2020/10/27 22:45:47 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void		set_init_value(t_philo *philo, pthread_mutex_t *forks,
	t_setting *setting, int i)
{
	philo->right_fork = forks + i;
	philo->id = i + 1;
	philo->setting = setting;
	philo->n_eat = setting->nb_time_eat;
}

static int		initiate_philos(t_setting *setting,
	t_philo *philos, pthread_mutex_t *forks)
{
	int						i;
	static pthread_mutex_t	speaking;

	pthread_mutex_init(&speaking, NULL);
	i = -1;
	g_start_time = get_current_time();
	setting->end_count = 0;
	setting->end_signal = 0;
	while (++i < setting->num_of_philo)
	{
		if (i == 0)
			philos->left_fork = forks + (setting->num_of_philo - 1);
		else
			philos[i].left_fork = forks + (i - 1);
		philos[i].speaking = &speaking;
		set_init_value(&philos[i], forks, setting, i);
		if (!(philos[i].eating = malloc(sizeof(pthread_mutex_t))))
			return (EXIT_FAILURE);
		pthread_mutex_init(philos[i].eating, NULL);
		pthread_create(&philos[i].thread, NULL, start_routine, philos + i);
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
	pthread_mutex_destroy(philos->speaking);
	while (++i < philos->setting->num_of_philo)
	{
		pthread_detach(philos[i].monitor);
		pthread_detach(philos[i].thread);
		pthread_mutex_destroy(philos[i].right_fork);
		pthread_mutex_destroy(philos[i].eating);
		free(philos[i].eating);
	}
}

void			initiate(t_setting *setting)
{
	pthread_mutex_t	*forks;
	t_philo			*philos;
	int				i;

	i = -1;
	if (!(philos = malloc(sizeof(t_philo) * setting->num_of_philo)))
		return ;
	if (!(forks = malloc(sizeof(pthread_mutex_t) * setting->num_of_philo)))
		return ;
	while (++i < setting->num_of_philo)
		pthread_mutex_init(&forks[i], NULL);
	if (initiate_philos(setting, philos, forks) == EXIT_SUCCESS)
		wait_philo_died(philos);
	clean_mutex_thread(philos);
	free(forks);
	free(philos);
}
