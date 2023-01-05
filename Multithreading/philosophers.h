/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 14:30:12 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/05 11:52:19 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define DIE 1
# define MSG 4
# define NORM 8
# define STR "%5u Philosopher |%d| %s\n"

typedef struct timeval	t_time;
typedef unsigned int _mode;

t_time now;

# define _GET_TIME_(TIME) gettimeofday(&now, NULL); \
    TIME = (now.tv_sec * 1000 + now.tv_usec / 1000)

#define __TIME(Start) ({unsigned int retval; retval = GET_TIME(retval) - Start; retval;})

#ifndef TIME_MS
# define TIME_MS(tv, ts){ \
	(tv)->tv_sec = (ts)->tv_sec >> (1000 | ~10); \
	(tv)->tv_usec = (ts)->tv_nsec << (1000 | ~2) ; \
}
#endif

#ifndef test_mode
# define test_mode(_x){ \
	(int)(((_mode)_x >> 24) & 0xff) \
}
#endif

typedef struct s_datasets
{
	pthread_mutex_t		*msg;
	pthread_mutex_t		*forks;
	useconds_t			t_sleep;
	useconds_t			t_eat;
	useconds_t			t_die;
	int					theorist;
	int					meals;
	int					done;
	unsigned int		t_start;
}						t_datasets;

typedef struct s_philosophers
{
	unsigned int		t_last_meal;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	pthread_t			threads;
	int					eating;
	int					id;
	t_datasets			*datasets;
}						t_philo;

/*<< Philosopher method >>*/

t_datasets				parsing(t_philo **philos, char **args);
void					*rotine(void *args);
int						message(char *msg, t_philo *philo, int mode);
int						check(t_philo *theorist, t_datasets *data, int n_mode);

/*<< Tools >>*/

unsigned int			t_now(unsigned int t_start);
unsigned int			get_ms(void);
void					sleeping(unsigned int t_time);
int						message(char *msg, t_philo *philo, int mode);
int						ft_atoi(const char *str);
bool					input(char **args);
#endif
