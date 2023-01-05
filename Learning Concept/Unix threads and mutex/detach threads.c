/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detach threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:06:54 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/05 14:37:19 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "thread.h"

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
    } while (test->nb < 1000);
    
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
    
    // creats 10 threads 
    data->thread = malloc(sizeof(pthread_t) * 10);
    if (! data->thread)
        return (perror("THREAD MALLOC"), exit(1),1);
    
    i = -1;
    while (++i < 10)
    {
        pthread_create(data->thread + i, NULL, &routine, data);
        // detach thread
        pthread_detach(data->thread[i]);
    }
    
    int status = 0;
    
    while (true)
    {
        i = -1;
        // checking for all 10 threads
        while (++i < 10)
        {
            if (data->nb == 888)
            {
                status = true;
                break;
            }
        }
        if (!(status ^ true))
            break;
    }
    sleep(1);
    pthread_mutex_destroy(&data->mutex);
    free(data->thread);
    free(data);
    return (EXIT_SUCCESS);
}