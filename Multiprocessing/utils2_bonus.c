/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:50:28 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/01 23:24:19 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	message(char *msg, t_philo *philo, int mode)
{
	int	t_time;
	int	id;

	sem_wait(philo->datasets->message);
	t_time = get_ms() - philo->datasets->t_start;
	id = philo->id;
	if (mode & DIE)
		return (printf(STR, t_time, (~id * -1), msg), EXIT_FAILURE);
	printf(STR, t_time, (~id * -1), msg);
	sem_post(philo->datasets->message);
	return (EXIT_SUCCESS);
}

void	killing(t_philo *theorists, int philosophers)
{
	int	i;

	i = -1;
	while (++i < philosophers)
		kill(theorists[i].process, SIGKILL);
}

int	ft_wait(t_philo *theorists, t_datasets datasets)
{
	int	s_exit;
	int	failure;

	while (true)
	{
		failure = waitpid(-1, &s_exit, 0);
		if (failure == -1)
			return (EXIT_SUCCESS);
		if (WIFEXITED(s_exit) && WEXITSTATUS(s_exit) == EXIT_SUCCESS)
			continue ;
		return (killing(theorists, datasets.theorist), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
