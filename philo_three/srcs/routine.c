/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 22:23:22 by thgermai          #+#    #+#             */
/*   Updated: 2020/11/04 05:36:19 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void		*monitoring(void *arg)
{
	t_philo				*p;
	long unsigned int	time;

	p = (t_philo *)arg;
	while (!p->setting->end_signal && p->death_time != ULONG_MAX)
	{
		sem_wait(p->monitor_sem);
		if ((time = get_current_time()) >= p->death_time)
		{
			sem_wait(p->speaking);
			display2(time, p->id, DEAD);
			exit(1);
		}
		else
		{
			sem_post(p->monitor_sem);
			ft_sleep(1);
		}
	}
	return (NULL);
}

static void		eat(t_philo *p)
{
	sem_wait(p->forks);
	display(p->speaking, get_current_time(), p->id, FORK);
	sem_wait(p->forks);
	display(p->speaking, get_current_time(), p->id, FORK);
	sem_wait(p->monitor_sem);
	if (p->death_time != get_current_time())
		p->death_time = get_current_time() + p->setting->time_to_die;
	display(p->speaking, get_current_time(), p->id, EAT);
	ft_sleep(p->setting->time_to_eat);
	sem_post(p->monitor_sem);
	sem_post(p->forks);
	sem_post(p->forks);
}

void			start_routine(void *arg)
{
	t_philo				*p;

	p = (t_philo *)arg;
	p->death_time = get_current_time() + p->setting->time_to_die;
	pthread_create(&p->monitor, NULL, monitoring, (void *)p);
	pthread_detach(p->monitor);
	while (p->n_eat-- != 0 && !p->setting->end_signal)
	{
		eat(p);
		display(p->speaking, get_current_time(), p->id, SLEEP);
		ft_sleep(p->setting->time_to_sleep);
		display(p->speaking, get_current_time(), p->id, THINK);
	}
	exit(1);
}
