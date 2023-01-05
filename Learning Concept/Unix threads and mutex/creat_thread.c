/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:02:13 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/05 12:07:21 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

void    *routine(void *args)
{
    (void)args;
    puts("HY 1 From thread");
    sleep(2);
    puts("HY 2 From thread");
    return (NULL);
}

int main(void) 
{
    pthread_t p1;
    pthread_t p2;

    // creating threads
    pthread_create(&p1, NULL, routine, NULL);
    pthread_create(&p2, NULL, routine, NULL);
    
    // waiting for threads
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    
    return (EXIT_SUCCESS);
}