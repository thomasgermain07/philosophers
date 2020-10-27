/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 12:57:37 by thomasgerma       #+#    #+#             */
/*   Updated: 2020/10/27 22:30:55 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>

// Delete this
# include <stdio.h>

# define MISS_SETTINGS "Error: missing arguments\n"
# define WRONG_ARGS "Error: wrong arguments\n"
# define WRONG_NUM "Error: arguments isn't of type INT\n"
# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define FORK "has taken a fork\n"
# define DEAD "died\n"

long unsigned int		g_start_time;

typedef struct			s_setting
{
	int					num_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_time_eat;
	int					end_count;
	int					end_signal;
}						t_setting;

typedef struct			s_philo
{
	int					id;
	long unsigned int	death_time;
	int					n_eat;
	pthread_t			thread;
	pthread_t			monitor;
	pthread_mutex_t		*speaking;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*eating;
	t_setting			*setting;
}						t_philo;

/*
** Main Functions
*/

void					initiate(t_setting *setting);
void					*start_routine(void *arg);
long unsigned int		get_current_time(void);

/*
** Utiles Functions
*/

int						ft_atoi(const char *str);
void					display(pthread_mutex_t *speaking,
	long unsigned int time, int id, char *status);
void					display2(long unsigned int time, int id, char *status);
long unsigned int		get_current_time(void);
int						ft_isnum(char *str);
void					ft_sleep(unsigned int time);

#endif
