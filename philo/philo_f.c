/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:22:40 by jpluta            #+#    #+#             */
/*   Updated: 2025/04/17 20:23:19 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dining_philosophers(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_stop(philo->table))
	{
		if (check_stop(philo->table))
			break ;
		if ((philo->id % 2) == 0)
			even_philo(philo);
		else
			odd_philo(philo);
	}
	return (NULL);
}

void	odd_philo(t_philo *philo)
{
	if (check_stop(philo->table))
		return ;
	if (!check_stop(philo->table))
		print_sleeping(philo);
	if (!check_stop(philo->table))
		print_thinking(philo);
	if (pthread_mutex_lock(&philo->right_fork) == 0)
	{
		if (!check_stop(philo->table))
		{
			pthread_mutex_lock(&philo->left_fork);
			print_taken_fork_eating(philo);
			usleep(philo->table->time_to_eat * 1000);
			pthread_mutex_lock(&philo->times_eaten_mutex);
			philo->times_eaten += 1;
			pthread_mutex_unlock(&philo->times_eaten_mutex);
			pthread_mutex_lock(&philo->last_meal_time_mutex);
			philo->last_meal_time = start_timer(1);
			pthread_mutex_unlock(&philo->last_meal_time_mutex);
			pthread_mutex_unlock(&philo->left_fork);
			pthread_mutex_unlock(&philo->right_fork);
		}
		else
			pthread_mutex_unlock(&philo->right_fork);
	}
}

void	even_philo(t_philo *philo)
{
	if (check_stop(philo->table))
		return ;
	if (pthread_mutex_lock(&philo->left_fork) == 0)
	{
		if (!check_stop(philo->table))
		{
			pthread_mutex_lock(&philo->right_fork);
			print_taken_fork_eating(philo);
			usleep(philo->table->time_to_eat * 1000);
			pthread_mutex_lock(&philo->times_eaten_mutex);
			philo->times_eaten += 1;
			pthread_mutex_unlock(&philo->times_eaten_mutex);
			pthread_mutex_lock(&philo->last_meal_time_mutex);
			philo->last_meal_time = start_timer(1);
			pthread_mutex_unlock(&philo->last_meal_time_mutex);
			pthread_mutex_unlock(&philo->left_fork);
			pthread_mutex_unlock(&philo->right_fork);
		}
		else
			pthread_mutex_unlock(&philo->left_fork);
		if (!check_stop(philo->table))
			print_sleeping(philo);
		if (!check_stop(philo->table))
			print_thinking(philo);
	}
}
