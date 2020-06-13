/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 12:57:37 by thomasgerma       #+#    #+#             */
/*   Updated: 2020/06/13 14:31:06 by thgermai         ###   ########.fr       */
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

typedef struct 			s_fork
{
	unsigned int		id;
	pthread_mutex_t		mutex;
}						t_fork;

typedef struct			s_philo
{
	int					id;
	long unsigned int	death_time;
	int					*is_running;
	pthread_mutex_t		*speaking;
	pthread_t			thread;
	t_fork				*right_fork;
	t_fork				*left_fork;
	t_setting			*setting;
}						t_philo;

/* main functions */
void					parse_setting(t_setting *setting, int ac, char **arg);
void					initiate(t_setting *setting, pthread_t *monitoring);
void					*start_routine(void *arg);
long unsigned int		get_current_time(void);
void					*monitoring_thread(void *arg);
void					clean_mutex_thread(t_philo *philos);

/* utiles functions */
char					*ft_itoa(int num);
char					*ft_strjoin(char const *s1, char const *s2, int option);
void					*ft_memccpy(void *dst, const void *src, int c, size_t n);
int						ft_atoi(const char *str);

# endif
