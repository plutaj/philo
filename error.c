/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:01:37 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/04/04 18:15:24 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    error_msg()
{
    printf("Error [philo malloc failed]\n");
    exit(1);
}

void	ft_error2()
{
	write(1, "Error one of arguments is not valid number\n", 43);
	exit(1);
}
