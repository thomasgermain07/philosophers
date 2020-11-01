/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:28:38 by thgermai          #+#    #+#             */
/*   Updated: 2020/10/29 10:43:14 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int		convert_to_str(long unsigned int n, char *buff, int start)
{
	int			i;
	int			ret;

	i = start;
	while (n || (!i && !n))
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

static int		insert_status(char *buff, char *status, int i)
{
	buff = buff + i;
	while (status)
	{
		(*((unsigned int *)buff)) = (*((unsigned int *)status));
		if (status[0] && status[1] && status[2] && status[3])
			status += sizeof(unsigned int);
		else
		{
			while (*status)
			{
				*buff = *status;
				buff++;
				status++;
				i++;
			}
			break ;
		}
		buff += sizeof(unsigned int);
		i += sizeof(unsigned int);
	}
	*buff = '\0';
	return (i);
}

void			display(sem_t *speaking,
	long unsigned int time, int id, char *status)
{
	char		tab[50];
	int			ret;

	if (!speaking)
		return ;
	ret = convert_to_str(time, tab, 0);
	tab[ret] = ' ';
	ret += convert_to_str((long unsigned int)id, tab, ret + 1);
	tab[ret + 1] = ' ';
	ret = insert_status(tab, status, ret + 2);
	if (sem_wait(speaking) != -1)
	{
		write(1, tab, ret);
		sem_post(speaking);
	}
}

void			display2(long unsigned int time, int id, char *status)
{
	char		tab[50];
	int			ret;

	ret = convert_to_str(time, tab, 0);
	tab[ret] = ' ';
	ret += convert_to_str((long unsigned int)id, tab, ret + 1);
	tab[ret + 1] = ' ';
	ret = insert_status(tab, status, ret + 2);
	write(1, tab, ret);
}

char			*get_name(int i)
{
	char		*tab;
	int			ret;

	if (!(tab = malloc(sizeof(char) * 12)))
		return (NULL);
	ret = insert_status(tab, "/monitor", 0);
	ret += convert_to_str((unsigned long int)i, tab, ret);
	tab[ret] = '\0';
	return (tab);
}
