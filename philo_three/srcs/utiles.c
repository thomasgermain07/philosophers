/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 13:07:08 by thomasgerma       #+#    #+#             */
/*   Updated: 2020/11/01 16:18:25 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long unsigned int	get_current_time(void)
{
	struct timeval		t1;

	gettimeofday(&t1, NULL);
	if (!g_start_time)
		return (((t1.tv_sec * 1000) + (t1.tv_usec / 1000)));
	return ((t1.tv_sec * 1000) + (t1.tv_usec / 1000) - g_start_time);
}

int					ft_isnum(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int					ft_atoi(const char *str)
{
	int		i;
	int		neg;
	int		total;

	total = 0;
	neg = 1;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		total = (total * 10) + (str[i] - 48);
		i++;
	}
	return (total * neg);
}

void				ft_sleep(unsigned int time)
{
	long unsigned int	finish;

	finish = get_current_time() + time;
	while (get_current_time() < finish)
		usleep(1);
}

sem_t				*create_sem(char *name, int value)
{
	sem_t			*sem;

	sem_unlink(name);
	sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (sem == SEM_FAILED)
	{
		write(2, SEM_OPEN_FAILED, sizeof(SEM_OPEN_FAILED));
		return (NULL);
	}
	return (sem);
}
