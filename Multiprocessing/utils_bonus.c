/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:50:26 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/01 23:24:14 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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

unsigned int	get_ms(void)
{
	t_time	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

bool	input(char **args)
{
	while (*args)
		if (ft_atoi(*args++) <= false)
			return (false);
	return (true);
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
	return (get_ms() - t_start);
}
