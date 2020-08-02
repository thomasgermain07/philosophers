/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 12:57:37 by thomasgerma       #+#    #+#             */
/*   Updated: 2020/08/01 19:15:01 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <errno.h>

# define MISS_SETTINGS "Error: missing arguments\n"
# define WRONG_ARGS "Error: wrong arguments\n"
# define WRONG_NUM "Error: arguments isn't of type INT\n"
# define SEM_OPEN_FAILED "Error: sem_open failed\n"
# define SEM_WAIT_FAILED "Error: sem_wait failed\n"
# define SEM_POST_FAILED "Error: sem_post failed\n"

# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define FORK "has taken a fork\n"
# define DEAD "died\n"

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
	int					*signal;
	pthread_t			thread;
	sem_t				*sem;
	sem_t				*speaking;
	t_setting			*setting;
}						t_philo;

/*
** Main Functions
*/
int						parse_setting(t_setting *setting, int ac, char **arg);
long unsigned int		get_current_time(void);
void					*start_routine(void *arg);
void					create_philos(t_philo *philos, t_setting *setting,
	sem_t *sem, sem_t *speaking);
/*
** Utiles Functions
*/
int						ft_atoi(const char *str);
void					display(sem_t *speaking, int id, char *status);
long unsigned int		get_current_time(void);
int						ft_isnum(char *str);
int						ft_strlen(char *str);

#endif
