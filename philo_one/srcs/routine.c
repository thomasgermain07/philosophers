/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 22:23:22 by thgermai          #+#    #+#             */
/*   Updated: 2020/11/04 05:35:27 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void		*monitoring(void *arg)
{
	t_philo				*p;
	long unsigned int	time;

	p = (t_philo *)arg;
	while (!p->setting->end_signal)
	{
		pthread_mutex_lock(p->eating);
		if ((time = get_current_time()) >= p->death_time)
		{
			pthread_mutex_lock(p->speaking);
			display2(time, p->id, DEAD);
			p->setting->end_signal = 1;
		}
		else
		{
			pthread_mutex_unlock(p->eating);
			ft_sleep(1);
		}
	}
	return (NULL);
}

static void		eat(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	display(p->speaking, get_current_time(), p->id, FORK);
	pthread_mutex_lock(p->right_fork);
	display(p->speaking, get_current_time(), p->id, FORK);
	pthread_mutex_lock(p->eating);
	if (p->death_time != get_current_time())
		p->death_time = get_current_time() + p->setting->time_to_die;
	display(p->speaking, get_current_time(), p->id, EAT);
	ft_sleep(p->setting->time_to_eat);
	pthread_mutex_unlock(p->eating);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

void			*start_routine(void *arg)
{
	t_philo				*p;

	p = (t_philo *)arg;
	p->death_time = get_current_time() + p->setting->time_to_die;
	pthread_create(&p->monitor, NULL, monitoring, arg);
	pthread_detach(p->monitor);
	while (p->n_eat-- != 0 && !p->setting->end_signal)
	{
		eat(p);
		display(p->speaking, get_current_time(), p->id, SLEEP);
		ft_sleep(p->setting->time_to_sleep);
		display(p->speaking, get_current_time(), p->id, THINK);
	}
	p->n_eat = -1;
	p->death_time = ULONG_MAX;
	p->setting->end_count++;
	return (NULL);
}
