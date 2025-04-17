/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:18:10 by jpluta            #+#    #+#             */
/*   Updated: 2025/04/17 21:03:29 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_taken_fork_eating(t_philo *philo)
{
	if (!check_stop(philo->table))
	{
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("%ld %d has taken a fork\n", start_timer(1), philo->id);
		printf("%ld %d is eating\n", start_timer(1), philo->id);
		pthread_mutex_unlock(&philo->table->print_mutex);
	}
}

void	print_thinking(t_philo *philo)
{
	if (!check_stop(philo->table))
	{
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("%ld %d is thinking\n", start_timer(1), philo->id);
		pthread_mutex_unlock(&philo->table->print_mutex);
		usleep((philo->table->time_to_eat - philo->table->time_to_sleep)
			* 1000);
	}
}

void	print_sleeping(t_philo *philo)
{
	if (!check_stop(philo->table))
	{
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("%ld %d is sleeping\n", start_timer(1), philo->id);
		pthread_mutex_unlock(&philo->table->print_mutex);
		usleep(philo->table->time_to_sleep * 1000);
	}
}
