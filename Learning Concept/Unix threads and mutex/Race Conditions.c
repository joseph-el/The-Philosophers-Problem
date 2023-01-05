/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Race Conditions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:08:38 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/05 12:16:28 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

int nb = 0;

void* routine(void *args)
{
    int i;

    i = 0;
    do
    {
        // read nb from registre
        // increment the value of nb
        // write the new value of nb after increment
    } while (++i < 1000000);
    return (NULL);
}

int main(void)
{
    pthread_t p1;
    pthread_t p2;
    
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