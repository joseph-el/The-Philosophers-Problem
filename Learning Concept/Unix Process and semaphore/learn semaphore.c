/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   learn semaphore.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:18:05 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/05 14:35:36 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

#define SEM "/sem-lol"
#define NB_OF_SEM 1

int g_i;
g_i = 0;

void    child(sem_t **sem)
{
    while (true)
    {
        // lock
        sem_wait((*sem));
        g_i ++;
        if (g_i == 888)
            exit(0);
        sem_post((*sem));
        // unlock
    }
}

int main(void)
{
    pid_t   *pid;
    sem_t   *sem;
    int     i;
    sem = malloc(sizeof(sem_t));

    // unlink sem
    sem_unlink(SEM);
    
    // open the semaphore
    sem = sem_open(SEM, O_CREAT, 0644, NB_OF_SEM);
    // check semaphore
    if (sem == SEM_FAILED)
        exit(1);

    // creat 4 child process
    pid = malloc(sizeof(pid_t) * 4);
    if (!pid)
        exit(2);
    i = -1;
    while (++i < 4)
    {
        pid[i] = fork();
        if (!pid[i])
            child(&sem);
    }
    // waiting for all 4 process
    while (wait(NULL) != -1);
    
    sem_close(sem);
    free(sem);
    free(pid);
    return (puts("ALL IS FINE"), EXIT_SUCCESS);
}