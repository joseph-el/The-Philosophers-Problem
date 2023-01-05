/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl race condition.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:17:21 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/05 14:37:37 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

int nb = 0;
pthread_mutex_t mutex;

void* routine(void *args)
{
    int i;

    i = 0;
    do
    {
        pthread_mutex_lock(&mutex);
        i ++;
        pthread_mutex_unlock(&mutex);
        // read nb from registre
        // increment the value of nb
        // write the new value of nb after increment
    } while (i < 1000000);
    return (NULL);
}

int main(void)
{
    pthread_t p1;
    pthread_t p2;
    
    // init mutex
    pthread_mutex_init(&mutex, NULL);
    
    pthread_create(&p1, NULL, &routine, NULL);
    pthread_create(&p2, NULL, &routine, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    if ((nb % 2) ^ 0)
        puts("No race");
    else
        puts("Race");
    
    return (EXIT_SUCCESS);
}