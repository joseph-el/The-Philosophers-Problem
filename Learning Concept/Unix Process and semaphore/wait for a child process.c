/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait for a child process.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:10:32 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/05 14:17:04 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

void    process(void)
{
    int i;

    i = -1;
    do
    {
        sleep(1);
    } while (++i < 4);
    if (!(i ^ 4))
        exit(EXIT_SUCCESS); // exit child process
}

int main(int ac, char **av)
{
    int pid;

    puts("HEY");
    pid = fork();
    if (pid == 0)
        process();
    
    // Waiting for processes to finish
    // 1
    waitpid(pid, NULL, 0); // waiting for child process
    
    // 2
    // wait(NULL); the wait system calls waiting all child process
    
    return (puts("ALL IS FINE"), EXIT_SUCCESS);
}