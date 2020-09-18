/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 21:52:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/09/18 16:52:51 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void			ft_sleep(unsigned int time)
{
	long unsigned int	finish;

	finish = get_current_time() + time;
	while (get_current_time() < finish)
		usleep(1);
}

void				*start_routine(void *arg)
{
	t_philo		*p;

	p = (t_philo *)arg;
	p->death_time = get_current_time() + p->setting->time_to_die;
	while (p->n_eat-- != 0)
	{
		pthread_mutex_lock(p->left_fork);
		display(p->speaking, get_current_time(), p->id, FORK);
		pthread_mutex_lock(p->right_fork);
		display(p->speaking, get_current_time(), p->id, FORK);
		p->death_time = get_current_time() + p->setting->time_to_die;
		display(p->speaking, get_current_time(), p->id, EAT);
		ft_sleep(p->setting->time_to_eat);
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		display(p->speaking, get_current_time(), p->id, SLEEP);
		ft_sleep(p->setting->time_to_sleep);
		display(p->speaking, get_current_time() ,p->id, THINK);
	}
	p->n_eat = -1;
	p->death_time = ULONG_MAX;
	p->setting->end_signal++;
	return (NULL);
}

void				*wait_philo_died(void *arg)
{
	int			i;
	t_philo		*philos;

	philos = (t_philo *)arg;
	i = philos->setting->num_of_philo + 1;
	while (--i >= -1
		&& philos->setting->end_signal != philos->setting->num_of_philo)
	{
		if (i == -1)
			i = philos->setting->num_of_philo + 1;
		if (philos[i].death_time <= get_current_time())
		{
			pthread_mutex_lock(philos->speaking);
			display2(philos[i].death_time, philos[i].id, DEAD);
			return (NULL);
		}
	}
	return (NULL);
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
