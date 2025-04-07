/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:01:37 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/04/07 18:28:30 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    error_msg_1()
{
    printf("Error1 [philo malloc failed]\n");
    exit(1);
}

void    error_msg_2()
{
    printf("Error2 [philo malloc failed]\n");
    exit(1);
}

void    error_msg_3()
{
    printf("Error3 [philo malloc failed]\n");
    exit(1);
}

void	ft_error2()
{
	write(1, "Error one of arguments is not valid number\n", 43);
	exit(1);
}
