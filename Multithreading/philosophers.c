/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 14:30:10 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/05 11:37:56 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_datasets	parsing(t_philo **philos, char **args)
{
	t_datasets	data;
	int			i;

	memset(&data, 0, sizeof(t_datasets));
	data.theorist = ft_atoi(args[1]);
	data.t_die = (useconds_t)ft_atoi(args[2]);
	data.t_eat = (useconds_t)ft_atoi(args[3]);
	data.t_sleep = (useconds_t)ft_atoi(args[4]);
	data.meals = ft_atoi(args[5]);
	_GET_TIME_(data.t_start);
	(*philos) = malloc(sizeof(t_philo) * data.theorist);
	data.forks = malloc(sizeof(pthread_mutex_t) * data.theorist);
	data.msg = malloc(sizeof(pthread_mutex_t));
	if (!data.forks || !(*philos) || !data.msg)
		return (data);
	pthread_mutex_init(data.msg, NULL);
	i = -1;
	while (++i < data.theorist)
	{
		memset(&(*philos)[i], 0, sizeof(t_philo));
		pthread_mutex_init(data.forks + i, NULL);
		(*philos)[i].right_fork = data.forks + i;
		(*philos)[i].left_fork = data.forks + (i + 1) % data.theorist;
	}
	return (data);
}

int	message(char *msg, t_philo *philo, int mode)
{
	unsigned int	t_time;
	int				id;

	pthread_mutex_lock(philo->datasets->msg);
	t_time = t_now(philo->datasets->t_start);
	id = philo->id;
	if (mode & DIE)
		return (printf(STR, t_time, (~id * -1), msg), EXIT_FAILURE);
	printf(STR, t_time, (~id * -1), msg);
	pthread_mutex_unlock(philo->datasets->msg);
	return (EXIT_SUCCESS);
}

int	check(t_philo *theorist, t_datasets *data, int n_mode)
{
	int	i;

	if (n_mode & NORM)
	{
		message("is sleeping", theorist, MSG);
		sleeping(theorist->datasets->t_sleep);
		message("is thinking", theorist, MSG);
		return (EXIT_SUCCESS);
	}
	while (true)
	{
		i = -1;
		while (++i < data->theorist)
		{
			if ((data->meals ^ -1) && !(data->done ^ data->theorist))
				return (EXIT_SUCCESS);
			else if (t_now(data->t_start)
				- theorist[i].t_last_meal > data->t_die)
				return (message("is Die", theorist, DIE), 1);
		}
	}
	return (EXIT_SUCCESS);
}

void	*rotine(void *args)
{
	t_philo	*theorist;

	theorist = (t_philo *)args;
	if (!(theorist->id & 1) % 2)
		usleep(100);
	while (true)
	{
		pthread_mutex_lock(theorist->left_fork);
		message("Has taken left fork", theorist, MSG);
		pthread_mutex_lock(theorist->right_fork);
		message("Has taken right fork", theorist, MSG);
		message("is eating", theorist, MSG);
		sleeping(theorist->datasets->t_eat);
		pthread_mutex_unlock(theorist->left_fork);
		pthread_mutex_unlock(theorist->right_fork);
		theorist->t_last_meal = t_now(theorist->datasets->t_start);
		(theorist->eating)++;
		if (theorist->eating >= theorist->datasets->meals
			&& (theorist->datasets->meals ^ -1))
			return ((theorist->datasets->done)++, args);
		check(theorist, NULL, NORM);
	}
}

int	main(int ac, char **args)
{
	t_datasets	datasets;
	t_philo		*theorist;
	int			i;

	if (ac < 5 || ac > 6 || !input(args + 1))
		return (write(2, "<BAD ARGS>\n", 12), EXIT_FAILURE);
	datasets = parsing(&theorist, args);
	i = -1;
	while (++i < datasets.theorist)
	{
		theorist[i].datasets = &datasets;
		theorist[i].id = i;
		pthread_create(&theorist[i].threads, NULL, rotine, &theorist[i]);
		pthread_detach(theorist[i].threads);
	}
	check(theorist, &datasets, 0);
	usleep(100);
	while (i--)
		pthread_mutex_destroy(&datasets.forks[i]);
	pthread_mutex_destroy(datasets.msg);
	return (free(theorist), free(datasets.forks), free(datasets.msg), 0);
}
