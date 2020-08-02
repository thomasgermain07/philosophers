/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 16:13:21 by thgermai          #+#    #+#             */
/*   Updated: 2020/07/30 22:47:00 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void		create_philos(t_philo *philos, t_setting *setting,
	sem_t *sem, sem_t *speaking)
{
	int				i;

	i = -1;
	while (++i < setting->num_of_philo)
	{
		philos[i].id = i + 1;
		philos[i].n_eat = 0;
		philos[i].setting = setting;
		philos[i].sem = sem;
		philos[i].speaking = speaking;
		philos[i].death_time = get_current_time() + setting->time_to_die;
		pthread_create(&philos[i].thread, NULL, &start_routine, &philos[i]);
		usleep(setting->time_to_eat * 100);
	}
}

static int		check_param(t_setting *setting, int ac)
{
	if (setting->num_of_philo <= 0)
		return (EXIT_FAILURE);
	if (setting->time_to_die < 0 || setting->time_to_eat < 0 ||
		setting->time_to_sleep < 0)
		return (EXIT_FAILURE);
	if (ac == 6 && setting->number_of_time_to_eat < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
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

int				parse_setting(t_setting *setting, int ac, char **arg)
{
	if (check_args(arg))
		return (EXIT_FAILURE);
	setting->num_of_philo = ft_atoi(arg[1]);
	setting->time_to_die = ft_atoi(arg[2]);
	setting->time_to_eat = ft_atoi(arg[3]);
	setting->time_to_sleep = ft_atoi(arg[4]);
	if (ac == 6)
		setting->number_of_time_to_eat = ft_atoi(arg[5]);
	else
		setting->number_of_time_to_eat = -1;
	if (check_param(setting, ac))
	{
		write(2, WRONG_ARGS, sizeof(WRONG_ARGS));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
