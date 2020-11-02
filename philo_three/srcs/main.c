/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 21:52:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/11/02 14:45:07 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int			check_param(t_setting *setting, int ac)
{
	if (setting->num_of_philo <= 0)
		return (EXIT_FAILURE);
	if (setting->time_to_die < 0 || setting->time_to_eat < 0 ||
		setting->time_to_sleep < 0)
		return (EXIT_FAILURE);
	if (ac == 6 && setting->nb_time_eat < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int			parse_setting(t_setting *setting, int ac, char **arg)
{
	setting->num_of_philo = ft_atoi(arg[1]);
	setting->time_to_die = ft_atoi(arg[2]);
	setting->time_to_eat = ft_atoi(arg[3]);
	setting->time_to_sleep = ft_atoi(arg[4]);
	if (ac == 6)
		setting->nb_time_eat = ft_atoi(arg[5]);
	else
		setting->nb_time_eat = -1;
	if (check_param(setting, ac))
	{
		write(2, WRONG_ARGS, sizeof(WRONG_ARGS));
		return (EXIT_FAILURE);
	}
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
