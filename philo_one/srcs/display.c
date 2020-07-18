/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:28:38 by thgermai          #+#    #+#             */
/*   Updated: 2020/07/17 14:39:25 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>

static void		ft_putnbr(long unsigned int n)
{
	long unsigned int	nb;
	char				c;

	nb = n;
	if (nb >= 10)
		ft_putnbr((nb / 10));
	c = (nb % 10) + 48;
	write(1, &c, 1);
}

static int		ft_strlen(char *str)
{
	int			i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

void			display(pthread_mutex_t *speaking, int id, char *status)
{
	pthread_mutex_lock(speaking);
	ft_putnbr(get_current_time());
	write(1, " ", 1);
	ft_putnbr((long unsigned int)id);
	write(1, " ", 1);
	write(1, status, ft_strlen(status));
	pthread_mutex_unlock(speaking);
}
