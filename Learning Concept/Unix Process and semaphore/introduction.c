/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   introduction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:20:38 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/01/05 14:35:23 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

int main(void)
{
    
    fork();
    puts("Hello World");
    
    return (EXIT_SUCCESS);
}

/**
* output :
* Hello World
* Hello World
**/