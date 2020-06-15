/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 12:57:37 by thomasgerma       #+#    #+#             */
/*   Updated: 2020/06/15 15:11:24 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define WRONG_SETTINGS "Missing arguments\n"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"

typedef struct			s_setting
{
	int					num_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_time_to_eat;
}						t_setting;

typedef struct			s_philo
{
	int					id;
	long unsigned int	death_time;
	int					n_eat;
	pthread_t			thread;
	pthread_mutex_t		*speaking;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_setting			*setting;
}						t_philo;

/*
** Main Functions
*/
int						parse_setting(t_setting *setting, int ac, char **arg);
void					initiate(t_setting *setting);
void					*start_routine(void *arg);
long unsigned int		get_current_time(void);
void					wait_philo_died(void *arg);

/*
** Utiles Functions
*/
int						ft_atoi(const char *str);
void					display(pthread_mutex_t *speaking,
	int id, char *status);
long unsigned int		get_current_time(void);

#endif
