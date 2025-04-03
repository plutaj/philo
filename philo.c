/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:06:16 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/04/03 16:57:41 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_table *table;

    edge_cases(argc, argv);
    alloc_init_table(table, argv);
    alloc_create_philos(table);
    return (0);
}

void    alloc_init_table(t_table *table, char **argv)
{
	int	i;

	i = 0;
    table = (t_table *)malloc(sizeof(t_table));
    if (!table)
        exit(1);
    table->num_of_philo = atoi(argv[1]);
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->num_of_philo);
    if (!table->forks)
		exit(1);
	while (i < table->num_of_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	table->time_to_die = atoi(argv[2]);
    table->time_to_eat = atoi(argv[3]);
    table->time_to_sleep = atoi(argv[4]);
    table->number_of_times_each_phil_must_eat = atoi(argv[5]);
	table->philo = NULL;
}

void    create_philos(t_table *table)
{
    int n;

    n = 0;
	t_philo *new_philo;
	t_philo	*head;

	new_philo = NULL;
	alloc_philos(table, new_philo, head, n);
}

void	check_starvation(t_table *table)
{
	/* TU SOM SKONCIL PRACU V TEJTO FUNKII POKRACOVAT*/
	int		i;
	char	*philo_id;

	i = 0;
	while (i < table->num_of_philo)
	{
		if (table->philo->last_meal_time > table->time_to_die)
		{
			philo_id = ft_itoa(table->philo->id);
			write(1, "\nPhilosopher number ", 20);
			write(1, philo_id, 1);
			write(1, "died of starvation", 18);
			exit(0);
		}
		table->philo = table->philo->next;
	}
}

void	alloc_philos(t_table *table, t_philo *new_philo, t_philo *head, int n)
{
	if (table->philo == NULL && table->num_of_philo > 0)
	{
		new_philo = (t_philo *)malloc(sizeof(t_philo));
		if (!new_philo)
			error_msg();
		head = new_philo;
		new_philo->id = n;
		pthread_create(&new_philo->thread, NULL, NULL, &new_philo->id); // add 3rd param
		new_philo->last_meal_time = 0;
		new_philo->times_eaten = 0;
		new_philo->next = NULL;
		table->philo = new_philo;
		n++;
	}
	while(n < table->num_of_philo)
	{
		new_philo = (t_philo *)malloc(sizeof(t_philo));
		if (!new_philo)
			error_msg();
		new_philo->id = n;
		new_philo->last_meal_time = 0;
		new_philo->times_eaten = 0;
		pthread_create(&new_philo->thread, NULL, NULL, &new_philo->id); // add 3rd param
		table->philo->next = new_philo;
		table->philo = table->philo->next;
		table->philo->next = NULL;
		n++;
	}
	table->philo = head;
}

void    edge_cases(int argc, char **argv)
{
    int num_of_philo;
	int	is_digit;
	int	i;

    num_of_philo = atoi(argv[1]);
	i = 2;
    if (argc != 5)
    {
        printf("Error [Wrong number of arguments]\n");
        exit(0);
    }
    if (num_of_philo < 1)
    {
        printf("Error [Wrong number of philosophers]\n");
        exit(0);
    }
	while (i <= 5)
	{
		is_digit(is_digit);

		if ()
		i++;
	}
}