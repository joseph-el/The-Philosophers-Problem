/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 14:30:08 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/05 11:38:51 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	number;

	if (!str)
		return (-1);
	number = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		return (-1);
	str += (*str == '+');
	while (*str && *str >= 48 && *str <= 57)
	{
		number = (number * 10) + (*str - '0');
		str++;
	}
	if (*str)
		return (-1);
	return (number);
}

bool	input(char **args)
{
	while (*args)
		if (ft_atoi(*args++) <= false)
			return (false);
	return (true);
}

unsigned int	get_ms(void)
{
	t_time	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void	sleeping(unsigned int t_time)
{
	unsigned int	t_now;

	t_now = get_ms();
	while (get_ms() - t_now < t_time)
		usleep(50);
}

unsigned int	t_now(unsigned int t_start)
{
	unsigned int	time_t;
	
	_GET_TIME_(time_t);
	return (time_t - t_start);
}
