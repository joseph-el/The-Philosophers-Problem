/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting for a child process.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:25:41 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/05 14:08:31 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

typedef struct s_data
{
    char    *n_mom;
    char    *n_pere;
    int     tele;
    int     job;
}               t_data;

typedef struct s_process
{
    char    *name;
    int     age;
    int     id;
    pid_t   pid;
    t_data  *data;
}               t_prc;

int child(t_prc prss, int *id)
{
    int	val;
    int i;
    
	srand(time(NULL));
	val = rand();
    i = 0;
    while (true)
    {
        i ++;
        if (((val % i) * -1) >> 2)
            exit(EXIT_FAILURE);
        else if (! (i ^ 1000))
            break;
    }
    return (EXIT_SUCCESS);
}

int main(void)
{
    t_prc   *childs;
    t_data  data;
    int     i;

    // init data
    memset(&data, 0, sizeof(t_data));
    data.n_mom = strdup("FATIMA");
    data.n_pere = strdup("HAMIDE");
    data.tele = 06123456;
    // giving the t_prc struct for 4 childs
    childs = malloc(sizeof(t_prc) * 4);
    i = -1;
    while (++i < 4)
    {
        // init the struct t_prc for childs
        memset(&childs[i], 0, sizeof(t_prc));
        childs[i].data = &data;
        childs[i].age = (i + 1) + 15;
        childs[i].name = strdup("INKONU");
        // creat new process for child (i)
        childs[i].pid = fork();
        if (!childs[i].pid)
            child(childs[i], &i); // the job for all childs
        // if the fork failed 
        else if (childs[i].pid < 0)
        // kill all process
            kill(0, SIGKILL);
    }
    
    // wiating all child process
    
    int failed;
    int exit_status_for_any_process;
    while (true)
    {
        failed = waitpid(-1, &exit_status_for_any_process, 0);
        if (failed == -1)
        {
            // When all childs processes exit by normal then we need to exit from the while(true)
            // if waitpid Did not find what u are waiting for then waitpid return -1
            return (EXIT_SUCCESS);
        }
        // check the exit status 
        // if the exit status FAILED then we kill all process
        // else if the exit status success then we continue waiting another process
        if (WEXITSTATUS(exit_status_for_any_process) == EXIT_SUCCESS)
            continue;
        // kill all process
        kill(0, SIGKILL);
    }
    
    return (EXIT_SUCCESS);
}
