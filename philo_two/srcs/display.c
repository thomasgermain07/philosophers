/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:28:38 by thgermai          #+#    #+#             */
/*   Updated: 2020/07/26 00:30:03 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>

int			ft_strlen(char *str)
{
	int			i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

int			convert_to_str(long unsigned int n, char *buff, int start)
{
	int			i;
	int			ret;

	i = start;
	while (n)
	{
		buff[i++] = n % 10 + 48;
		n = n / 10;
	}
	buff[i] = '\0';
	ret = i - start;
	i--;
	while (start < i)
	{
		buff[start] ^= buff[i];
		buff[i] ^= buff[start];
		buff[start] ^= buff[i];
		start++;
		i--;
	}
	return (ret);
}

void		insert_status(char *buff, char *status, int i)
{
	int		j;

	j = -1;
	while (status[++j])
	{
		buff[i] = status[j];
		i++;
	}
	buff[i] = '\0';
}

void			display(sem_t *speaking, int id, char *status)
{
	char		tab[50];
	int			ret;

	ret = convert_to_str(get_current_time(), tab, 0);
	tab[ret] = ' ';
	ret += convert_to_str((long unsigned int)id, tab, ret + 1);
	tab[ret + 1] = ' ';
	insert_status(tab, status, ret + 2);
	if (sem_wait(speaking) == -1)
		exit(EXIT_FAILURE);
	write(1, tab, ft_strlen(tab));
	if (ft_strlen(status) != 5)
		if (sem_post(speaking) == -1)
			exit(EXIT_FAILURE);
}
