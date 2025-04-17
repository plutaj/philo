/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:01:37 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/04/17 20:23:48 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	edge_cases(int argc, char **argv, t_table *table)
{
	int	num_of_philo;
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Error [Wrong number of arguments]\n");
		free(table);
		return (0);
	}
	if (argc == 5)
		table->number_of_times_each_phil_must_eat = -1;
	else
		table->number_of_times_each_phil_must_eat = 0;
	if (!isnum(argc, argv, table))
		return (0);
	num_of_philo = ft_atoi(argv[1]);
	if (num_of_philo < 1)
	{
		printf("Error [Wrong number of philosophers]\n");
		free(table);
		return (0);
	}
	if (*argv[1] == '1' && !one_philo_case(argv))
		return (0);
	return (1);
}

int	isnum(int argc, char **argv, t_table *table)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_num(argv[i]))
		{
			printf("Error: [Invalid argument]\n");
			free(table);
			return (0);
		}
		i++;
	}
	return (1);
}

void	cleanup(t_table *table)
{
	int		i;
	t_philo	*tmp;
	t_philo	*philo;

	i = 0;
	philo = table->philo;
	while (philo)
	{
		pthread_mutex_destroy(&philo->last_meal_time_mutex);
		pthread_mutex_destroy(&philo->times_eaten_mutex);
		pthread_mutex_destroy(&philo->stop_mutex);
		tmp = philo;
		philo = philo->next;
		free(tmp);
	}
	while (i < table->num_of_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->stop_mutex);
	free(table->forks);
	free(table);
}

int	one_philo_case(char **argv)
{
	long	time_to_die;

	time_to_die = ft_atoi(argv[2]);
	start_timer(0);
	printf("%ld 0 is thinking\n", start_timer(1));
	usleep(time_to_die * 1000);
	printf("%ld 0 died\n", start_timer(1));
	return (0);
}

int	check_stop(t_table *table)
{
	int	result;

	pthread_mutex_lock(&table->stop_mutex);
	result = table->stop;
	pthread_mutex_unlock(&table->stop_mutex);
	return (result);
}
