/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 21:52:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/09/15 22:33:17 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void				*start_routine(void *arg)
{
	t_philo		*p;
	int			nb_time_eat;

	p = (t_philo *)arg;
	nb_time_eat = p->setting->nb_time_eat;
	while (nb_time_eat == -1 || p->n_eat++ != nb_time_eat)
	{
		pthread_mutex_lock(p->left_fork);
		display(p->speaking, p->id, FORK);
		pthread_mutex_lock(p->right_fork);
		display(p->speaking, p->id, FORK);
		p->death_time = get_current_time() + p->setting->time_to_die;
		display(p->speaking, p->id, EAT);
		usleep(p->setting->time_to_eat * 1000);
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		display(p->speaking, p->id, SLEEP);
		usleep(p->setting->time_to_sleep * 1000);
		display(p->speaking, p->id, THINK);
	}
	p->n_eat = -1;
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
			display(philo->speaking, philo->id, DEAD);
			return ;
		}
	}
}

static int			check_args(char **av)
{
	int				i;

	i = 0;
	while (av[++i])
	{
		if (ft_isnum(av[i]))
		{
			write(2, WRONG_NUM, sizeof(WRONG_NUM));
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int					main(int ac, char **av)
{
	t_setting		setting;

	if (ac <= 4 || ac > 6)
	{
		write(2, MISS_SETTINGS, sizeof(MISS_SETTINGS));
		return (EXIT_FAILURE);
	}
	if (check_args(av))
		return (EXIT_FAILURE);
	if (parse_setting(&setting, ac, av))
		return (EXIT_FAILURE);
	g_start_time = 0;
	initiate(&setting);
	return (EXIT_SUCCESS);
}
