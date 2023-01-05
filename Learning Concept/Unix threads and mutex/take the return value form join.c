/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take the return value form join.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:54:47 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/05 13:03:42 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "thread.h"

typedef struct s_test
{
    unsigned long             lol;
    pthread_mutex_t         metux;
}                   t_test;


void    *routine(void* arg)
{
    // rotine func void so we need to casting 
    t_test  *help;
    int     *res;

    help = (t_test *)arg;
    res = malloc(sizeof(int));
    while (true)
    {
        help->lol ++;
        if (help->lol < 200)
            continue;
        else
            break;
    }
    *res = help->lol;
    return ((void *)res);
}

int main(void)
{
    pthread_t thread;
    t_test *data;
    int i;
    int *result;
    

    data = malloc(sizeof(t_test));
    if (!data)
        return (write(2, "MALLOC ERROR\n", 14), exit(1), 1);
    memset(data, 0, sizeof(t_test));

    // use argument 4 for send struct data to rotine func
    pthread_create(thread, NULL, routine, data);
    
    // ------ Take the return value of rotine func using the arg 2 in join
    pthread_join(thread, (void **)&result);
    
    printf("the result is |%d|\n", *result);
    
    if (data->lol ^ *result)
        puts("Join return FAILURE");
    else
        puts("Join return SUCCESS");
    
    free(data);
    free(result);
    return (EXIT_SUCCESS);
}