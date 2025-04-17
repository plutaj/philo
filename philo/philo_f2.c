/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_f2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:25:14 by jpluta            #+#    #+#             */
/*   Updated: 2025/04/17 21:18:49 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc_philos(t_table *table)
{
	int		n;
	t_philo	*new_philo;
	t_philo	*current;

	n = 0;
	new_philo = (t_philo *)malloc(sizeof(t_philo));
	if (!new_philo)
	{
		printf("Error: Malloc failed\n");
		return (0);
	}
	new_philo->id = n;
	new_philo->last_meal_time = 0;
	new_philo->times_eaten = 0;
	new_philo->next = NULL;
	new_philo->table = table;
	table->philo = new_philo;
	current = new_philo;
	n++;
	if (!alloc_philos_2(n, new_philo, table, current))
		return (0);
	return (1);
}

int	alloc_philos_2(int n, t_philo *new_philo, t_table *table, t_philo *current)
{
	while (n < table->num_of_philo)
	{
		new_philo = (t_philo *)malloc(sizeof(t_philo));
		if (!new_philo)
		{
			printf("Error: Malloc failed\n");
			return (0);
		}
		new_philo->id = n;
		new_philo->last_meal_time = 0;
		new_philo->times_eaten = 0;
		new_philo->next = NULL;
		new_philo->table = table;
		current->next = new_philo;
		current = new_philo;
		n++;
	}
	return (1);
}

void	threads_create_f(t_table *table)
{
	t_philo	*head;

	head = table->philo;
	usleep(1000);
	start_timer(0);
	while (head)
	{
		pthread_mutex_lock(&head->last_meal_time_mutex);
		head->last_meal_time = start_timer(1);
		pthread_mutex_unlock(&head->last_meal_time_mutex);
		head = head->next;
	}
	init_monitoring(table);
	head = table->philo;
	threads_create_f2(head);
	head = table->philo;
	while (head)
	{
		pthread_join(head->thread, NULL);
		head = head->next;
	}
	pthread_join(table->monitoring, NULL);
}

void	threads_create_f2(t_philo *head)
{
	while (head)
	{
		pthread_create(&head->thread, NULL, dining_philosophers, (void *)head);
		head = head->next;
	}
}

void	join_forks(t_table *table)
{
	int		i;
	t_philo	*current;

	i = 0;
	current = table->philo;
	while (table->num_of_philo > i)
	{
		current->left_fork = table->forks[i];
		current->right_fork = table->forks[(i + 1) % table->num_of_philo];
		i++;
		current = current->next;
	}
}
