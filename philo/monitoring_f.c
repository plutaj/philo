/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:27:34 by jpluta            #+#    #+#             */
/*   Updated: 2025/04/17 21:13:39 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_monitoring(t_table *table)
{
	pthread_create(&table->monitoring, NULL, monitoring_f, (void *)table);
}

int	have_all_eaten(t_table *table)
{
	t_philo	*head;

	head = table->philo;
	if (table->number_of_times_each_phil_must_eat == -1)
		return (0);
	while (head)
	{
		pthread_mutex_lock(&head->times_eaten_mutex);
		if (head->times_eaten < table->number_of_times_each_phil_must_eat)
		{
			pthread_mutex_unlock(&head->times_eaten_mutex);
			return (0);
		}
		pthread_mutex_unlock(&head->times_eaten_mutex);
		head = head->next;
	}
	return (1);
}

void	*monitoring_f(void *arg)
{
	t_philo	*head;
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		head = table->philo;
		while (head)
		{
			pthread_mutex_lock(&head->last_meal_time_mutex);
			if ((start_timer(1) - head->last_meal_time) > table->time_to_die)
				return (died_of_starvation(table, head));
			pthread_mutex_unlock(&head->last_meal_time_mutex);
			head = head->next;
		}
		if (handle_all_eaten(table) == NULL)
			return (NULL);
		usleep(1000);
	}
}

static void	*handle_all_eaten(t_table *table)
{
	if (have_all_eaten(table))
	{
		pthread_mutex_lock(&table->stop_mutex);
		write(1, "Program succsessfully finished\n", 31);
		table->stop = 1;
		pthread_mutex_unlock(&table->stop_mutex);
		return (NULL);
	}
	return ((void *)1);
}

static void	*died_of_starvation(t_table *table, t_philo *philo)
{
	pthread_mutex_unlock(&philo->last_meal_time_mutex);
	pthread_mutex_lock(&table->print_mutex);
	printf("%ld %u died\n", start_timer(1), philo->id);
	pthread_mutex_unlock(&table->print_mutex);
	pthread_mutex_lock(&table->stop_mutex);
	table->stop = 1;
	pthread_mutex_unlock(&table->stop_mutex);
	return (NULL);
}

// void	*monitoring_f(void *arg)
// {
// 	t_philo	*head;
// 	t_table	*table;

// 	table = (t_table *)arg;
// 	while (1)
// 	{
// 		head = table->philo;
// 		while (head)
// 		{
// 			pthread_mutex_lock(&head->last_meal_time_mutex);
// 			if ((start_timer(1) - head->last_meal_time) > table->time_to_die)
// 			{
// 				pthread_mutex_unlock(&head->last_meal_time_mutex);
// 				pthread_mutex_lock(&table->print_mutex);
// 				printf("%ld %u died\n", start_timer(1), head->id);
// 				pthread_mutex_unlock(&table->print_mutex);
// 				pthread_mutex_lock(&table->stop_mutex);
// 				table->stop = 1;
// 				pthread_mutex_unlock(&table->stop_mutex);
// 				return (NULL);
// 			}
// 			else
// 				pthread_mutex_unlock(&head->last_meal_time_mutex);
// 			head = head->next;
// 		}
// 		if (have_all_eaten(table))
// 		{
// 			pthread_mutex_lock(&table->stop_mutex);
// 			write(1, "Program succsessfully finished\n", 31);
// 			table->stop = 1;
// 			pthread_mutex_unlock(&table->stop_mutex);
// 			return (NULL);
// 		}
// 		usleep(1000);
// 	}
// }
