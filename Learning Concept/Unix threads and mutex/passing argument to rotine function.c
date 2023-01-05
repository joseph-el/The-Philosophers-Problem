/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   passing argument to rotine function.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:37:30 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/05 12:53:39 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

int	count_len(int nb)
{
	long	n;
	int		url;

	n = nb;
	url = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		url++;
		n *= -1;
	}
	while (n != 0)
	{
		n /= 10;
		url++;
	}
	return (url);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	nb;

	nb = n;
	i = count_len(nb);
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (n == 0)
		return (str[0] = '0', str);
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	while (nb != 0)
	{
		str[i] = 48 + (nb % 10);
		nb /= 10;
		i--;
	}
	return (str);
}

typedef struct s_test
{
    char                        *str;
    unsigned long             lol;
    pthread_mutex_t         metux;
}                   t_test;


void    *routine(void* arg)
{
    // rotine func void so we need to casting 
    t_test  *help;

    help = (t_test *)arg;
    while (true)
    {
        help->lol ++;
        
        printf("Value of nb ");
        help->str = strdup(ft_itoa(help->lol));
        puts(help->str);
        free(help->str);
        
        if (help->lol < 1000000)
            continue;
        else
            break;
    }
    return (NULL);
}

int main(void)
{
    pthread_t thread;
    t_test *data;
    int i;

    data = malloc(sizeof(t_test));
    if (!data)
        return (write(2, "MALLOC ERROR\n", 14), exit(1), 1);
    memset(data, 0, sizeof(t_test));

    // use argument 4 for send struct data to rotine func
    pthread_create(thread, NULL, routine, data);
    
    // waiting fro threads
    pthread_join(thread, NULL);

    pritnf("|%d|\n", data->lol);
    free(data);
    return (EXIT_SUCCESS);
}