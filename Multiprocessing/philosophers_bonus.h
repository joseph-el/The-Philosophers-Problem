/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:49:45 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/01 23:22:47 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define STR "%5u Philosopher |%d| %s\n"
# define SEM_F "/sem-forks"
# define SEM_M "/sem-msg"
# define DIE 4
# define MSG 1

typedef struct timeval	t_time;

typedef struct s_datasets
{
	sem_t				*message;
	sem_t				*forks;
	int					theorist;
	useconds_t			t_sleep;
	useconds_t			t_eat;
	useconds_t			t_die;
	int					meals;
	unsigned int		t_start;
}						t_datasets;

typedef struct s_philosophers
{
	unsigned int		t_last_meal;
	pthread_t			thread;
	pid_t				process;
	int					eating;
	int					id;
	int					done;
	int					s_exit;
	t_datasets			*datasets;
}						t_philo;

/*<< Philosopher method >>*/

t_datasets				parsing(t_philo **theorists, char **args);
int						check(t_philo *theorist, t_datasets *data);
int						process(t_philo theorist, t_datasets datasets, int *i);

/*<< Tools >>*/

unsigned int			get_ms(void);
unsigned int			t_now(unsigned int t_start);
void					sleeping(unsigned int t_time);
void					killing(t_philo *theorists, int philosophers);
int						message(char *msg, t_philo *philo, int mode);
int						ft_wait(t_philo *theorists, t_datasets datasets);
int						ft_atoi(const char *str);
bool					input(char **args);

#endif