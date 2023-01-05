/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat new process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:22:24 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/05 14:34:27 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "process.h"

int main(void)
{
    pid_t   pid;

    pid = fork();
    if (! pid)
    {
        puts("HY From child");
        // exit child process
        exit(EXIT_SUCCESS);
    }
    else
        puts("HY FROM PERE");
    return (EXIT_SUCCESS);
}