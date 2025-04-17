/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:06:16 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/04/17 20:32:26 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (0);
	if (!edge_cases(argc, argv, table))
		return (0);
	if (!alloc_init_table(table, argv))
		return (0);
	if (!alloc_philos(table))
		return (0);
	join_forks(table);
	init_support_mutexes(table->philo);
	threads_create_f(table);
	cleanup(table);
	return (0);
}

void	init_support_mutexes(t_philo *philo)
{
	t_philo	*head;

	head = philo;
	while (head)
	{
		pthread_mutex_init(&head->last_meal_time_mutex, NULL);
		pthread_mutex_init(&head->times_eaten_mutex, NULL);
		pthread_mutex_init(&head->stop_mutex, NULL);
		head = head->next;
	}
}

long	start_timer(int i)
{
	static struct timeval	start_time;
	struct timeval			end_time;
	long					elapsed_time;
	long					seconds;
	long					microseconds;

	if (i == 0)
	{
		gettimeofday(&start_time, NULL);
		return (0);
	}
	gettimeofday(&end_time, NULL);
	seconds = end_time.tv_sec - start_time.tv_sec;
	microseconds = end_time.tv_usec - start_time.tv_usec;
	if (microseconds < 0)
	{
		microseconds += 1000000;
		seconds -= 1;
	}
	elapsed_time = seconds * 1000 + microseconds / 1000;
	return (elapsed_time);
}

int	alloc_init_table(t_table *table, char **argv)
{
	int	i;

	i = 0;
	table->num_of_philo = ft_atoi(argv[1]);
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->num_of_philo);
	if (!table->forks)
	{
		printf("Error1 [philo malloc failed]\n");
		return (0);
	}
	while (i < table->num_of_philo)
		pthread_mutex_init(&table->forks[i++], NULL);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (table->number_of_times_each_phil_must_eat == 0)
		table->number_of_times_each_phil_must_eat = ft_atoi(argv[5]);
	table->philo = NULL;
	table->stop = 0;
	pthread_mutex_init(&table->stop_mutex, NULL);
	pthread_mutex_init(&table->print_mutex, NULL);
	return (1);
}
