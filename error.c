/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:01:37 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/04/12 13:22:17 by jozefpluta       ###   ########.fr       */
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

void	one_philo_case(char **argv)
{
	long	time_to_die;

	time_to_die = ft_atoi(argv[2]);
	start_timer(0);
	printf("%ld 0 is thinking\n", start_timer(1));
	usleep(time_to_die * 1000);
	printf("%ld 0 died\n", start_timer(1));
	exit(0);
}