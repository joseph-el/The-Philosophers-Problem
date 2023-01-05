/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating thread using loop.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:20:57 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/05 12:36:22 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"


typedef struct s_loop
{
    pthread_mutex_t                 mutex;
    unsigned long long              nb;
    pthread_t                       *thread;
}                   t_test;


void    *routine(void *args)
{
    t_test *test;

    test = (t_test *)args;
    do
    {
        pthread_mutex_lock(&test->mutex);
        test->nb++;
        pthread_mutex_unlock(&test->mutex);
    } while (test->nb < 100000000);
    
    return (NULL);
}

int main(void)
{
    t_test *data;
    int i;

    data = malloc(sizeof(t_test));
    if (!data)
        return (write(2, "MALLOC ERROR\n", 14), exit(1), 1);
    memset(data, 0, sizeof(t_test));
    
    // lets say we need creats 10 threads 
    data->thread = malloc(sizeof(pthread_t) * 10);
    if (! data->thread)
        return (perror("THREAD MALLOC"), exit(1),1);
    
    i = -1;
    // creat 10 threads
    while (++i < 10)
        pthread_create(data->thread + i, NULL, &routine, data);
    while (i--)
        pthread_join(data->thread[i], NULL);
    
    // check race condition for nb
    if ((data->nb % 2) ^ 0)
        puts("No race");
    else
        puts("Race");
    
    free(data->thread);
    free(data);
    return (EXIT_SUCCESS);
}
