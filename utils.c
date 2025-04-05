/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:59:17 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/04/05 14:38:12 by jpluta           ###   ########.fr       */
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
	{
        i++;
	}
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

int	is_num(char *num)
{
	while (num)
	{
		if (!is_digit(*num))
			return (1);
		num++;
	}
	return (0);
}

int	is_digit(char c)
{
	int	n;

	n = ft_atoi(&c);
	if (n >= 48 && n <= 57)
		return (1);
	else
		return (0);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
