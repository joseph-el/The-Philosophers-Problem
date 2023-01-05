/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:50:23 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/05 11:55:46 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

t_datasets	parsing(t_philo **theorists, char **args)
{
	t_datasets	datasets;

	memset(&datasets, 0, sizeof(t_datasets));
	datasets.theorist = ft_atoi(args[1]);
	datasets.t_die = (useconds_t)ft_atoi(args[2]);
	datasets.t_eat = (useconds_t)ft_atoi(args[3]);
	datasets.t_sleep = (useconds_t)ft_atoi(args[4]);
	datasets.meals = ft_atoi(args[5]);
	datasets.t_start = get_ms();
	sem_unlink(SEM_F);
	sem_unlink(SEM_M);
	datasets.forks = sem_open(SEM_F, O_CREAT, 0644, datasets.theorist);
	datasets.message = sem_open(SEM_M, O_CREAT, 0644, MSG);
	if (datasets.forks == SEM_FAILED || datasets.message == SEM_FAILED)
		exit(1);
	(*theorists) = malloc(sizeof(t_philo) * datasets.theorist);
	if (!(*theorists))
		return (exit(1), datasets);
	return (datasets);
}

void	*rotine(void *args)
{
	t_philo	*theorist;

	theorist = (t_philo *)args;
	while (true)
	{
		sem_wait(theorist->datasets->forks);
		message("has taken a fork", theorist, MSG);
		sem_wait(theorist->datasets->forks);
		message("has taken a fork", theorist, MSG);
		message("is eating", theorist, MSG);
		sleeping(theorist->datasets->t_eat);
		sem_post(theorist->datasets->forks);
		sem_post(theorist->datasets->forks);
		theorist->t_last_meal = t_now(theorist->datasets->t_start);
		(theorist->eating)++;
		if (theorist->eating >= theorist->datasets->meals
			&& (theorist->datasets->meals ^ -1))
			return (theorist->done = true, args);
		message("is sleeping", theorist, MSG);
		sleeping(theorist->datasets->t_sleep);
		message("is thinking", theorist, MSG);
	}
	return (NULL);
}

int	check(t_philo *theorist, t_datasets *data)
{
	while (true)
	{
		if ((data->meals ^ -1) && !(theorist->done ^ true))
			return (EXIT_SUCCESS);
		if (t_now(data->t_start) - theorist->t_last_meal > data->t_die)
			return (message("is Die", theorist, DIE), 1);
		usleep(60);
	}
	return (EXIT_SUCCESS);
}

int	process(t_philo theorist, t_datasets datasets, int *i)
{
	int	s_exit;

	theorist.datasets = &datasets;
	theorist.id = *i;
	if (!(*i & 1) % 2)
		usleep(200);
	pthread_create(&theorist.thread, NULL, rotine, &theorist);
	pthread_detach(theorist.thread);
	s_exit = check(&theorist, &datasets);
	if (!s_exit)
		return (exit(EXIT_SUCCESS), 0);
	return (exit(EXIT_FAILURE), 1);
}

int	main(int ac, char **args)
{
	t_datasets	datasets;
	t_philo		*theorists;
	int			i;

	if (ac < 5 || ac > 6 || !input(args + 1))
		return (write(2, "<BAD ARGS>\n", 12), EXIT_FAILURE);
	datasets = parsing(&theorists, args);
	i = -1;
	while (++i < datasets.theorist)
	{
		memset(&theorists[i], 0, sizeof(t_philo));
		theorists[i].process = fork();
		if (!theorists[i].process)
			process(theorists[i], datasets, &i);
		else if (theorists[i].process < 0)
		{
			killing(theorists, datasets.theorist);
			write(2, "FORK ERROR\n", 12);
			exit(1);
		}
	}
	ft_wait(theorists, datasets);
	sem_close(datasets.forks);
	sem_close(datasets.message);
	return (free(theorists), EXIT_SUCCESS);
}
