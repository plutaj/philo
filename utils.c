/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:59:17 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/03/22 15:49:01 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_atoi(const char *str)
{
	int			i;
	int			sign;
	int			num;
	const char	*p_str;

	i = 0;
	num = 0;
	sign = 1;
	p_str = str;
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
            || str[i] == '\r' || str[i] == '\v')
        i++;
	if (p_str[i] == '+' || p_str[i] == '-')
	{
        if (p_str[i] == '-')
		    sign = -1;
		i++;
	}
	while (p_str[i] >= '0' && p_str[i] <= '9')
	{
		num = num * 10 + (p_str[i] - '0');
		i++;
	}
	return (num * sign);
}